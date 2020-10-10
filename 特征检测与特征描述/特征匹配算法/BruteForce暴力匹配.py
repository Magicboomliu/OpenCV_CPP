__author__ = "Luke Liu"
#encoding="utf-8"
import  cv2
import matplotlib.pyplot as plt
import  numpy as np


img1 = cv2.imread("1.jpg")
img2 = cv2.imread("2.jpg")
gray1 =cv2.cvtColor(img1,cv2.COLOR_BGR2GRAY)
gray2 =cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)

orb=cv2.ORB_create(nfeatures=100)

kp1,des1=orb.detectAndCompute(img1,None)
kp2,des2=orb.detectAndCompute(img2,None)
#
# ret1 = cv2.drawKeypoints(gray1,kp1,img1,255,4)
# ret2 =cv2.drawKeypoints(gray2,kp2,img2,255,4)
# plt.imshow(img1)
# plt.imshow(img2)
# plt.show()


# 使用hamming距离，开启交叉认证
bf=cv2.BFMatcher_create(normType=cv2.NORM_HAMMING2,crossCheck=True)
#返回一个Dmatch列表
matches=bf.match(des1,des2)

#点的idx
queryIdx = [m.queryIdx for m in matches ]
trainIdx = [m.trainIdx for m in matches]
scoresIdx =[m.distance for m in matches]
print(len(queryIdx))
print(len(trainIdx))


matches =sorted(matches,key=lambda x:x.distance)

ret= cv2.drawMatches(img1,kp1,img2,kp2,matches[:10],None,flags=2)

plt.imshow(ret)
plt.axis("off")
plt.show()
