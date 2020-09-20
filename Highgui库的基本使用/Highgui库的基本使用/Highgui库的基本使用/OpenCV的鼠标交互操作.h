#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;

#define WINDOWS_NAME "MYMOUSE"
//声明一些全局函数

// 鼠标事件的回调函数
void on_MouseHandle(int event, int x, int y, int flags, void*);

// 画一个矩形，
void DrawRectangle(Mat &img, Rect box);

// 帮助用户理解MYMOUSE
void ShowHelpText();

//声明一些全局变量

Rect g_rectangle;
bool g_draw = false; //是否进行绘画
RNG g_rng(12345);  // 产生一个随机数，seed=12345
//执行函数
void play() {

	g_rectangle = Rect(-1, -1, 0, 0);
	
	Mat srcImage(600, 800, CV_8UC3), tempImage;
	
	srcImage.copyTo(tempImage);

	g_rectangle = Rect(-1, -1, 0, 0);
	
	// src为一个黑色图像
	srcImage = Scalar::all(0);

	// 设置鼠标回调函数
	namedWindow(WINDOWS_NAME);
	
	//对 srcimage进行操作， void*可以理解为用户行为
	setMouseCallback(WINDOWS_NAME, on_MouseHandle, (void*)&srcImage);
    
	// 进行绘制的识别符为真，开始绘制
	while (1)
	{
		srcImage.copyTo(tempImage); //复制到临时变量
		if (g_draw) {
			//画矩形
			DrawRectangle(tempImage, g_rectangle);

		}
		imshow(WINDOWS_NAME, tempImage);
		if (waitKey(10) == 27) { break; }

	}

}

//实现鼠标回调函数
void on_MouseHandle(int event, int x, int y, int flags, void* para) {
	// 地址复制
	Mat& image = *(Mat*) para;
	
	// 根据时间类型进行相应
	switch (event)
	{
	case EVENT_MOUSEMOVE:   //鼠标移动事件
	{ 
		// 更新矩形的大小
		if (g_draw) {
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
		break;
	case EVENT_LBUTTONDOWN:  // 鼠标左键按下事件
	{
	      //按下证明正在画图
		g_draw = true;
		g_rectangle = Rect(x, y, 0, 0);// 记录当前的起点，初始化rect长宽为0
	}	
		break;
	case EVENT_LBUTTONUP:  // 鼠标左键抬起
		
	{
		//不在绘画，置为false
		g_draw = false;
		//对长和宽小于0的处理
		if (g_rectangle.width < 0) {

			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;

		}
		if (g_rectangle.height < 0) {

			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		//调用绘图函数
		DrawRectangle(image, g_rectangle);
	}
		
		break;
	default:
		break;
	}
}

// 实现画图函数
void DrawRectangle(Mat &img, Rect box) {

	//tl()  : top left 左上角的坐标      br(): bottom right 右下角左边
	int r = g_rng.uniform(0, 255);
	int g= g_rng.uniform(0, 255);
	int b = g_rng.uniform(0, 255);
	rectangle(img, box.tl(), box.br(), Scalar(r,g,b));

}