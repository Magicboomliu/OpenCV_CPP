__author__ = "Luke Liu"
#encoding="utf-8"

# 导入工具包
import numpy as np
import argparse
import cv2
import os
import myutils

# 绘图展示
def cv_show(name,img):
	cv2.imshow(name, img)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

# 指定信用卡类型
FIRST_NUMBER = {
	"3": "American Express",
	"4": "Visa",
	"5": "MasterCard",
	"6": "Discover Card"
}

# 获取信用卡和模板图片
def get_images_data():
    images = os.listdir('./images')
    credits_cards_list = images[:5]
    credits_cards_list=[os.path.join("images",f) for f in credits_cards_list]
    template_ref = images[-1]
    template_ref=os.path.join('images',template_ref)
    return credits_cards_list,template_ref

#处理模板图像
def process_the_template(template_ref):
    # 读取图片
    template_ref_image =cv2.imread(template_ref)
    #  转化为灰度图片
    template_ref_gray= cv2.cvtColor(template_ref_image,cv2.COLOR_BGR2GRAY)
    # 二值图像
    ret,ref = cv2.threshold(template_ref_gray, 10, 255, cv2.THRESH_BINARY_INV)
    # cv_show('ref', ref)

    # 计算轮廓
    # cv2.findContours()函数接受的参数为二值图，即黑白的（不是灰度图）,cv2.RETR_EXTERNAL只检测外轮廓，cv2.CHAIN_APPROX_SIMPLE只保留终点坐标
    # 返回的list中每个元素都是图像中的一个轮廓

    #获得维度的轮廓
    ref_, refCnts, hierarchy = cv2.findContours(ref.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    cv2.drawContours(template_ref_image, refCnts, -1, (0, 0, 255), 3)
    # cv_show('ref_with_refCnts',template_ref_image)

    #一共有10个外轮廓
    print("Contours Mount of the ref is ",np.array(refCnts).shape[0])
    # 对轮廓进行排序，从左到右，从上到下
    refCnts = myutils.sort_contours(refCnts, method="left-to-right")[0]

    ref_dict={}

    # 遍历每一个轮廓,0,1,2,3,4,5,6,7,8,9,进行resize，提取ROI
    for (i, c) in enumerate(refCnts):
        # 计算外接矩形并且resize成合适大小
        (x, y, w, h) = cv2.boundingRect(c)
        roi = ref[y:y + h, x:x + w]
        roi = cv2.resize(roi, (57, 88))
        # 每一个数字对应每一个模板
        ref_dict[i] = roi

    return  ref_dict

def process_the_target_image(srcImage,ref_dict):

    # 初始化卷积核
    rectKernel = cv2.getStructuringElement(cv2.MORPH_RECT, (9, 3))
    sqKernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))

    # 读取输入图像，预处理
    image = cv2.imread(srcImage)
    # cv_show('image', image)
    image = myutils.resize(image, width=300)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    # cv_show('gray', gray)

    # 礼帽操作，突出更明亮的区域
    tophat = cv2.morphologyEx(gray, cv2.MORPH_TOPHAT, rectKernel)
    # cv_show('tophat', tophat)

    # 计算X方向的梯度，突出edage
    gradX = cv2.Sobel(tophat, ddepth=cv2.CV_32F, dx=1, dy=0,  # ksize=-1相当于用3*3的
                      ksize=-1)
    #对梯度进行归一化操作
    gradX = np.absolute(gradX)
    (minVal, maxVal) = (np.min(gradX), np.max(gradX))
    gradX = (255 * ((gradX - minVal) / (maxVal - minVal)))
    gradX = gradX.astype("uint8")

    print(np.array(gradX).shape)
    # cv_show('gradX', gradX)

    # 通过闭操作（先膨胀，再腐蚀）将数字连在一起
    gradX = cv2.morphologyEx(gradX, cv2.MORPH_CLOSE, rectKernel)
    # cv_show('gradX', gradX)
    # THRESH_OTSU会自动寻找合适的阈值，适合双峰，需把阈值参数设置为0
    thresh = cv2.threshold(gradX, 0, 255,
                           cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
    # cv_show('thresh', thresh)

    # 再来一个闭操作


    thresh = cv2.morphologyEx(thresh, cv2.MORPH_CLOSE, sqKernel)  # 再来一个闭操作
    # cv_show('thresh2', thresh)

    # 计算轮廓

    thresh_, threshCnts, hierarchy = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
                                                      cv2.CHAIN_APPROX_SIMPLE)
    cnts = threshCnts
    cur_img = image.copy()
    cv2.drawContours(cur_img, cnts, -1, (0, 0, 255), 3)
    # cv_show('img', cur_img)
    locs = []

    # 遍历轮廓
    for (i, c) in enumerate(cnts):
        # 计算外接矩形
        (x, y, w, h) = cv2.boundingRect(c)
        #计算长宽比
        ar = w / float(h)

        # 选择合适的区域，根据实际任务来，这里的基本都是四个数字一组
        #比较长宽比
        if ar > 2.5 and ar < 4.0:
            #比较w,h具体长度
            if (w > 40 and w < 55) and (h > 10 and h < 20):
                # 符合的留下来
                locs.append((x, y, w, h))
    print(len(locs))

    # 将符合的轮廓从左到右排序,空间顺序
    locs = sorted(locs, key=lambda x: x[0])

    #展示一下结果
    my_curImage = image.copy()
    for boudingbox in locs:
        cv2.rectangle(my_curImage,(boudingbox[0],boudingbox[1]),(boudingbox[0]+boudingbox[2],boudingbox[1]+boudingbox[3]),
                      (0,0,255),2)
    # cv_show("rect",my_curImage)


    '''提取每个boundingbox的图片信息'''
    output=[]
    # 遍历每一个轮廓中的数字
    for (i, (gX, gY, gW, gH)) in enumerate(locs):
        # initialize the list of group digits
        groupOutput = []

        # 根据坐标提取每一个组
        # 稍微扩充一下这个roi
        group = gray[gY - 5:gY + gH + 5, gX - 5:gX + gW + 5]
        # cv_show('group', group)
        # 预处理,OTSU阈值化
        ret,group = cv2.threshold(group, 0, 255,
                              cv2.THRESH_BINARY | cv2.THRESH_OTSU)
        # cv_show('group', group)
        # 计算每一组的轮廓
        group_, digitCnts, hierarchy = cv2.findContours(group.copy(), cv2.RETR_EXTERNAL,
                                                        cv2.CHAIN_APPROX_SIMPLE)
        #对轮廓进行空间排序
        digitCnts = myutils.sort_contours(digitCnts,
                                           method="left-to-right")[0]
        #显示这个轮廓
        # mygroup=group.copy()
        # cv2.drawContours(mygroup, digitCnts, -1, (0, 0, 255), 3)
        # cv_show("group_contours",mygroup)

        # 计算每一组中的每一个数值
        for c in digitCnts:
            # 找到当前数值的轮廓，resize成合适的的大小
            (x, y, w, h) = cv2.boundingRect(c)
            roi = group[y:y + h, x:x + w]
            roi = cv2.resize(roi, (57, 88))
            # cv_show('roi', roi)

            # 计算匹配得分
            scores = []

            # 在模板中计算每一个得分
            for (digit, digitROI) in ref_dict.items():
                # 模板匹配
                '''
                cv2.TM_CCOEFF （系数匹配法）
                cv2.TM_CCOEFF_NORMED（相关系数匹配法）
                cv2.TM_CCORR （相关匹配法）
                cv2.TM_CCORR_NORMED （归一化相关匹配法）
                cv2.TM_SQDIFF （平方差匹配法）
                cv2.TM_SQDIFF_NORMED （归一化平方差匹配法
                '''
                result = cv2.matchTemplate(roi, digitROI,
                                           cv2.TM_CCOEFF)

                #根据 匹配方法不同，选择最大还是最小
                (minval, maxval, minloc,maxloc) = cv2.minMaxLoc(result)
                scores.append(maxval)

            # 得到最合适的数字
            groupOutput.append(str(np.argmax(scores)))

            # 画出来
        cv2.rectangle(image, (gX - 5, gY - 5),
                          (gX + gW + 5, gY + gH + 5), (0, 0, 255), 1)
        cv2.putText(image, "".join(groupOutput), (gX, gY - 15),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.65, (0, 0, 255), 2)

        # 得到结果
        output.extend(groupOutput)

    cv_show("img",image)
    return output



if __name__ == '__main__':

    # load the image and the template ref
    credits_cards_list,template_ref=get_images_data()

    # show the orginal srcImage
    cv_show("orginal srcImage",cv2.imread(credits_cards_list[0]))

    # preprocess the template and spilt to certain size image ROIs
    ref_dict= process_the_template(template_ref)

    # preprocess the srcImage, and do template match with template
    output = process_the_target_image(credits_cards_list[0],ref_dict)

    # print the OCR outcome
    print("Credit_card Number is :","".join(output))









