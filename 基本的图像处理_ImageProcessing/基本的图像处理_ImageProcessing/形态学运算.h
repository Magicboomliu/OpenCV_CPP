#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;
//��̬ѧ�����������������㣬�����㣬��̬ѧ�ݶȣ���ñ����ñ��
//(1)�ȸ�ʴ ������
// (2)�����ͣ���ʴ
//(3)����-��ʴ
//(4)ԭͼ��- ������
//(5)������-ԭͼ��

// ����ʹ��api����
// morphologyEx

// ����ȫ�ֱ���
Mat tsrcImage;
Mat tdstImage;
int selected_modeed = 0;  // Ĭ��ֵΪ������
#define myWindow "MOR"

void change_mode(int,void*);
void process();
void morphlology_operation()
{

	string path_image = "images/person.jpg";
	tsrcImage = imread(path_image, 1);

	//��ʼ����
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
	morphologyEx(tsrcImage, tdstImage, MORPH_OPEN, element);
	imshow(myWindow, tdstImage);

	createTrackbar("Mode:", myWindow, &selected_modeed, 4, change_mode);
	change_mode(selected_modeed, 0);
	
	waitKey(0);
}

// ͼ�������
void process() {
	// ����һ����
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
	if (selected_modeed == 0)  // ������
	{
		morphologyEx(tsrcImage, tdstImage, MORPH_OPEN, element);

	}
	else if (selected_modeed==1)  // ������
	{
		morphologyEx(tsrcImage, tdstImage, MORPH_CLOSE, element);
	}
	else if(selected_modeed==2)  // ��̬ѧ�ݶ�
	{
		morphologyEx(tsrcImage, tdstImage, MORPH_GRADIENT, element);
	}
	else if (selected_modeed == 3)  // Top hat
	{
		morphologyEx(tsrcImage, tdstImage, MORPH_TOPHAT, element);


	}
	else if (selected_modeed == 4)  // Black Hat
	{
		morphologyEx(tsrcImage, tdstImage, MORPH_BLACKHAT, element);

	}

	// show the image
	imshow(myWindow, tdstImage);
}
// �ڻص������е���
void change_mode(int, void*) {

	process();
}