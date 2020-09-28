#pragma once
#include<opencv2\opencv.hpp>
#include<opencv2\core/core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>
#include<string>
using namespace cv;
using namespace std;
void Edege_detection();
// ��Ե����һ�㲽�裺
//��1�� ���� һ��ʹ�ø�˹�˲�
//  (2)   ��ǿ�� һ����ʹ��ͼ���ݶ�   
//  (3)  ���

// Canny 
void Canny_edege_detection();
// Sobel 
void Sobel_edage_detection();
// Lapalce
void Laplace_edage_detction();
// Scharr 
void Scharr_edage_detection();

Mat srcimage;
Mat grayimage;
Mat dstImage;
string path;

void Edege_detection()
{
	path = "images/anime.jpg";

	srcimage = imread(path);

	cvtColor(srcimage, grayimage, COLOR_BGR2GRAY);

	// ʹ��Canny��Ե���
	
	Canny_edege_detection();
	
	// ʹ��Sobel���б�Ե���

	Sobel_edage_detection();

	// ʹ��Laplace ���б�Ե���

	Laplace_edage_detction();

	// ʹ��Scharr���в��
	Scharr_edage_detection();

	waitKey(0);
}

// Canny ���ӵı�Ե���
void Canny_edege_detection()
{

	// ���Ƚ��и�˹�˲� ksize��λ3*3

	Mat myimage;
	myimage = grayimage.clone();

	GaussianBlur(myimage, myimage, Size(3, 3),0);

	// Use gradient
	//Mat element = getStructuringElement(MORPH_RECT,Size(5,5));
	//morphologyEx(myimage, myimage, MORPH_GRADIENT,element);


	Canny(myimage, myimage, 100, 150, 3);
	imshow("Canny", myimage);


}

// Sobel���ӱ�Ե���
// Sobel���Ӿ��Ǽ���x��y������ݶ�
void Sobel_edage_detection()
{

	Mat grad_x; 
	Mat grad_y;
	Mat gradiant;

	Mat tempimage = grayimage.clone();

	GaussianBlur(tempimage, tempimage, Size(3, 3), 0);
	// ����X������ݶ�
	Sobel(tempimage, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, grad_x);
	// ����Y������ݶ�
	Sobel(tempimage, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, grad_y);
	// �ϲ�
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, gradiant);

	imshow("Sobel gradient", gradiant);

}
// Laplace ��Ե���
void Laplace_edage_detction()
{
	Mat temP_image;
	temP_image= imread(path,0);
	Mat mydst;
	Laplacian(temP_image, mydst, CV_16S, 3, 1, 0, BORDER_DEFAULT);


	convertScaleAbs(mydst,mydst);


	imshow("Laplace Image", mydst);

}
// Schaar���� ������x�����y����Ĳ�֣����Կ����̶�ksize��Sobel����
void Scharr_edage_detection()
{
	// ����һЩ����
	Mat temp = grayimage.clone();
	Mat grad_x;
	Mat grad_y;

	GaussianBlur(temp, temp, Size(3, 3), 0);

	// X����Ĳ��
	Scharr(temp, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, grad_x);
	// Y����Ĳ��
	Scharr(temp, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, grad_y);
	// �ϲ�����
	imshow("X����", grad_x);
	imshow("Y����", grad_y);
	Mat merge;
	addWeighted(grad_x, 0.5, grad_y, 0.5,0,merge);
	imshow("Merge", merge);




}
