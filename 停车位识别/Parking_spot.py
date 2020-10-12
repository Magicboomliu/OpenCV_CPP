__author__ = "Luke Liu"
#encoding="utf-8"

#导入需要的库文件
import matplotlib.pyplot as plt
import cv2
import os, glob
import numpy as np


class Parking_spot:
    # 显示test用例的2张图片
    def show_images(self,images,cmap=None):
        cols=2
        rows = (len(images) + 1) // cols
        plt.figure(figsize=(15, 12))
        for i, image in enumerate(images):
            plt.subplot(rows, cols, i+1)
            if len(image.shape)==2:
                cmap='gray'
            else:
                cmap=None
            plt.imshow(image, cmap=cmap)
            plt.xticks([])
            plt.yticks([])
        plt.tight_layout(pad=0, h_pad=0, w_pad=0)
        plt.show()

    #显示图片
    def cv_show(self,name,img):
        cv2.imshow(name, img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

    #去除过滤部分颜色，保留一部分颜色
    def select_rgb_white_yellow(self, image):
        # 过滤掉背景
        lower = np.uint8([120, 120, 120])
        upper = np.uint8([255, 255, 255])
        # lower_red和高于upper_red的部分分别变成0，lower_red～upper_red之间的值变成255,相当于过滤背景
        white_mask = cv2.inRange(image, lower, upper)
        # self.cv_show('white_mask', white_mask)

        masked = cv2.bitwise_and(image, image, mask=white_mask)
        # self.cv_show('masked', masked)
        return masked
    # 转化为灰度图像
    def convert_gray_scale(self,image):
        return cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    #边缘检测，使用Canny算子进行检测。
    def detect_edges(self,image, low_threshold=50, high_threshold=200):
        return cv2.Canny(image, low_threshold, high_threshold)
    #建立一个mask
    def filter_region(self,image, vertices):
        """
                剔除掉不需要的地方
        """
        mask = np.zeros_like(image)
        if len(mask.shape)==2:
            cv2.fillPoly(mask, vertices, 255)
            # self.cv_show('mask', mask)
        return cv2.bitwise_and(image, mask)

    #选择我们需要的区域，使用6个点
    def select_region(self, image):
        """
                手动选择区域
        """
        # first, define the polygon by vertices
        rows, cols = image.shape[:2]
        pt_1 = [cols * 0.05, rows * 0.90]
        pt_2 = [cols * 0.05, rows * 0.70]
        pt_3 = [cols * 0.30, rows * 0.55]
        pt_4 = [cols * 0.6, rows * 0.15]
        pt_5 = [cols * 0.90, rows * 0.15]
        pt_6 = [cols * 0.90, rows * 0.90]

        vertices = np.array([[pt_1, pt_2, pt_3, pt_4, pt_5, pt_6]], dtype=np.int32)
        point_img = image.copy()
        point_img = cv2.cvtColor(point_img, cv2.COLOR_GRAY2RGB)
        for point in vertices[0]:
            cv2.circle(point_img, (point[0], point[1]), 10, (0, 0, 255), 4)
        # self.cv_show('point_img', point_img)

        return self.filter_region(image, vertices)

    #由于停车位主要是一个直线组成的几何体，在这里使用Hough直线检测
    def hough_lines_detect(self,image):
        # 输入的图像需要是边缘检测后的结果
        # minLineLengh(线的最短长度，比这个短的都被忽略)和MaxLineCap（两条直线之间的最大间隔，小于此值，认为是一条直线）
        # rho距离精度,theta角度精度,threshod超过设定阈值才被检测出线段
        return cv2.HoughLinesP(image, rho=0.1, theta=np.pi / 10, threshold=15, minLineLength=9, maxLineGap=4)

    def draw_lines(self, image, lines, color=[255, 0, 0], thickness=2, make_copy=True):
        # 过滤霍夫变换检测到直线
        if make_copy:
            image = np.copy(image)
        #对直线进行筛选，对长度与方向做一定的取舍
        cleaned = []
        for line in lines:
            for x1, y1, x2, y2 in line:
                if abs(y2 - y1) <= 1 and abs(x2 - x1) >= 25 and abs(x2 - x1) <= 55:
                    cleaned.append((x1, y1, x2, y2))
                    cv2.line(image, (x1, y1), (x2, y2), color, thickness)
        print(" No lines detected: ", len(cleaned))
        return image

    # 确定每个停车位区域的位置
    def identify_blocks(self, image, lines, make_copy=True):
        #拷贝一下原图
        if make_copy:
            new_image = np.copy(image)
        # Step 1: 过滤部分直线
        cleaned = []
        for line in lines:
            # 对直线进行筛选，对长度与方向做一定的取舍
            for x1, y1, x2, y2 in line:
                if abs(y2 - y1) <= 1 and abs(x2 - x1) >= 25 and abs(x2 - x1) <= 55:
                    cleaned.append((x1, y1, x2, y2))

        # Step 2: 对直线按照x1进行排序，x1一样的按照y1排序
        import operator
        list1 = sorted(cleaned, key=operator.itemgetter(0, 1))

        # Step 3: 找到多个列，相当于每列是一排车
        clusters = {}
        dIndex = 0
        #规定一个最短的距离
        clus_dist = 10

        for i in range(len(list1) - 1):
            distance = abs(list1[i + 1][0] - list1[i][0])
            #x1之差距小于最短距离被认为是一cluster，排过序
            if distance <= clus_dist:
                if not dIndex in clusters.keys(): clusters[dIndex] = []
                clusters[dIndex].append(list1[i])
                clusters[dIndex].append(list1[i + 1])

            else:
                #否则开辟一个新的cluster
                dIndex += 1

        # Step 4: 统计每个cluster外接矩形的坐标
        rects = {}
        i = 0
        #每个cluster按照y1排序
        for key in clusters:
            all_list = clusters[key]
            cleaned = list(set(all_list))
            if len(cleaned) > 5:
                cleaned = sorted(cleaned, key=lambda tup: tup[1])
                # y1,y2取最大最小
                avg_y1 = cleaned[0][1]
                avg_y2 = cleaned[-1][1]

                #x1,x2取平均值
                avg_x1 = 0
                avg_x2 = 0

                for tup in cleaned:
                    avg_x1 += tup[0]
                    avg_x2 += tup[2]
                avg_x1 = avg_x1 / len(cleaned)
                avg_x2 = avg_x2 / len(cleaned)
                rects[i] = (avg_x1, avg_y1, avg_x2, avg_y2)

                i += 1
        #统计一个用多少个Lanes
        temp=rects
        rects =self.change_the_block_dicts(rects)
        print("Num Parking Lanes: ", len(rects))

        # Step 5: 把列矩形画出来
        buff = 7
        for key in rects:
            tup_topLeft = (int(rects[key][0] - buff), int(rects[key][1]))
            tup_botRight = (int(rects[key][2] + buff), int(rects[key][3]))
            cv2.rectangle(new_image, tup_topLeft, tup_botRight, (0, 255, 0), 3)
        return new_image, rects



    def change_the_block_dicts(self,block_dict):
        block_dict[2]=[]
        for i in range(2,12):
            block_dict[i]=block_dict[i+1]
        block_dict[12]=None
        block_dict.pop(12)

        return block_dict

    # 微调这个图片
    def draw_parking(self, image, rects, make_copy=True, color=[255, 0, 0], thickness=2, save=True):
        if make_copy:
            new_image = np.copy(image)
        gap = 15.5  #每2个车位之间的距离设为gap,gap固定为15.5
        spot_dict = {}  # 字典：一个车位对应一个位置
        tot_spots = 0
        # 微调
        adj_y1 = {0: 20, 1: -10, 2: 0, 3: -11, 4: 28, 5: 5, 6: -15, 7: -15, 8: -10, 9: -30, 10: 9, 11: -32}
        adj_y2 = {0: 30, 1: 50, 2: 15, 3: 10, 4: -15, 5: 15, 6: 15, 7: -20, 8: 15, 9: 15, 10: 0, 11: 30}

        adj_x1 = {0: -8, 1: -15, 2: -15, 3: -15, 4: -15, 5: -15, 6: -15, 7: -15, 8: -10, 9: -10, 10: -10, 11: 0}
        adj_x2 = {0: 0, 1: 15, 2: 15, 3: 15, 4: 15, 5: 15, 6: 15, 7: 15, 8: 10, 9: 10, 10: 10, 11: 0}
        for key in rects:
            # 调整每个矩形的坐标，按照实际位置进行调整
            tup = rects[key]
            x1 = int(tup[0] + adj_x1[key])
            x2 = int(tup[2] + adj_x2[key])
            y1 = int(tup[1] + adj_y1[key])
            y2 = int(tup[3] + adj_y2[key])
            cv2.rectangle(new_image, (x1, y1), (x2, y2), (0, 255, 0), 2)

            # 统计一个有多少个gap间隔
            num_splits = int(abs(y2 - y1) // gap)

            for i in range(0, num_splits + 1):
                y = int(y1 + i * gap)
                #画一条直线
                cv2.line(new_image, (x1, y), (x2, y), color, thickness)

            #除了第一个和最后一个，都是有2排的，因此画一个中间线
            if key > 0 and key < len(rects) - 1:
                # 竖直线
                x = int((x1 + x2) / 2)
                cv2.line(new_image, (x, y1), (x, y2), color, thickness)

            # 计算数量，如果是第一个和最后一个，停车位总数+1
            if key == 0 or key == (len(rects) - 1):
                tot_spots += num_splits + 1
            # 其他排的停车位 都是2排的， 因此 *2
            else:
                tot_spots += 2 * (num_splits + 1)

            # 字典对应好

            if key == 0 or key == (len(rects) - 1):
                for i in range(0, num_splits + 1):
                    cur_len = len(spot_dict)
                    y = int(y1 + i * gap)
                    spot_dict[(x1, y, x2, y + gap)] = cur_len + 1
            else:
                for i in range(0, num_splits + 1):
                    cur_len = len(spot_dict)
                    y = int(y1 + i * gap)
                    x = int((x1 + x2) / 2)
                    #如果不是第1和最后，一般都要乘2
                    spot_dict[(x1, y, x, y + gap)] = cur_len + 1
                    spot_dict[(x, y, x2, y + gap)] = cur_len + 2

        print("total parking spaces: ", tot_spots, cur_len)
        if save:
            filename = 'with_parking.jpg'
            cv2.imwrite(filename, new_image)
        return new_image, spot_dict

    # 对任何一张输入图片进行划分
    def assign_spots_map(self,image, spot_dict, make_copy = True, color=[255, 0, 0], thickness=2):
        if make_copy:
            new_image = np.copy(image)
        for spot in spot_dict.keys():
            (x1, y1, x2, y2) = spot
            cv2.rectangle(new_image, (int(x1),int(y1)), (int(x2),int(y2)), color, thickness)
        return new_image

    # 获得cnn的训练图片，对划分好的图片进行切割
    def save_images_for_cnn(self, image, spot_dict, folder_name='cnn_data'):
        #创建这个文件夹
        if os.path.exists(folder_name):
            pass
        else:os.mkdir(folder_name)

        saved_image=0
        for spot in spot_dict.keys():
            (x1, y1, x2, y2) = spot
            (x1, y1, x2, y2) = (int(x1), int(y1), int(x2), int(y2))
            # 裁剪
            spot_img = image[y1:y2, x1:x2]
            # spot_image变成原来的2倍，方便输入网络
            spot_img = cv2.resize(spot_img, (0, 0), fx=2.0, fy=2.0)
            spot_id = spot_dict[spot]

            filename = 'spot' + str(spot_id) + '.jpg'
            print(spot_img.shape, filename, (x1, x2, y1, y2))

            cv2.imwrite(os.path.join(folder_name, filename), spot_img)
            saved_image=saved_image+1
            print("Finished{}/{}".format(saved_image,len(spot_dict)))

    #  做出预测，根据输入数据进行预测
    def make_prediction(self, image, model, class_dictionary):
        # 预处理
        img = image / 255.

        # 转换成4D tensor
        image = np.expand_dims(img, axis=0)

        # 用训练好的模型进行训练，输出一个 (None,2) 的结果
        class_predicted = model.predict(image)
        # 输出预测的结果
        inID = np.argmax(class_predicted[0])
        # 输出预测结果
        label = class_dictionary[inID]
        # 返回标签
        return label

    # 在图片上进行预测
    def predict_on_image(self, image, spot_dict, model, class_dictionary, make_copy=True, color=[0, 255, 0], alpha=0.5):
        # 是否copy iamge
        if make_copy:
            new_image = np.copy(image)
            overlay = np.copy(image)
        self.cv_show('new_image', new_image)
        # 统计有多少空车位
        cnt_empty = 0
        all_spots = 0
        # 提取每个spot并且进行resize成CNN的输入size
        for spot in spot_dict.keys():
            all_spots += 1
            (x1, y1, x2, y2) = spot
            (x1, y1, x2, y2) = (int(x1), int(y1), int(x2), int(y2))
            spot_img = image[y1:y2, x1:x2]
            spot_img = cv2.resize(spot_img, (48, 48))
            # 获得预测的 label
            label = self.make_prediction(spot_img, model, class_dictionary)
            # 如果  label = “empty"  证明为空着车位
            if label == 'empty':
                # 画出一个填充为绿色的矩形
                cv2.rectangle(overlay, (int(x1), int(y1)), (int(x2), int(y2)), color, -1)
                cnt_empty += 1
        # 二张图片进行一个融合
        cv2.addWeighted(overlay, alpha, new_image, 1 - alpha, 0, new_image)
        # 显示一共多少可以停的车位
        cv2.putText(new_image, "Available: %d spots" % cnt_empty, (30, 95),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.7, (255, 255, 255), 2)
        # 显示一个有多少车位
        cv2.putText(new_image, "Total: %d spots" % all_spots, (30, 125),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.7, (255, 255, 255), 2)
        cv2.imwrite("After_.png",new_image)
        save = True

        # 如果save的
        if save:
            filename = 'After_detected.jpg'
            cv2.imwrite(filename, new_image)
        self.cv_show('new_image', new_image)

        return new_image










