#pragma once
#include<opencv2\opencv.hpp>
#include<opencv2\core/core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>
#include<string>
using namespace cv;
using namespace std;
#define Win "Hough"

Mat bsrcImage;
Mat cannyImage;
Mat bdstImage;
vector<Vec4i> mylines;

int max_value = 200;
int current_value = 80;
// trackerbar的回调函数
void on_hough(int, void*);

void usage_of_Hough()
{
   
	string my_path = "images/building.jpg";
	bsrcImage = imread(my_path);
	// 高斯模糊
	GaussianBlur(bsrcImage, bsrcImage, Size(7, 7), 0);
	cvtColor(bsrcImage, bsrcImage, COLOR_BGR2GRAY);

	namedWindow(Win);
	createTrackbar("Threshold:", Win, &current_value, max_value, on_hough);
	// Canny算子
	Canny(bsrcImage, cannyImage, 50, 200, 3);
	// 第一次Hough检测
	on_hough(current_value, 0);
	/*HoughLinesP(cannyImage, mylines, 1, CV_PI / 180, 80, 50, 10);*/

	/*imshow(Win, cannyImage);*/

	waitKey(0);

}
void on_hough(int, void*) {

	Mat cannyImage1 = cannyImage.clone();
	vector<Vec4i> myli;
	HoughLinesP(cannyImage1,myli , 1, CV_PI / 180, current_value, 50, 10);
	for (size_t i = 0;i < myli.size();i++)
	{

		Vec4i li=myli[i];
		line(cannyImage1, Point(li[0], li[1]), Point(li[2], li[3]), Scalar(255, 0, 0), 2);
	}
	imshow(Win, cannyImage1);



}