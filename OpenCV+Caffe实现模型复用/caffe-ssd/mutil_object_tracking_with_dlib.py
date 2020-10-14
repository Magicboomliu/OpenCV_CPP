__author__ = "Luke Liu"
#encoding="utf-8"
import dlib
import cv2
import numpy as np

''' 注意 dlib 的每一个tracker 只能track一个object '''
# SSD标签
CLASSES = ["background", "aeroplane", "bicycle", "bird", "boat",
	"bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
	"dog", "horse", "motorbike", "person", "pottedplant", "sheep",
	"sofa", "train", "tvmonitor"]
# 读取caffe网络模型结构文件
def read_caffeNet_structure_and_weights(caffeNet_structure_path,model_weights_path):
    '''
    :param caffeNet_structure_path: .prototxt  file 
    :param model_weights_path: .caffemodel file
    :return: 
    '''
    # 读取了网络的结构以及权重
    net = cv2.dnn.readNetFromCaffe(caffeNet_structure_path,
                                   model_weights_path)
    return net

# 图像预处理
def imagePreprocessing(image_data):
    # 预处理操作,获得高和宽
    (h, w) = image_data.shape[:2]
    # 设置宽度的长度是600
    width = 600
    # 确定要缩放的比例
    r = width / float(w)
    # 获得等比缩放的宽和高
    dim = (width, int(h * r))
    # resize 图片
    frame = cv2.resize(image_data, dim, interpolation=cv2.INTER_AREA)
    # 获得灰度的图片
    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    return rgb

# initialize the first frame
def Image_detect_test(rgb_image,net,confidence=0.5):

    # 输入caffe-ssd 获得forward 点的结果，并且查看detection的shape
    h, w = rgb_image.shape[:2]
    blobs = cv2.dnn.blobFromImage(rgb_image, 0.007843, (w, h), 127.5)

    net.setInput(blobs)

    detections = net.forward()

    # caffe 的最后一层输出为[1,1,x,7]
    # 其中x是最后保留的框的个数，最后一维存放的数据为：
    # [image_id, label_id, confidence, xmin, ymin, xmax, ymax]
    # 遍历每一个结果
    for i in np.arange(0, detections.shape[2]):
        cur_confidence = detections[0, 0, i, 2]

        if cur_confidence > confidence:
            label_id = detections[0, 0, i, 1]
            label = CLASSES[int(label_id)]
            if label == "person":
                box = detections[0, 0, i, 3:7] * np.array([w, h, w, h])
                (startX, startY, endX, endY) = box.astype("int")

                return (startX, startY, endX, endY),rgb_image

# Video 视频追踪
def VideoTrack_with_dilb(VideoPath,net,confidence,saved):

    cap =cv2.VideoCapture(VideoPath)
    # 注意 dlib 的每一个tracker 只能track一个object
    trackers=[]


    while True:
        ret, frame =cap.read()

        if frame is not None:
            rgb_image = imagePreprocessing(frame)
            # 目前没有物体，进行检测
            if len(trackers)==0:
                (startX, startY, endX, endY), rgb_image= Image_detect_test(rgb_image,net,confidence=confidence)

                if saved == True:
                    fourcc = cv2.VideoWriter_fourcc(*"MJPG")
                    writer = cv2.VideoWriter("dlib_outcome.avi", fourcc, 30,
                                             (rgb_image.shape[1], rgb_image.shape[0]), True)
                # 使用dlib来进行目标追踪
                # http://dlib.net/python/index.html#dlib.correlation_tracker
                t = dlib.correlation_tracker()
                rect = dlib.rectangle(int(startX), int(startY), int(endX), int(endY))
                t.start_track(rgb_image, rect)
                # 保存结果
                # 绘图
                cv2.rectangle(rgb_image, (startX, startY), (endX, endY),
                              (0, 255, 0), 2)
                # 添加tracker
                trackers.append(t)

            # 如果已经有了框，就可以直接追踪了
            else:
                # 每一个追踪器都要进行更新
                for t in trackers:
                    t.update(rgb_image)
                    pos = t.get_position()

                    # 得到位置
                    startX = int(pos.left())
                    startY = int(pos.top())
                    endX = int(pos.right())
                    endY = int(pos.bottom())

                    # 画出来
                    cv2.rectangle(rgb_image, (startX, startY), (endX, endY),
                                  (0, 255, 0), 2)
                    cv2.putText(rgb_image,"Bolt",(startX, startY - 15),
				cv2.FONT_HERSHEY_SIMPLEX, 0.45, (0, 255, 0), 2)

            # 保存
            if saved:
                writer.write(rgb_image)


            # 显示
            cv2.imshow("Outcome", rgb_image)
            key = cv2.waitKey(1) & 0xFF

            # 退出
            if key == 27:
                break
        else:
            cap.release()
            cv2.destroyAllWindows()
            break



if __name__ == '__main__':
    # read the net
    # 读取网络
    net = read_caffeNet_structure_and_weights("mobilenet_ssd/MobileNetSSD_deploy.prototxt",
                                              "mobilenet_ssd/MobileNetSSD_deploy.caffemodel")
    VideoTrack_with_dilb("race.mp4",net=net,confidence=0.2,saved=True)






