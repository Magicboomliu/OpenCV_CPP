__author__ = "Luke Liu"
#encoding="utf-8"
import cv2
import numpy as np
import os
import  glob

import numpy as np
import cv2
from matplotlib import pyplot as plt

# 读取图片
extensions=['jpg','png']
image_list=[]
for extension in extensions:
    file_glob=os.path.join("images",'*.'+extension)
    f = glob.glob(file_glob)
    image_list.extend(f)

img = cv2.imread(image_list[0])
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
#找到质量大于0.1最好的25分点
corners = cv2.goodFeaturesToTrack(gray,25,0.01,10)
print(corners.shape)
# 䦃回的结果是 [[ 311., 250.]] 两层括号的数组。
corners = np.int0(corners)

print(corners.shape)
for i in corners:
    x,y = i.ravel()
    cv2.circle(img,(x,y),3,255,-1)

plt.gray()
plt.imshow(img)
plt.axis("off")
plt.show()