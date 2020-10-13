__author__ = "Luke Liu"
#encoding="utf-8"
'''

OpenCV provides all these in a single function, cv2.calcOpticalFlowPyrLK(). 
Here, we create a simple application which tracks some points in a video.
 To decide the points, we use cv2.goodFeaturesToTrack().
  We take the first frame, detect some Shi-Tomasi corner points in it, 
  then we iteratively track those points using Lucas-Kanade optical flow. 
  For the function cv2.calcOpticalFlowPyrLK() 
  we pass the previous frame, previous points and next frame. 
  It returns next points along with some status numbers 
  which has a value of 1 if next point is found, else zero. 
  We iteratively pass these next points as previous points in next step. 
  See the code below:

'''

import cv2
import numpy as np

cap = cv2.VideoCapture('test.avi')
# 首先进行 Shi-Tomasi 角点检测，用这些点（可逆，特征值大）进行光流估计
# params for ShiTomasi corner detection
feature_params = dict( maxCorners = 100,
                       qualityLevel = 0.3,
                       minDistance = 7,
                       blockSize = 7 )

# Parameters for lucas kanade optical flow
lk_params = dict( winSize  = (15,15), #滑动串口大小
                  maxLevel = 2,
                  criteria = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03))

# 给一个随机的颜色
# Create some random colors
color = np.random.randint(0,255,(100,3))
# 对第一帧进行焦点检测，确定要追踪什么焦点
ret, old_frame = cap.read()
old_gray = cv2.cvtColor(old_frame, cv2.COLOR_BGR2GRAY)

# To decide the points, we use cv2.goodFeaturesToTrack().
p0 = cv2.goodFeaturesToTrack(old_gray, mask = None, **feature_params)

# Create a mask image for drawing purposes
mask = np.zeros_like(old_frame)

while(1):

    ret,frame = cap.read()
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # calculate optical flow
    p1, st, err = cv2.calcOpticalFlowPyrLK(old_gray, frame_gray, p0, None, **lk_params)

    # Select good points
    good_new = p1[st==1]
    good_old = p0[st==1]
    print(p1.shape)

    # draw the tracks
    for i,(new,old) in enumerate(zip(good_new,good_old)):
        a,b = new.ravel()
        c,d = old.ravel()
        mask = cv2.line(mask, (a,b),(c,d), color[i].tolist(), 2)
        frame = cv2.circle(frame,(a,b),5,color[i].tolist(),-1)

    img = cv2.add(frame,mask)

    cv2.imshow('frame',img)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

    # Now update the previous frame and previous points
    old_gray = frame_gray.copy()

    p0 = good_new.reshape(-1,1,2)

cv2.destroyAllWindows()
cap.release()