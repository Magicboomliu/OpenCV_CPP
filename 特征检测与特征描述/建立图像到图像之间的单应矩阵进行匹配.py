__author__ = "Luke Liu"
#encoding="utf-8"
import  cv2
import os
import matplotlib.pyplot as plt
import numpy as np

#按照scale调整图片的大小的一个函数
def resize_the_image(src,scale):
    h,w= src.shape[:2]
    if scale>0:
        out = cv2.resize(src,(int(scale*w),int(scale*h)))
        return out
    else:return src

# SET SOME GLOBAL VARIABLES
MIN_MATCH_MOUNTS=10

'''Load the Image'''
queryImage =cv2.imread("./images/1.jpg")
gray_query = cv2.cvtColor(queryImage,cv2.COLOR_BGR2GRAY)
gray_query =resize_the_image(gray_query,0.4)

srcImage =cv2.imread("./images/2.jpg")
gray_src=cv2.cvtColor(srcImage,cv2.COLOR_BGR2GRAY)
gray_src=resize_the_image(gray_src ,0.4)

''' Get the matches points'''
sift =cv2.xfeatures2d.SIFT_create(nfeatures=100)
kp1,des1 = sift.detectAndCompute(gray_query,None)
kp2,des2 =sift.detectAndCompute(gray_src,None)

FLANN_INDEX_KDTREE=5
index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
search_params = dict(checks=50) # or pass empty dictionary
flann = cv2.FlannBasedMatcher(index_params,search_params)
matches = flann.knnMatch(des1,des2,k=2)

# store all the good matches as per Lowe's ratio test.
good = []
for m,n in matches:
    if m.distance < 0.7*n.distance:
        good.append(m)

#Get 56 matches
if len(good)<MIN_MATCH_MOUNTS:
    print("Can not match")

else:
    src_pts = np.float32([kp1[m.queryIdx].pt for m in good]).reshape(-1, 1, 2)
    dst_pts = np.float32([kp2[m.trainIdx].pt for m in good]).reshape(-1, 1, 2)

    H,mask=cv2.findHomography(src_pts,dst_pts,cv2.RANSAC,5.0)

    imgout=cv2.warpPerspective(gray_query,H,(gray_src.shape[1],gray_src.shape[0]))

    cv2.imshow("queryImage",gray_query)
    cv2.imshow("SrcImage",gray_src)
    cv2.imshow("outImage",imgout)

    cv2.waitKey(0)
    cv2.destroyAllWindows()



