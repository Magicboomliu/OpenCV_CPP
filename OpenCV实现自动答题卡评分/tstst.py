__author__ = "Luke Liu"
#encoding="utf-8"
import numpy as np
import cv2

img = cv2.imread("images/test_01.png",0)
height,width = img.shape[:2]


mask =np.zeros(img.shape,dtype='uint8')
mask[100:500,300:400] = 255

after_mask = cv2.bitwise_and(img,img,mask=mask)
# total 非零点的个数
total = cv2.countNonZero(after_mask)
print(total)
cv2.imshow("",after_mask)

cv2.waitKey(0)
cv2.destroyAllWindows()