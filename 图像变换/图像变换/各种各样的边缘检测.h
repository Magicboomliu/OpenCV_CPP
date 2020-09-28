#pragma once
#include<opencv2\opencv.hpp>
#include<opencv2\core/core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>
#include<string>
using namespace cv;
using namespace std;
void Edege_detection();
// 边缘检测的一般步骤：
//（1） 降噪 一般使用高斯滤波
//  (2)   增强， 一般是使用图像梯度   
//  (3)  检测

// Canny 
void Canny_edege_detection();
// Sobel 
void Sobel_edage_detection();
// Lapalce
void Laplace_edage_detction();
// Scharr 
void Scharr_edage_detection();

Mat srcimage;
Mat grayimage;
Mat dstImage;
string path;

void Edege_detection()
{
	path = "images/anime.jpg";

	srcimage = imread(path);

	cvtColor(srcimage, grayimage, COLOR_BGR2GRAY);

	// 使用Canny边缘检测
	
	Canny_edege_detection();
	
	// 使用Sobel进行边缘检测

	Sobel_edage_detection();

	// 使用Laplace 进行边缘检测

	Laplace_edage_detction();

	// 使用Scharr进行差分
	Scharr_edage_detection();

	waitKey(0);
}

// Canny 算子的边缘检测
void Canny_edege_detection()
{

	// 首先进行高斯滤波 ksize定位3*3

	Mat myimage;
	myimage = grayimage.clone();

	GaussianBlur(myimage, myimage, Size(3, 3),0);

	// Use gradient
	//Mat element = getStructuringElement(MORPH_RECT,Size(5,5));
	//morphologyEx(myimage, myimage, MORPH_GRADIENT,element);


	Canny(myimage, myimage, 100, 150, 3);
	imshow("Canny", myimage);


}

// Sobel算子边缘检测
// Sobel算子就是计算x和y方向的梯度
void Sobel_edage_detection()
{

	Mat grad_x; 
	Mat grad_y;
	Mat gradiant;

	Mat tempimage = grayimage.clone();

	GaussianBlur(tempimage, tempimage, Size(3, 3), 0);
	// 计算X方向的梯度
	Sobel(tempimage, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, grad_x);
	// 计算Y方向的梯度
	Sobel(tempimage, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, grad_y);
	// 合并
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, gradiant);

	imshow("Sobel gradient", gradiant);

}
// Laplace 边缘检测
void Laplace_edage_detction()
{
	Mat temP_image;
	temP_image= imread(path,0);
	Mat mydst;
	Laplacian(temP_image, mydst, CV_16S, 3, 1, 0, BORDER_DEFAULT);


	convertScaleAbs(mydst,mydst);


	imshow("Laplace Image", mydst);

}
// Schaar算子 就是求x方向和y方向的查分，可以看做固定ksize的Sobel算子
void Scharr_edage_detection()
{
	// 定义一些变量
	Mat temp = grayimage.clone();
	Mat grad_x;
	Mat grad_y;

	GaussianBlur(temp, temp, Size(3, 3), 0);

	// X方向的差分
	Scharr(temp, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, grad_x);
	// Y方向的差分
	Scharr(temp, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, grad_y);
	// 合并起来
	imshow("X方向", grad_x);
	imshow("Y方向", grad_y);
	Mat merge;
	addWeighted(grad_x, 0.5, grad_y, 0.5,0,merge);
	imshow("Merge", merge);




}
