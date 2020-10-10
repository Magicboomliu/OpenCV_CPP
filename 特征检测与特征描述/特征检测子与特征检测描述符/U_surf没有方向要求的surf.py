__author__ = "Luke Liu"
#encoding="utf-8"

import matplotlib.pyplot as plt
import cv2
import numpy as np
import  os
import glob

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

# Hessian Threshold is 400,提高Hessian的阈值可以减少kp的个数
surf =cv2.xfeatures2d.SURF_create(5000,upright=True,extended=True)

# Check upright flag, if it False, set it to True
# Recompute the feature points and draw it
kp = surf.detect(img,None)
img2 = cv2.drawKeypoints(img,kp,None,(255,0,0),4)

plt.imshow(img2)
plt.show()