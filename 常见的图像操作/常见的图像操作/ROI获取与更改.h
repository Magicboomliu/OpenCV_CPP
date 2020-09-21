#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;

// ʹ�û�������
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
	// ���㵱ǰ������
	alphaValue = (double)currentAlphaSpider / maxAlpha;
	betaValue = 1.0 - alphaValue;
	// ���Ի��
	addWeighted(mypic, alphaValue, imageROI, betaValue, 0, imageROI);
	imshow("�����ں����", bg);
}


// ��ȡͼ�����Լ�����Ȥ��area
void useROI() {

	// ʹ��mask���м�Ȩ
	resize(mypic, mypic, Size(100,100));

   imageROI = bg(Rect(100, 100, 100,100));

	//Mat mask = imread(image_path1,0);

	//resize(mask, mask, Size(100,100));

	//mypic.copyTo(imageROI, mask);

	//namedWindow("ʹ��mask���ROI");
	//imshow("ʹ��mask���ROI", bg);


	//��������ʼֵΪ10
	currentAlphaSpider = 80;
	// �ڴ����Ĵ����У�����һ��trackerbar
	char TrackerBarName[50]; // ע�����������char����
	sprintf_s(TrackerBarName, "͸����Ϊ%d",(int) alphaValue);
	namedWindow("�����ں����");
	createTrackbar(TrackerBarName, "�����ں����", &currentAlphaSpider, maxAlpha, on_trackerbar);

	// ����ڻص���������ʾ, 0 Ĭ��Ϊuserdata
	on_trackerbar(currentAlphaSpider, 0);

	waitKey(0);

}

