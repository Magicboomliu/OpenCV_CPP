#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;

// 高斯金子塔和拉普拉斯金字塔的含义：

//(1)高斯金字塔(Gaussianpyramid): 用来向下采样，主要的图像金字塔
//主要是先卷积，去掉偶数行和偶数列


//(2)拉普拉斯金字塔(Laplacianpyramid) : 用来从金字塔低层图像重建上层未采样图像，
//在数字图像处理中也即是预测残差，可以对图像进行最大程度的还原，
//配合高斯金字塔一起使用。每一层都是残差

// 定义图像金字塔
void pyramid()
{
	String path = "images/street.jpg";
   // 定义一个数组，放4高斯层金字塔
	Mat GuassianPyramid[4];
	GuassianPyramid[0] = imread(path);
	
	// 建立一个Gaussian Pyramid Array
	for (int i = 1;i < 4;i++)
	{
		pyrDown(GuassianPyramid[i - 1], GuassianPyramid[i],
		Size(GuassianPyramid[i - 1].cols / 2, GuassianPyramid[i - 1].rows / 2));
	}
	// 建立一个 Laplace Pyramid Array
	Mat LaplacePyramid[3];
	for (int i = 0;i < 3;i++)
	{
		Mat upsample_Image;
		// 上采样
		pyrUp(GuassianPyramid[i + 1], upsample_Image, Size(GuassianPyramid[i + 1].cols * 2, GuassianPyramid[i + 1].rows * 2));

		Mat residual;
		resize(upsample_Image, upsample_Image, Size(GuassianPyramid[i].size()));

		residual = GuassianPyramid[i] - upsample_Image;

		LaplacePyramid[i] = residual;

	}

	 //显示高斯金字塔
	int height = GuassianPyramid[0].rows;
	int width = 0;
	for (int i = 0;i < 4;i++) {

		width += GuassianPyramid[i].cols;
	
	}
	Mat black_holder(height, width, CV_8UC3,Scalar::all(0));
	//每个区域开始的坐标
	int X_beigin = 0;
	int y_beigin = 0;

	// 首先定义一个区域
	Mat imageROI;
    imageROI = black_holder(Rect(X_beigin, y_beigin, GuassianPyramid[0].cols, GuassianPyramid[0].rows));
	
	GuassianPyramid[0].copyTo(imageROI);
	
	for (int i = 1;i < 4; i++) {
		X_beigin += GuassianPyramid[i-1].cols;
		Mat imageROI = black_holder(Rect(X_beigin, y_beigin, GuassianPyramid[i].cols, GuassianPyramid[i].rows));
		 GuassianPyramid[i].copyTo(imageROI);
	}
	
	imshow("Gaussian Pyrmaid 图像金字塔", black_holder);

	//white_holder
	int wheight = GuassianPyramid[0].rows;
	int wwidth = 0;
	for (int i = 0;i < 3;i++) {

		wwidth += LaplacePyramid[i].cols;

	}
	Mat white_holder(height, width, CV_8UC3, Scalar::all(255));

	int xx_bei=0;
	int yy_bei=0;


	// ImageROI

	Mat wImageROI = white_holder(Rect(xx_bei, yy_bei, LaplacePyramid[0].cols, LaplacePyramid[0].rows));

	LaplacePyramid[0].copyTo(wImageROI);

	for (int i = 1;i < 3;i++)
	{
		xx_bei += LaplacePyramid[i - 1].cols;
		Mat wImageROI = white_holder(Rect(xx_bei, yy_bei, LaplacePyramid[i].cols, LaplacePyramid[i].rows));

		LaplacePyramid[i].copyTo(wImageROI);

	}

	imshow("Laplace金字塔 ", white_holder);


	waitKey(0);

}