#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>

using namespace std;
using namespace cv;
bool ROI_AddImage()
{
	//读入图像
	String path = "images/person.jpg";
	Mat srcImage = imread(path);
	Mat logo;
	
	resize(srcImage, logo, Size(srcImage.cols / 2, srcImage.rows / 2));
	
	Mat black_holder(800,800, CV_8UC3, Scalar::all(0));
	//.定义Roi区域
	Mat imageROI = black_holder(Rect(50, 50, logo.cols, logo.rows));
									 //将掩膜复制到RoiImage
	logo.copyTo(imageROI);

	//显示
	imshow("result", black_holder);
	waitKey(0);
	return true;
}