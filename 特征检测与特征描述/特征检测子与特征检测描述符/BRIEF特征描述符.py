__author__ = "Luke Liu"
#encoding="utf-8"

import cv2
import numpy as np
import os
import glob
import matplotlib.pyplot as plt

# 读取图片
extensions=['jpg','png']
image_list=[]
for extension in extensions:
    file_glob=os.path.join("images",'*.'+extension)
    f = glob.glob(file_glob)
    image_list.extend(f)

# 提取SURF描述子
img =cv2.imread(image_list[0])
gray=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

#使用Fast提取Features points,使用BRIEF进行描述子的计算

fast=cv2.FastFeatureDetector_create(threshold=50,nonmaxSuppression=True,
                                    type=cv2.FAST_FEATURE_DETECTOR_TYPE_7_12)

kp = fast.detect(gray,None)

#建立brief描述子
brief = cv2.xfeatures2d.BriefDescriptorExtractor_create()

des = brief.compute(gray,kp)


img3 = cv2.drawKeypoints(gray,kp,img)

plt.imshow(img)
plt.show()