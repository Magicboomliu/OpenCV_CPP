__author__ = "Luke Liu"
#encoding="utf-8"

'''Oriented Fast and Rotated BRIEF'''


import cv2
import numpy as np
import glob
import matplotlib.pyplot as plt
import os

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


orb= cv2.ORB_create(nfeatures=100,WTA_K=3)
# 获得orb描述子
kp = orb.detect(gray,None)
#获得特征描述子
kp,des= orb.compute(gray,kp)

img2 = cv2.drawKeypoints(gray,kp,img,255,4)

plt.imshow(img2)
plt.show()


