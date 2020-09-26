#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;
#define WindowName "Effects"
Mat srcImage;
Mat dstImage;

int selected_mode = 0; // 0����ʴ�� 1��������
int structure_elementSize = 3; // �ṹԪ�أ��ں˾����size

// ����trackerbar�Ļص�����
void on_selected_mode(int, void*);
void on_structure_elementSize(int, void*);
// ����ͼ������
void onProcess();
void erode_and_dilate()
{
	// ����ͼƬ
	string path = "images/person.jpg";
	srcImage = imread(path, 1);
	imshow("Origin", srcImage);
	// �Զ����

	Mat element = getStructuringElement(MORPH_RECT, Size(2 * structure_elementSize + 1, 2 * structure_elementSize + 1),
		Point(structure_elementSize, structure_elementSize));

	// ���ν��и�ʴ����
	erode(srcImage, dstImage, element);
	imshow(WindowName, dstImage);
	// ����createbar
	createTrackbar("ģʽ�л�:", WindowName, &selected_mode,1, on_selected_mode);
	createTrackbar("Size:", WindowName, &structure_elementSize, 10, on_structure_elementSize);
	// �ص�����
	on_selected_mode(selected_mode, 0);
	on_structure_elementSize(structure_elementSize, 0);
	// quit

	waitKey(0);




}

//����ͼ������
void onProcess() {

	//�Զ����
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * structure_elementSize + 1, 2 * structure_elementSize + 1),
		Point(structure_elementSize, structure_elementSize));

	// ����erode����dilate����
	if(selected_mode==0)  //erode
	{ 
		erode(srcImage, dstImage, element);
	
	}
	// dilate
	else {
		dilate(srcImage, dstImage, element);

	}

	// show the image
	imshow(WindowName, dstImage);

}

void on_selected_mode(int,void*){

	onProcess();
}
void on_structure_elementSize(int, void*) {


	onProcess();

}