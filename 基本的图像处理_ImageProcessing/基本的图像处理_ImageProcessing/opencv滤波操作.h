#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;

//opencv中常见的滤波操作有方框滤波 高斯滤波 均值滤波 双边滤波 和中值滤波
Mat mysrcImage; 
Mat dstimage1; // BoxFilter()
Mat dstimage2; // MeanFilter()
Mat dstimage3; // GussianFilter()
Mat dstimage4; // MedianFilter()
Mat dstimage5;  // BilateralFilter()

const int BoxFilterMaxValue=9; // 方框滤波的最大值
const int MeanBlurMaxValue = 10; // 均值滤波的最大值
const int GussianBlurMaxValue = 6; // 高斯滤波的最大值
const int MedianBlurMaxValue = 10; // 中值滤波的最大值
const int BilateralFilterMaxValue = 10; // 双边滤波的最大值

int currentBoxFilter;
int currentMeanFilter;
int currentGussianFilter;
int currentMeidanFilter;
int currentBliaterFilter;

#define WindowName "BoxFilter"
#define WindowName_1 "MeanFilter"
#define WindowName_2 "GaussianFilter"
#define WindowName_3 "MedianFilter"
#define WindowName_4 "BliaterFilter"

void on_Box_blur(int, void*);
void on_Mean_blur(int, void*);
void on_Gaussian_blur(int, void*);
void on_median_blur(int, void*);
void on_bliater_blur(int, void*);

void myblurs()
{
	string imagePath = "images/tower.jpg";
	mysrcImage = imread(imagePath);

	// 初始化
	currentBoxFilter = 0;
	currentMeanFilter = 0;
	currentGussianFilter = 0;
	currentMeidanFilter = 0;
	currentBliaterFilter = 0;
	// BoxFilter
	namedWindow(WindowName);

	createTrackbar("Box Kernel：", WindowName, &currentBoxFilter, 50, on_Box_blur);
	on_Box_blur(currentBoxFilter, 0);

	// MeanFilter
   namedWindow(WindowName_1);
   createTrackbar("Mean Kernl: ", WindowName_1, &currentMeanFilter, 50, on_Mean_blur);
   on_Mean_blur(currentMeanFilter, 0);
	// GaussainFilter
   namedWindow(WindowName_2);
   createTrackbar("Gaussain Kernl: ", WindowName_2, &currentGussianFilter, 50, on_Gaussian_blur);
   on_Gaussian_blur(currentGussianFilter, 0);

	// MedianFiler
   namedWindow(WindowName_3);
   createTrackbar("Median:", WindowName_3, &currentMeidanFilter, 50, on_median_blur);
   on_median_blur(currentMeidanFilter, 0);
  

	// BiltarFilter
   namedWindow(WindowName_4);
   createTrackbar("Bilter:", WindowName_4, &currentBliaterFilter, 50, on_bliater_blur);
   on_bliater_blur(currentBliaterFilter, 0);


	waitKey(0);


}

void on_Box_blur(int, void*) {

	boxFilter(mysrcImage, dstimage1, -1, Size(currentBoxFilter + 1, currentBoxFilter + 1));	
	imshow(WindowName, dstimage1);
	
}

void on_Mean_blur(int, void*) {
	blur(mysrcImage, dstimage2, Size(currentMeanFilter + 1, currentMeanFilter + 1));
	imshow(WindowName_1, dstimage2);


}
void on_Gaussian_blur(int, void*) {
	GaussianBlur(mysrcImage, dstimage3, Size(2 * currentGussianFilter + 1, 2 * currentGussianFilter + 1), 0, 0);
	imshow(WindowName_2, dstimage3);
}
void on_median_blur(int, void*) {
	medianBlur(mysrcImage, dstimage4,currentMeidanFilter+1);
	imshow(WindowName_3, dstimage4);

}
void on_bliater_blur(int, void*) {
	bilateralFilter(mysrcImage, dstimage5, currentBliaterFilter, currentBliaterFilter * 2, currentBliaterFilter / 2);
	imshow(WindowName_4, dstimage5);


}