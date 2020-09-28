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
// Houghֱ�߱任 Houghlines �� HoughlinesP
void line_detection();
// Hough ���Բ��
void Circle_detection();

Mat srcImage;
Mat src_grayimage;
Mat mydstImage;

void Hough_transform()
{
	string path = "images/street.jpg";
	srcImage = imread(path);
	cvtColor(srcImage, src_grayimage, COLOR_BGR2GRAY);
	

	line_detection();


	Circle_detection();
	
	waitKey(0);

}

// ����ʵ��
void line_detection() {

	// ʹ��HoughLine ���Api
	// ���Ⱦ���Canny��Ե���
	Canny(src_grayimage, mydstImage, 50, 200, 3);

	vector<Vec2f> lines;

	HoughLines(mydstImage, lines, 1, CV_PI / 180, 170, 0, 0);
	Mat temp = mydstImage.clone();
	// ������Щlines
	for (int i = 0;i < lines.size();i++)
	{
		Point p1; Point p2;
		float rho = lines[i][0];
		float theta = lines[i][1];
		float a = cos(theta);
		float b = sin(theta);
		float x0 = a * rho;
		float y0 = b * rho;
		// 1000�����㹻��
		p1.x = cvRound(x0 + 1000 * (-b));
		p1.y = cvRound(y0 + 1000 * a);

		p2.x = cvRound(x0 - 1000 * (-b));
		p2.y = cvRound(y0 - 1000 * (a));

	
		line(mydstImage, p1, p2, Scalar(55, 100, 195), 1, CV_AA);

	}
	imshow("HoughLines", mydstImage);
	vector<Vec4i> mylines;
	HoughLinesP(temp, mylines, 1, CV_PI / 180, 80, 50, 10);
	for (int i = 0;i < mylines.size();i++) {

		Vec4i li = mylines[i];

		line(temp, Point(li[0], li[1]), Point(li[2], li[3]), Scalar(50, 255, 200), 1, CV_AA);
	}
	imshow("HoughLinesP", temp);

	}
void Circle_detection()
{

	// HoughԲ�μ��
	string ball_path = "images/basketball.jpg";
	Mat basketball;
	basketball = imread(ball_path);

	Mat dstbasketball;
	cvtColor(basketball, dstbasketball, COLOR_BGR2GRAY);

	GaussianBlur(dstbasketball, dstbasketball, Size(9, 9), 0);

	vector<Vec3f> circles;
	HoughCircles(dstbasketball, circles, HOUGH_GRADIENT, 1.5, 10, 200, 120, 0, 0);

	for (size_t i = 0;i < circles.size();i++)
	{
		// Բ��Բ�ĺ�Բ�İ뾶
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		// ����Բ��
		circle(dstbasketball, center, 4, Scalar(0, 0, 255), 3);

		// ����Բ
		circle(dstbasketball, center, radius, Scalar(0, 0, 255), 2);


	}
	imshow("Hough Circle", dstbasketball);

}