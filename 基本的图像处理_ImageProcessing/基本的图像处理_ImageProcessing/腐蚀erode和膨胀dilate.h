#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;
#define WindowName "Effects"
Mat srcImage;
Mat dstImage;

int selected_mode = 0; // 0代表腐蚀， 1代表膨胀
int structure_elementSize = 3; // 结构元素，内核矩阵的size

// 声明trackerbar的回调函数
void on_selected_mode(int, void*);
void on_structure_elementSize(int, void*);
// 声明图像处理函数
void onProcess();
void erode_and_dilate()
{
	// 载入图片
	string path = "images/person.jpg";
	srcImage = imread(path, 1);
	imshow("Origin", srcImage);
	// 自定义核

	Mat element = getStructuringElement(MORPH_RECT, Size(2 * structure_elementSize + 1, 2 * structure_elementSize + 1),
		Point(structure_elementSize, structure_elementSize));

	// 初次进行腐蚀操作
	erode(srcImage, dstImage, element);
	imshow(WindowName, dstImage);
	// 建立createbar
	createTrackbar("模式切换:", WindowName, &selected_mode,1, on_selected_mode);
	createTrackbar("Size:", WindowName, &structure_elementSize, 10, on_structure_elementSize);
	// 回调参数
	on_selected_mode(selected_mode, 0);
	on_structure_elementSize(structure_elementSize, 0);
	// quit

	waitKey(0);




}

//定义图像处理函数
void onProcess() {

	//自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * structure_elementSize + 1, 2 * structure_elementSize + 1),
		Point(structure_elementSize, structure_elementSize));

	// 进行erode或是dilate操作
	if(selected_mode==0)  //erode
	{ 
		erode(srcImage, dstImage, element);
	
	}
	// dilate
	else {
		dilate(srcImage, dstImage, element);

	}

	// show the image
	imshow(WindowName, dstImage);

}

void on_selected_mode(int,void*){

	onProcess();
}
void on_structure_elementSize(int, void*) {


	onProcess();

}