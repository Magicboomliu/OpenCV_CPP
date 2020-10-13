__author__ = "Luke Liu"
#encoding="utf-8"
import cv2
import  numpy as np

''' Background subtraction is a major preprocessing steps in many vision based applications. 
There are three APIs:
(1)BackgroundSubtractorMOG
(2)BackgroundSubtractorMOG2
(3)BackgroundSubtractorGMG
'''
class Background_Substraction:
    # 初始化这个
    def __init__(self,videopath,mode=0):
        self.videopath=videopath
        self.substractionMode=mode


    def MOG2(self):
        cap=cv2.VideoCapture(self.videopath)
        # 建议GMM
        fgbg = cv2.createBackgroundSubtractorMOG2()
        while(1):
            ret,frame = cap.read()
            # 获得图像掩模
            fgmask = fgbg.apply(frame)
            # 中值滤波去除部分椒盐噪声
            fgmask=cv2.medianBlur(fgmask,5)
            # 开运算进一步去除噪声
            element=cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))
            fgmask=cv2.morphologyEx(fgmask,cv2.MORPH_OPEN,element)

            #找到人轮廓信息
            cnts = cv2.findContours(fgmask.copy(),cv2.RETR_EXTERNAL,
                            cv2.CHAIN_APPROX_SIMPLE)[1]
            # cv2.drawContours(frame, cnts, -1, (0, 255, 0), 3)

            for c in cnts:
                lenth=cv2.arcLength(c,True)
                if lenth>188:
                    (x,y,w,h)=cv2.boundingRect(c)
                    cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),3)

            cv2.imshow('frame', fgmask)
            cv2.imshow("orginal",frame)
            k = cv2.waitKey(30) & 0xff
            if k == 27:
                break

        cap.release()
        cv2.destroyAllWindows()

    def GMG(self):
        cap=cv2.VideoCapture(self.videopath)
        # 建议GMM
        fgbg = cv2.cv2.createBackgroundSubtractorGMG()
        while(1):
            ret,frame = cap.read()
            # 获得图像掩模
            fgmask = fgbg.apply(frame)
            # 中值滤波去除部分椒盐噪声
            fgmask=cv2.medianBlur(fgmask,5)
            # 开运算进一步去除噪声
            element=cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))
            fgmask=cv2.morphologyEx(fgmask,cv2.MORPH_OPEN,element)

            #找到人轮廓信息
            cnts = cv2.findContours(fgmask.copy(),cv2.RETR_EXTERNAL,
                            cv2.CHAIN_APPROX_SIMPLE)[1]
            # cv2.drawContours(frame, cnts, -1, (0, 255, 0), 3)

            for c in cnts:
                lenth=cv2.arcLength(c,True)
                if lenth>188:
                    (x,y,w,h)=cv2.boundingRect(c)
                    cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),3)

            cv2.imshow('frame', fgmask)
            cv2.imshow("orginal",frame)
            k = cv2.waitKey(30) & 0xff
            if k == 27:
                break

        cap.release()
        cv2.destroyAllWindows()


    def BackgroundSubstraction(self):
        if self.substractionMode==0:
            self.MOG2()
        elif self.substractionMode==1:
            self.GMG()
        else:
            print(" Mode Range is [0,1]")



# Test The Image
if __name__ == '__main__':
    videoPath='test.avi'
    bs=Background_Substraction(videopath=videoPath,mode=0)
    bs.BackgroundSubstraction()


