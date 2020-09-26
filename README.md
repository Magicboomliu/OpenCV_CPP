## OpenCV_CPP      following MagicBoom~（更新中）
 C++版本的opencv的快速学习与上手  
      ![blockchain]( https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1856784312,3552312626&fm=26&gp=0.jpg"区块链")

 **为美好世界献上Code，Explo**!**
***  
>Opencv3 Windows Visual Studio配置  
>https://blog.csdn.net/weixin_42132144/article/details/82014559  
>Opencv3+Opencv_Contrib Ubuntu 安装与配置
>https://blog.csdn.net/qq_36059536/article/details/107356389
***
>OpenCV 3.20相关文件以及SLAM有关的文件于电子书下载  
> 链接：https://pan.baidu.com/s/14FWbH4fSmiCY1P3KxPi_PQ  
>提取码：bbr6  
---

 ### **知识点一:OpenCV的基本数据结构：（Core组件内）**  
##### 常用的一些数据结构：

（1）Mat容器
 * Mat 容器的使用与构造方法  
 * OpenCV的格式化输出（C风格，Matlab风格，Python风格)  
 * 矩阵基本运算，加法、减法、乘法、除法、求逆，求转置，求行列式，求特征值、特征向量，求trace等。

(2)点类与使用： Point类
 * Point, Point2i，Point2f,Ponit_<>  

(3)颜色的表示：Scalar类  

（4）尺寸的表示: Size类  

##### 常用的一些方法：
 （1）基本的颜色转换 cvtColor()  

 （2）基本图形的绘制  
 * 画直线
 * 画椭圆
 * 画矩形
 * 画圆
 * 画多边形  

（3）Mat的遍历（Image中像素的遍历） 3种方式  

##### 案例： 遍历图片并实现空间掩模锐化  
**Path:"OpenCV的基本数据结构\OpenCV基本数据结构\OpenCV基本数据结构\利用遍历实现掩模.h"**




---
### **知识点二: 常见的一些图片操作：**    
（1）图片ROI操作  

（2）颜色通道的分离与组合 spilt（）和merge()函数  

  (3)图像对比度与亮度(结合TrackerBar)  

  （4）图像的离散傅里叶变换dft（）  

   (5)YML文件，XML文件的读写操作

---


 ### **知识点三: HighGui库的使用(OpenCV中的用户交互库)：**  

 （1）**图片的读取、显示、以及写入。**  
  * imread(), imshow(), imwrite(), nameWindows()的使用
  * addWeighted()的使用  
  * imgproc下的resize()函数的使用

  使用案例：融合2张图片  
   **Path:\Highgui库的基本使用\Highgui库的基本使用\Highgui库的基本使用\图像的载入_显示_输出.h**  


 (2)**TrackerBar的使用**  
  * createTrackerBar()创建一个TrackerBar 的使用，以及回调机制 on_TrackerBar(int,void*)
  * getTrackerPos() 获取当前trackerBar的位置  

  使用案例：使用TrackerBar融合2张图片（用户调节权重)  
   **Path :\Highgui库的基本使用\Highgui库的基本使用\Highgui库的基本使用\滑动条的创建与使用.h**  


   （3）**鼠标回调机制**  
   * setMouseCallBack的使用
   * Rect类的使用
   * rectangle() 画矩形函数的使用

    使用案例：使用鼠标画矩形  
    **Path:\Highgui库的基本使用\Highgui库的基本使用\Highgui库的基本使用\OpenCV的鼠标交互操作.h**  

---
### **知识点四： Image Processing 图像处理**  
（1）OPENCV的 Filter操作  
  * 方框滤波  
  * 高斯滤波  
  * 均值滤波  
  * 双边滤波   
  * 和中值滤波
（2）腐蚀和膨胀：erode dilate    

  (3)高斯金字塔和拉普拉斯金字塔  
  * 上采样  
  * 下采样  

  （4）形态学操作  
  * 开运算  
  * 闭运算  
  * 形态学梯度  
  * Top Hat  
  * Black Hat  

   (5)Threshold操作  
   * threshold()  
   * adaptive_threshold()   


---
### **知识点五： Image transfrom 图像变换**
---


  ## **更新中...**
