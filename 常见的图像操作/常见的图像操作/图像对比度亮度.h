#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
#include<vector>
using namespace std;
using namespace cv;

int contrast_value;
int brightness_value;
Mat mysrcimage;
Mat mydstimage;

//声明回调函数
void on_contrast_brightness(int, void*);

void adjust_brightness_and_contrast()
{
	// image path
	string image_path1 = "images/anime.jpg";
     mysrcimage = imread(image_path1,1);
	 mydstimage=Mat::zeros(mysrcimage.size(), mysrcimage.type());

	//设置对比度与亮度的初值
	contrast_value = 80;
	brightness_value = 80;
	
	// 创立窗口
	namedWindow("Fa");
	imshow("Fa", mysrcimage);

	createTrackbar("对比度", "Fa", &contrast_value, 300, on_contrast_brightness);
	createTrackbar("亮度", "Fa", &brightness_value, 200, on_contrast_brightness);

	//回调函数初始化
	on_contrast_brightness(contrast_value, 0);
	on_contrast_brightness(brightness_value, 0);

	waitKey(0);


}

void on_contrast_brightness(int, void*) {
     
	namedWindow("Mo",1);
	//对像素点进行操作
	for (int y = 0; y < mysrcimage.rows;  y++) {
		for (int x = 0; x < mysrcimage.cols;  x++)
		{
			for (int c = 0; c < 3;c++)
			{
				mydstimage.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(contrast_value*0.01*(mysrcimage.at<Vec3b>(y, x)[c]) + brightness_value);
			}

		}
	}
	imshow("Mo", mysrcimage);
	imshow("Fa", mydstimage);
}