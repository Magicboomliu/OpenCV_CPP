#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;

// 使用滑动条的
const int maxAlpha = 100;
int currentAlphaSpider;

double alphaValue;
double betaValue;


// image path
string image_path1 = "images/anime.jpg";
Mat mypic = imread(image_path1, 1);
string image_path2 = "images/street.jpg";
Mat bg = imread(image_path2, 1);
Mat dstImage;
Mat imageROI;


void on_trackerbar(int, void*) {
	// 计算当前进度条
	alphaValue = (double)currentAlphaSpider / maxAlpha;
	betaValue = 1.0 - alphaValue;
	// 线性混合
	addWeighted(mypic, alphaValue, imageROI, betaValue, 0, imageROI);
	imshow("线性融合填充", bg);
}


// 获取图形中自己感兴趣的area
void useROI() {

	// 使用mask进行加权
	resize(mypic, mypic, Size(100,100));

   imageROI = bg(Rect(100, 100, 100,100));

	//Mat mask = imread(image_path1,0);

	//resize(mask, mask, Size(100,100));

	//mypic.copyTo(imageROI, mask);

	//namedWindow("使用mask填充ROI");
	//imshow("使用mask填充ROI", bg);


	//滑动条初始值为10
	currentAlphaSpider = 80;
	// 在创建的窗体中，创建一个trackerbar
	char TrackerBarName[50]; // 注意这里必须是char数组
	sprintf_s(TrackerBarName, "透明度为%d",(int) alphaValue);
	namedWindow("线性融合填充");
	createTrackbar(TrackerBarName, "线性融合填充", &currentAlphaSpider, maxAlpha, on_trackerbar);

	// 结果在回调函数中显示, 0 默认为userdata
	on_trackerbar(currentAlphaSpider, 0);

	waitKey(0);

}

