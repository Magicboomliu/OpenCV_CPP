#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;
//形态学操作，包括，开运算，闭运算，形态学梯度，顶帽，黑帽子
//(1)先腐蚀 后膨胀
// (2)先膨胀，后腐蚀
//(3)膨胀-腐蚀
//(4)原图形- 开运算
//(5)闭运算-原图形

// 可以使用api操作
// morphologyEx

// 声明全局变量
Mat tsrcImage;
Mat tdstImage;
int selected_modeed = 0;  // 默认值为开运算
#define myWindow "MOR"

void change_mode(int,void*);
void process();
void morphlology_operation()
{

	string path_image = "images/person.jpg";
	tsrcImage = imread(path_image, 1);

	//开始运算
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
	morphologyEx(tsrcImage, tdstImage, MORPH_OPEN, element);
	imshow(myWindow, tdstImage);

	createTrackbar("Mode:", myWindow, &selected_modeed, 4, change_mode);
	change_mode(selected_modeed, 0);
	
	waitKey(0);
}

// 图像处理操作
void process() {
	// 定义一个核
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
	if (selected_modeed == 0)  // 开运算
	{
		morphologyEx(tsrcImage, tdstImage, MORPH_OPEN, element);

	}
	else if (selected_modeed==1)  // 闭运算
	{
		morphologyEx(tsrcImage, tdstImage, MORPH_CLOSE, element);
	}
	else if(selected_modeed==2)  // 形态学梯度
	{
		morphologyEx(tsrcImage, tdstImage, MORPH_GRADIENT, element);
	}
	else if (selected_modeed == 3)  // Top hat
	{
		morphologyEx(tsrcImage, tdstImage, MORPH_TOPHAT, element);


	}
	else if (selected_modeed == 4)  // Black Hat
	{
		morphologyEx(tsrcImage, tdstImage, MORPH_BLACKHAT, element);

	}

	// show the image
	imshow(myWindow, tdstImage);
}
// 在回调函数中调用
void change_mode(int, void*) {

	process();
}