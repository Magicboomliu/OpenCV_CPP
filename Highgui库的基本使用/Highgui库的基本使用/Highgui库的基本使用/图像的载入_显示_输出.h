#pragma once
#include<iostream>
using namespace std;
#include<string>
// 声明头文件，core组件以及highgui 的hpp文件
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

// 使用opencv的标准命名空间cv
using namespace cv;
void show_and_save_image()
{
 /*    在opencv中文件的路径名不能是中文，日语等*/	

	string huihui_path = "images/anime.jpg";
    // 图像默认为是一个Mat对象
	Mat huihui = imread(huihui_path);   // 默认为1，即为无损的彩色图像
	// 效果相同   Mat huihui = imread(huihui_path,1);	
	//显示灰色图片
	/*Mat huihui_gray = imread(huihui_path, 0);*/
	// 显示带Alpha通道的图片
	//Mat huihui_alpha = imread(huihui_path, -1);

	namedWindow("爆裂魔法使", WINDOW_AUTOSIZE); //创建一个“爆裂魔法使”的窗口
	
	imshow("爆裂魔法使", huihui);  //展示这张图片，输入窗口的信息


	/*  图像的融合 */
	Mat backgroud = imread("images/street.jpg");
	Mat foreground = imread("images/person.jpg");

	
	// 查看图像的尺寸的维度
	cout << foreground.size() << endl;   // 第一个属性是cols,第二个属性是rows
	cout << backgroud.dims << endl; //输出图像的维度,为2维度
	//查看图像的宽和长
	cout << backgroud.rows <<" "<< backgroud.cols << endl;
	//重新定义foregound的大小，注意调用resize函数需要使用imgproc头文件
	resize(foreground, foreground, Size(100, 100));


	imshow("背景图片", backgroud);
	imshow("前景图片", foreground);

	// 定义一个图像ROI    ,前2个参数为开始的Y和X坐标，后面2个参数为rect的高和宽
	Mat ImageROI = backgroud(Rect(10, 10, foreground.cols, foreground.rows));


	// 将ImageROI替换为foreground
	// para1: 第一个图片    para2:权重  para3: 第二个图片，para4权重 para5每个像素价值，最后一个para6 返回元素
	addWeighted(ImageROI, 0.3, foreground, 0.5, 3, ImageROI);

	// 添加后的效果
	imshow("添加后的效果", backgroud);

	// 保存在本地
	imwrite("after/merged.jpg", backgroud);

	waitKey(0); // 按任意键继续
	
}