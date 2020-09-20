#pragma once
#include<opencv2\opencv.hpp>
#include<string>
#include<opencv2\highgui\highgui.hpp>
#include<vector>
using namespace std;
using namespace cv;

void draws()
{

	//(1)画直线

	/*void line(InputOutputArray img,
	Point pt1,
	Point pt2,
	const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
	}*/

	Point2i p1(0, 0);
	Point2i p2(200, 200);
	Mat background(200, 200, CV_8UC3, Scalar(0, 0, 0));
	line(background, p1, p2, Scalar(255, 0, 0), 2);


// (2)有箭头的直线

//	void arrowedLine(InputOutputArray img, Point pt1, Point pt2, const Scalar& color, int thickness = 1, int line_type = 8, int shift = 0, double tipLength = 0.1);
//
//img:输入图像，直线画在该图像上
//	pt1 : 直线的起点
//	pt2 : 直线的终点
//	color : 直线的颜色
//	thickness : 直线的大小
//	lineType：直线类型
//	shift : 直线的偏移量
//	tipLength : 箭头占线段的比例
	Point2i p3(150, 50);
	Point2i p4(50,150);
	arrowedLine(background, p3, p4, Scalar(255, 255, 0), 2);
	
	//(3)画矩形
	
	/*
	void rectangle(CV_IN_OUT Mat& img, Rect rec, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);

img:输入图像，矩形画在该图像上
	rec : 矩形
	color : 矩形的颜色
	thickness : 矩形边的大小
	lineType：矩形类型
	shift : 直线的偏移量*/
	rectangle(background, Rect(25, 25, 150, 150), Scalar(0, 0, 255), 2);

	//(4)画圆

//	void circle(InputOutputArray img, Point center, int radius, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
//img:输入图像，圆形画在该图像上
//	center : 圆心
//	color : 圆形的颜色
//	thickness : 圆形边的大小
//	lineType：圆形类型
//	shift : 圆形的偏移量
	
	circle(background, Point2i(100, 100), 50, Scalar(0, 255, 0), 3);
	
	//（5）画椭圆
	ellipse(background, RotatedRect(Point2f(100, 100), Size2f(50, 100), 0), Scalar(0, 255, 255), 3);
	
	
	
	// (6)显示文字
	putText(background, "Liu Zihua", Point2f(100, 10), 0, 0.4, Scalar(255, 0, 0), 2);

	//（7） 画多边形
	Point pts[5];
	pts[0] = Point(10, 50);
	pts[1] = Point(70, 50);
	pts[2] = Point(75, 75);
	pts[3] = Point(45, 150);
	pts[4] = Point(190, 120);
	fillConvexPoly(background, pts, 5, Scalar(0, 255, 0), LINE_8, 0);
	
	imshow("sss", background);
	waitKey(0);
	
}