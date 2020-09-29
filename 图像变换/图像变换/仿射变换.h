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


// ����仯
void affine_transfrom()
{
	Mat srcimage;
	Mat dstimage;
	Mat aff_mat;

	string path = "images/anime.jpg";
	srcimage = imread(path);
	// ԭʼ������
	Point2f  tra1[3];
	// ��Ӧ������ѡ�ĸ�
	Point2f tra2[3];
	
	// ԭʼͼ���е�������
	tra1[0] = Point2f(0, 0);
	tra1[1] = Point2f(static_cast<float>(srcimage.cols - 1), 0);
	tra1[2] = Point2f(0, static_cast<float>(srcimage.rows - 1));

	// ��ӦҪ�任��������
	tra2[0] = Point(0, 0);
	tra2[1] = Point(static_cast<float>(srcimage.cols *0.5), 0);
	tra2[2] = Point2f(static_cast<float>(srcimage.cols *0.5), static_cast<float>(srcimage.rows - 1));

	// �õ�2*3�� affine matrix
	aff_mat = getAffineTransform(tra1, tra2);

	// ��ԭͼ���з���任
	warpAffine(srcimage, dstimage, aff_mat, srcimage.size());

	imshow("Affine transfrom", dstimage);
	

	// ��ԭͼ����ŷ����α任��Ҳ����rotation
	// ˵����ת�����Լ���ת�Ƕȣ��Ƕ�����
	Point2f center(dstImage.cols / 2, dstimage.rows / 2);
	double angel = 30; // ����Ϊ˳ʱ�룬����Ϊ��ʱ��
	double scale = 0.8; // ���ųߴ�
	Mat rotMat;
	rotMat = getRotationMatrix2D(center, angel, scale);
	Mat after_rotation;
	warpAffine(dstimage, after_rotation, rotMat, dstimage.size());

	imshow("rotation_after_affine", after_rotation);


	waitKey(0);


}