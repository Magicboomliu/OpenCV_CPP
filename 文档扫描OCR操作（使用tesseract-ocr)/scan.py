__author__ = "Luke Liu"
#encoding="utf-8"

# 导入工具包
import numpy as np
import cv2
import os

'''读取要操作的图片'''
def get_the_test_images():
    imageslist=os.listdir("images")
    imageslist=[os.path.join("images",f) for f in imageslist]
    return imageslist

# 绘图展示
def cv_show(name,img):
	cv2.imshow(name, img)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

'''定义一个resize函数，resize图片大小'''
def resize(image, width=None, height=None, inter=cv2.INTER_AREA):
	dim = None
	(h, w) = image.shape[:2]
	if width is None and height is None:
		return image
	if width is None:
		r = height / float(h)
		dim = (int(w * r), height)
	else:
		r = width / float(w)
		dim = (width, int(h * r))
	resized = cv2.resize(image, dim, interpolation=inter)
	return resized

def four_points_tranform(image,pts):
    ''' Get four points'''
    rect=np.zeros((4,2), dtype=np.float32)

    left_top,left_bottom,right_bottom,right_top= pts
    left_top=left_top[0]
    left_bottom=left_bottom[0]
    right_bottom=right_bottom[0]
    right_top=right_top[0]

    rect[0]=left_top
    rect[1]=left_bottom
    rect[2]=right_bottom
    rect[3]=right_top

    #求高和宽
    widthA = np.sqrt(((right_top[0] - left_top[0]) ** 2)+((right_top[1] - left_top[1]) ** 2))
    widthB = np.sqrt(((right_bottom[0] - left_bottom[0]) ** 2)+((right_bottom[1] - left_bottom[1]) ** 2))
    if widthA>=widthB:
        maxWith=widthA
    else:maxWith=widthB

    heightA = np.sqrt(((right_top[0] - right_bottom[0]) ** 2) + ((right_top[1] - right_bottom[1]) ** 2))
    heightB = np.sqrt(((left_top[0] - left_bottom[0]) ** 2) + ((left_top[1] - left_bottom[1]) ** 2))
    if heightA >= heightB:
        maxheight=heightA
    else:
        maxheight = heightB

    # 转换后对应的点坐标
    dst = np.array([
        [0, 0],
        [0, maxheight - 1],
        [maxWith - 1, maxheight - 1],
        [maxWith - 1, 0]],
        dtype=np.float32)



    # 计算变换矩阵
    M = cv2.getPerspectiveTransform(rect, dst)
    print("OK")
    warped = cv2.warpPerspective(image, M, (int(maxWith),int(maxheight)))

    # 返回变换后结果
    return warped

# 提取目标图片的外轮廓
def Extract_the_Eadge(image):
    # 记录图像大小resize前的比率，坐标也会相同变化
    ratio = image.shape[0] / 500.0
    orig = image.copy()
    image = resize(orig, height=500)
    # 预处理, 变灰度  ->  高斯滤波 -> Canny边缘提取
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (5, 5), 0)
    edged = cv2.Canny(gray, 75, 200)

    # 展示预处理结果
    print("STEP 1: 边缘检测")
    cv_show("resized Image",image)
    cv_show("Canny eagde",edged)

    # 轮廓检测,按照最大面积进行排序，要前5个
    _,cnts,_ = cv2.findContours(edged.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
    '''
    contour：带有轮廓信息的图像；
    cv2.RETR_TREE：提取轮廓后，输出轮廓信息的组织形式，除了cv2.RETR_TREE还有以下几种选项：
    cv2.RETR_EXTERNAL：输出轮廓中只有外侧轮廓信息；
    cv2.RETR_LIST：以列表形式输出轮廓信息，各轮廓之间无等级关系；
    cv2.RETR_CCOMP：输出两层轮廓信息，即内外两个边界（下面将会说到contours的数据结构）；
    cv2.RETR_TREE：以树形结构输出轮廓信息。
    cv2.CHAIN_APPROX_SIMPLE：指定轮廓的近似办法，有以下选项：
    cv2.CHAIN_APPROX_NONE：存储轮廓所有点的信息，相邻两个轮廓点在图象上也是相邻的；
    cv2.CHAIN_APPROX_SIMPLE：压缩水平方向，垂直方向，对角线方向的元素，只保留该方向的终点坐标；
    cv2.CHAIN_APPROX_TC89_L1：使用teh-Chinl chain 近似算法保存轮廓信息。
    '''
    cnts = sorted(cnts, key=cv2.contourArea, reverse=True)[:5]
    # 遍历轮廓
    for c in cnts:
        # 计算轮廓近似周长peri
        peri = cv2.arcLength(c, True)
        # C表示输入的点集
        # epsilon表示从原始轮廓到近似轮廓的最大距离，它是一个准确度参数,度量值
        # True表示封闭的
        #返回值是一个数组
        approx = cv2.approxPolyDP(c, 0.02 * peri, True)


        # 4个点的时候就拿出来
        if len(approx) == 4:
            screenCnt = approx

            ''' screenCnt points order is:
              0.left-top
              1.left-bottom
              2.right-bottom
              3.right-top
              '''
            break
        # 展示结果
    print("STEP 2: 获取轮廓")
    cv2.drawContours(image, [screenCnt], -1, (0, 255, 0), 2)
    cv_show("Outline",image)

    # 透视变换
    warped = four_points_tranform(orig, screenCnt*ratio)
    # 二值处理
    warped = cv2.cvtColor(warped, cv2.COLOR_BGR2GRAY)
    ref = cv2.threshold(warped, 100, 255, cv2.THRESH_BINARY)[1]
    cv2.imwrite('scan.jpg', ref)
    # 展示结果
    print("STEP 3: 变换")
    cv_show("Scaaned",resize(ref,height=650))



if __name__ == '__main__':
    '''读取图片'''
    imagelist= get_the_test_images()
    page_image,recipt_image = imagelist[:2]
    page_image=cv2.imread(page_image)
    recipt_image=cv2.imread(recipt_image)
    # cv_show("page Orgin",page_image)
    '''提取图片的边缘'''
    Extract_the_Eadge(recipt_image)
