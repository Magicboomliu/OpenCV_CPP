__author__ = "Luke Liu"
#encoding="utf-8"

'''导入需要的第三方库文件'''
import  numpy as np
import cv2
import os

from myutils import sort_contours

# 正确答案 的dict
ANSWER_KEY = {0: 1, 1: 4, 2: 0, 3: 3, 4: 1}

# 展示阶段性结果
def cv_show(name, img):
    cv2.imshow(name, img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()



def Four_points_transform(image,pts):

    # 首先获得输入点的左边
    left_top,left_bootom,right_bottom,right_top = pts
    left_top=left_top[0]
    left_bootom=left_bootom[0]
    right_bottom=right_bottom[0]
    right_top=right_top[0]


    rect=np.array(pts).reshape(4,2)
    # 注意前后数据类型一致
    rect=np.float32(rect)




    # 获得需要进行变换的坐标
    witdhA = np.sqrt((left_top[0]-right_top[0])**2+ (left_top[1]-right_top[1])**2)
    witdhB = np.sqrt((left_bootom[0]-right_bottom[0])**2+ (left_bootom[1]-right_bottom[1])**2)
    # 选择最大的width
    if witdhA>witdhB:
        maxwidth=int(witdhA)
    else:maxwidth=int(witdhB)

    heightA = np.sqrt((left_top[0]-left_bootom[0])**2+ (left_top[1]-left_bootom[1])**2)
    heightB =np.sqrt((right_top[0]-right_bottom[0])**2+ (right_top[1]-right_bottom[1])**2)

    if heightA>heightB:
        maxheight=int(heightA)
    else:maxheight=int(heightB)


    # 变换之后的坐标

    # 变换后对应坐标位置
    dst = np.array([
        [0, 0],
        [0,maxheight-1],
        [maxwidth-1, maxheight-1],
        [maxwidth-1,0]], dtype="float32")


    # 计算变换矩阵
    M = cv2.getPerspectiveTransform(rect, dst)
    warped = cv2.warpPerspective(image, M, (maxwidth, maxheight))

    # 返回变换后结果
    return warped


# 图片处理
def process_the_image(image):
    # 首先是预处理，包括灰度图片，高斯滤波和Canny边缘提取
    contours_img = image.copy()
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)
    # cv_show('blurred', blurred)
    edged = cv2.Canny(blurred, 75, 200)
    # cv_show('edged', edged)

    # 轮廓检测，检测外轮廓
    cnts = cv2.findContours(edged.copy(), cv2.RETR_EXTERNAL,
                            cv2.CHAIN_APPROX_SIMPLE)[1]
    #轮廓画图
    cv2.drawContours(contours_img, cnts, -1, (0, 0, 255), 3)
    # cv_show('contours_img', contours_img)

    docCnt = None

     # 外轮廓不一定是一个矩形，根据轮廓面积排序
    # 确保检测到了最外围的四大点作为矩形，
    if len(cnts) > 0:
        # 根据轮廓大小进行排序
        cnts = sorted(cnts, key=cv2.contourArea, reverse=True)

        # 遍历每一个轮廓
        for c in cnts:
            # 多边形近似
            peri = cv2.arcLength(c, True)
            approx = cv2.approxPolyDP(c, 0.02 * peri, True)

            # 准备做透视变换，确保是一个矩形
            if len(approx) == 4:
                docCnt = approx
                break
    # print(docCnt.shape)  # shape is (4,1,2)
    '''docCnt 进行坐标变换'''
    warped = Four_points_transform(gray, docCnt)
    # cv_show('warped', warped)

    warped_copy =warped.copy()

    '''  提取圆形的轮廓   '''

    # 对变换后的图像进行Ostu阈值处理

    ret,thresh = cv2.threshold(warped, 0, 255,
                           cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)
    # cv_show('thresh', thresh)
    # 二值的轮廓
    thresh_Contours = thresh.copy()

    # 进行轮廓检查
    cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
                            cv2.CHAIN_APPROX_SIMPLE)[1]
    cv2.drawContours(thresh_Contours, cnts, -1, (0, 255, 0), 3)
    # cv_show('thresh_Contours', thresh_Contours)

    questionCnts = []

    # 遍历,得到自己想要的轮廓信息信息，放在quesetionCnts中
    for c in cnts:
        # 计算比例和大小
        (x, y, w, h) = cv2.boundingRect(c)
        ar = w / float(h)

        # 根据实际情况指定标准，提取比较大的轮廓，长宽比在0.9到1.1
        if w >= 20 and h >= 20 and ar >= 0.9 and ar <= 1.1:
            questionCnts.append(c)

    # 显示自己要提取的部分轮廓
    cv2.drawContours(warped_copy, questionCnts, -1, (0, 255, 0), 3)
    # cv_show('circles', warped_copy)
    print(len(questionCnts))

    # 将提取出来的轮廓按照空间顺序进行排序
    # 按照从上到下进行排序
    questionCnts = sort_contours(questionCnts,
                                 method="top-to-bottom")[0]
    correct = 0

    # 每排有5个选项，q代表第几行，i=0,i=5,i=10,i=15,i=20
    for (q, i) in enumerate(np.arange(0, len(questionCnts), 5)):
        # 排序，默认从左向右排序
        cnts = sort_contours(questionCnts[i:i + 5])[0]
        # 学生选择的那个的非零的值应该是最大的
        student_seleted = None


        # 遍历每一个结果
        for (j, c) in enumerate(cnts):
            # 使用mask来判断结果
            mask = np.zeros(thresh.shape, dtype="uint8")
            cv2.drawContours(mask, [c], -1, 255, -1)  # 最后一个-1表示填充
            # cv_show('mask', mask)
            # 通过计算非零点数量来算是否选择这个答案,被涂抹的那个零点个数一定是最多的
            mask = cv2.bitwise_and(thresh, thresh, mask=mask)
            # 统计此时的非零点的个数
            total = cv2.countNonZero(mask)
        # 通过阈值判断
            if student_seleted is None or total > student_seleted[0]:
                # 记录此时最大的total,并且此时的位置 j 代表学生选的那个选项
                student_seleted = (total, j)

        # 正确的答案
        color = (0, 0, 255)
        correct_answer = ANSWER_KEY[q]
        if student_seleted[1]==correct_answer:
            color = (0, 255, 0)
            correct=correct+1

        # 把真正的答案画出来绘图
        cv2.drawContours(warped, [cnts[correct_answer]], -1, color, 3)

    #计算机最后的得分
    score = (correct / 5.0) * 100
    print("[INFO] score: {:.2f}%".format(score))
    cv2.putText(warped, "{:.2f}%".format(score), (10, 30),
                cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 0, 255), 2)
    cv2.imshow("Original", image)
    cv2.imshow("Exam", warped)
    cv2.waitKey(0)











# 执行的库文件
if __name__ == '__main__':
    images = [cv2.imread(os.path.join("images",f)) for f in os.listdir("images")]
    process_the_image(images[1])

