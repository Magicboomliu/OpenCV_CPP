#pragma once
#include<opencv2\opencv.hpp>
#include<string>
#include<opencv2\highgui\highgui.hpp>
#include<vector>
using namespace std;
using namespace cv;

void draws()
{

	//(1)��ֱ��

	/*void line(InputOutputArray img,
	Point pt1,
	Point pt2,
	const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
	}*/

	Point2i p1(0, 0);
	Point2i p2(200, 200);
	Mat background(200, 200, CV_8UC3, Scalar(0, 0, 0));
	line(background, p1, p2, Scalar(255, 0, 0), 2);


// (2)�м�ͷ��ֱ��

//	void arrowedLine(InputOutputArray img, Point pt1, Point pt2, const Scalar& color, int thickness = 1, int line_type = 8, int shift = 0, double tipLength = 0.1);
//
//img:����ͼ��ֱ�߻��ڸ�ͼ����
//	pt1 : ֱ�ߵ����
//	pt2 : ֱ�ߵ��յ�
//	color : ֱ�ߵ���ɫ
//	thickness : ֱ�ߵĴ�С
//	lineType��ֱ������
//	shift : ֱ�ߵ�ƫ����
//	tipLength : ��ͷռ�߶εı���
	Point2i p3(150, 50);
	Point2i p4(50,150);
	arrowedLine(background, p3, p4, Scalar(255, 255, 0), 2);
	
	//(3)������
	
	/*
	void rectangle(CV_IN_OUT Mat& img, Rect rec, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);

img:����ͼ�񣬾��λ��ڸ�ͼ����
	rec : ����
	color : ���ε���ɫ
	thickness : ���αߵĴ�С
	lineType����������
	shift : ֱ�ߵ�ƫ����*/
	rectangle(background, Rect(25, 25, 150, 150), Scalar(0, 0, 255), 2);

	//(4)��Բ

//	void circle(InputOutputArray img, Point center, int radius, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
//img:����ͼ��Բ�λ��ڸ�ͼ����
//	center : Բ��
//	color : Բ�ε���ɫ
//	thickness : Բ�αߵĴ�С
//	lineType��Բ������
//	shift : Բ�ε�ƫ����
	
	circle(background, Point2i(100, 100), 50, Scalar(0, 255, 0), 3);
	
	//��5������Բ
	ellipse(background, RotatedRect(Point2f(100, 100), Size2f(50, 100), 0), Scalar(0, 255, 255), 3);
	
	
	
	// (6)��ʾ����
	putText(background, "Liu Zihua", Point2f(100, 10), 0, 0.4, Scalar(255, 0, 0), 2);

	//��7�� �������
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