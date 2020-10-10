__author__ = "Luke Liu"
#encoding="utf-8"

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
surf =cv2.xfeatures2d.SURF_create(5000)

# 检测kp关键点，并且得到描述子
kp =surf.detect(gray,None)
kp,des=surf.compute(gray,kp)
#获取kp点的x,y坐标
print(kp[0].pt)
# kp,des = surf.detectAndCompute(gray,None)

ret = cv2.drawKeypoints(gray,kp,img)

cv2.imshow("",img)

cv2.waitKey(0)
cv2.destroyAllWindows()
