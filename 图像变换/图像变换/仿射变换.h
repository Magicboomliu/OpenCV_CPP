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


// 仿射变化
void affine_transfrom()
{
	Mat srcimage;
	Mat dstimage;
	Mat aff_mat;

	string path = "images/anime.jpg";
	srcimage = imread(path);
	// 原始三角形
	Point2f  tra1[3];
	// 对应的三角选哪个
	Point2f tra2[3];
	
	// 原始图像中的三角形
	tra1[0] = Point2f(0, 0);
	tra1[1] = Point2f(static_cast<float>(srcimage.cols - 1), 0);
	tra1[2] = Point2f(0, static_cast<float>(srcimage.rows - 1));

	// 对应要变换的三角形
	tra2[0] = Point(0, 0);
	tra2[1] = Point(static_cast<float>(srcimage.cols *0.5), 0);
	tra2[2] = Point2f(static_cast<float>(srcimage.cols *0.5), static_cast<float>(srcimage.rows - 1));

	// 得到2*3的 affine matrix
	aff_mat = getAffineTransform(tra1, tra2);

	// 对原图进行仿射变换
	warpAffine(srcimage, dstimage, aff_mat, srcimage.size());

	imshow("Affine transfrom", dstimage);
	

	// 对原图进行欧几里何变换，也就是rotation
	// 说明旋转中心以及旋转角度，是都缩放
	Point2f center(dstImage.cols / 2, dstimage.rows / 2);
	double angel = 30; // 负数为顺时针，正数为逆时针
	double scale = 0.8; // 缩放尺寸
	Mat rotMat;
	rotMat = getRotationMatrix2D(center, angel, scale);
	Mat after_rotation;
	warpAffine(dstimage, after_rotation, rotMat, dstimage.size());

	imshow("rotation_after_affine", after_rotation);


	waitKey(0);


}