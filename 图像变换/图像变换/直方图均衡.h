#pragma once
#include<opencv2\opencv.hpp>
#include<opencv2\core/core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>
#include<string>
#include<vector>
using namespace cv;
using namespace std;

void HistEqual()
{

	string path = "images/cars.jpg";
	Mat car = imread(path);

	Mat gray;
	Mat dst;
	cvtColor(car, gray, COLOR_BGR2GRAY);

	equalizeHist(gray, dst);


	imshow("ԭͼ", gray);
	imshow("ֱ��ͼ����֮���ͼ", dst);

	waitKey(0);
}