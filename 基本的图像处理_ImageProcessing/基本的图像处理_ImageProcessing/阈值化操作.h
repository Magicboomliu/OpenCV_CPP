#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;

int Threshold_Max = 100;
int threshold_value =100;
int threshold_type = 0;//默认值为0
void on_threshold(int, void*);

Mat target_image;
Mat gray_target_image;
Mat after_target_image;
#define Windowss "Threshold阈值处理"

void Threshold_adjust()
{
	String path = "images/street.jpg";
	
	target_image = imread(path);
	
	cvtColor(target_image, gray_target_image, COLOR_BGR2GRAY);
	namedWindow(Windowss);

	createTrackbar("threshold Type:", Windowss, &threshold_type, 4, on_threshold);

	createTrackbar("threshold Value:", Windowss, &threshold_value, 255, on_threshold);

	on_threshold(threshold_type, 0);
	on_threshold(threshold_value, 0);

	waitKey(0);
}

void on_threshold(int, void*) {

	threshold(gray_target_image, after_target_image, threshold_value, 255, threshold_type);

	imshow(Windowss, after_target_image);

}