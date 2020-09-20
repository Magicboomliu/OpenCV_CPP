#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;

	const int g_nMaxAlphaValue = 100;  // Alpha的上限值为100
	int  g_nAlphaSlider;  //滑动条对应的变量

	// 两个权重变量
	double g_dAlphaValue;
	double g_BetaValue;

	Mat g_srcImage1;  // 要进行混合的第一个图片
	Mat g_srcImage2;  // 要进行混合的第二个图片
	Mat g_dstImage;;  // 混合后的图片
	
	// 定义滑动条拖动后的回调函数
	void on_Trackbar( int, void* )//注意这里必须是void* ,代表usrdata}
		
	{
		// 计算机出用户交互后，AlphaValue与BetaValue的值
		g_dAlphaValue = (double)g_nAlphaSlider / g_nMaxAlphaValue;
		g_BetaValue = (1.0 - g_dAlphaValue);
		// 将二个参数进行混合，得到merged_image，传给dstImage
		addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_BetaValue, 0.0, g_dstImage);
		imshow("线性混合后的图片", g_dstImage);
	}

	void showImage() {
		// 加载2张图片，same size
		g_srcImage1 = imread("images/street.jpg");
		g_srcImage2 = imread("images/person.jpg");
		// 改变image2的大小，使其与image1一样大
		resize(g_srcImage2, g_srcImage2, Size(g_srcImage1.cols, g_srcImage1.rows));

		// 初始化滑动条的值
		g_nAlphaSlider = 0;

		// 在创建的窗体中，创建一个trackerbar
		char TrackerBarName[50]; // 注意这里必须是char数组
		sprintf_s(TrackerBarName, "透明度为%d", g_nMaxAlphaValue);

		// 要告诉编译器，创建一个同名的窗体
		namedWindow("线性混合后的图片");

		createTrackbar(TrackerBarName, "线性混合后的图片", &g_nAlphaSlider,
			g_nMaxAlphaValue, on_Trackbar );


		// 返回当前trackerbar的位置
		int pos;
		pos = getTrackbarPos(TrackerBarName, "线性混合后的图片");
		cout << pos << endl;



		// 结果在回调函数中显示, 0 默认为userdata
		on_Trackbar(g_nAlphaSlider, 0);



		waitKey(0);

	}







