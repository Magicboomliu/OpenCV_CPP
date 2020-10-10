__author__ = "Luke Liu"
#encoding="utf-8"

import cv2
import numpy as np
import  os
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

#建立图像Fast角点检测与描述子,是否开启非极大值抑制,邻域的大小
fast = cv2.FastFeatureDetector_create(threshold=100,nonmaxSuppression=True,type=
                                      cv2.FAST_FEATURE_DETECTOR_TYPE_5_8)
kp=fast.detect(gray,None)

img2 = cv2.drawKeypoints(gray,kp,img)

plt.imshow(img2)
plt.show()
