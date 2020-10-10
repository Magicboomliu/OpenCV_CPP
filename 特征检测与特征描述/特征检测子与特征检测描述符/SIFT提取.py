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



img = cv2.imread(image_list[0])
gray= cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

# 图像特征点提取器
sift = cv2.xfeatures2d.SIFT_create()
keypoints = sift.detect(gray,None)

#画出这些特征点
ret = cv2.drawKeypoints(gray,keypoints,img)
#获得关键点与特征描述子
kp1,des1 =sift.compute(gray,keypoints)
cv2.imshow("",img)

cv2.waitKey(0)
cv2.destroyAllWindows()








