#pragma once
#include<opencv2\opencv.hpp>
#include<string>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;

void change_COLOR()
{
	string image_path = "images/tower.jpg";
	Mat mypic = imread(image_path, 1);
	resize(mypic, mypic, Size(300, 300));
	imshow("ԭͼ", mypic);
	//mypic.convertTo(mypic, CV_32FC3);
	//imshow("Float", mypic);
	//waitKey(0);

	Mat Gray;
	cvtColor(mypic, Gray, COLOR_BGR2GRAY);
	imshow("Grays", Gray);
	waitKey(0);




}