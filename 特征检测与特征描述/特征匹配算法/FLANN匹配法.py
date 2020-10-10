__author__ = "Luke Liu"
#encoding="utf-8"

''' 使用SIFT进行检测，使用FLANN进行特征点匹配'''
import  cv2
import matplotlib.pyplot as plt
import  numpy as np

'''Load the Image'''
img1 = cv2.imread("1.jpg")
img2 = cv2.imread("2.jpg")
gray1 =cv2.cvtColor(img1,cv2.COLOR_BGR2GRAY)
gray2 =cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)

'''Extract the SIFT points and descriptors'''
sift =cv2.xfeatures2d.SIFT_create(nfeatures=100)
kp1,des1 = sift.detectAndCompute(gray1,None)
kp2,des2 =sift.detectAndCompute(gray2,None)


''' Set configs dict for FLANN'''

# FLANN parameters
FLANN_INDEX_KDTREE = 0
index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
search_params = dict(checks=50) # or pass empty dictionary
flann = cv2.FlannBasedMatcher(index_params,search_params)
matches = flann.knnMatch(des1,des2,k=2)

''' Select Points and Confront a Mask'''
# Need to draw only good matches, so create a mask
matchesMask = [[0,0] for i in range(len(matches))]
# ratio test as per Lowe's paper
for i,(m,n) in enumerate(matches):
    if m.distance < 0.7*n.distance:
        matchesMask[i]=[1,0]

draw_params = dict(matchColor = (0,255,0),
                  singlePointColor = (255,0,0),
                   matchesMask = matchesMask,
                flags = 2)

img3 = cv2.drawMatchesKnn(img1,kp1,img2,kp2,matches,None,**draw_params)
plt.imshow(img3)
plt.axis("off")
plt.show()

