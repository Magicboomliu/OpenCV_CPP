__author__ = "Luke Liu"
#encoding="utf-8"
import cv2
import numpy as np
import os
import  glob

# 读取图片
extensions=['jpg','png']
image_list=[]
for extension in extensions:
    file_glob=os.path.join("images",'*.'+extension)
    f = glob.glob(file_glob)
    image_list.extend(f)

#开始harris检测
img =cv2.imread(image_list[0])
gray=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
dst= np.float32(gray)

mdst =cv2.cornerHarris(dst,3,5,0.04)


mdst = cv2.dilate(mdst,None)
# 大于最大值的0.1认为是harris焦点
img[mdst>0.1*mdst.max()]=[0,0,255]
cv2.imshow('dst',img)


if cv2.waitKey(0) & 0xff == 27:
    cv2.destroyAllWindows()



