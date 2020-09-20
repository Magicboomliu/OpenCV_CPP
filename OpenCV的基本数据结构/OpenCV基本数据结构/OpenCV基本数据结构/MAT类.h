#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<string>
#include<opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

// 在opencv中 ，图形或者是矩阵主要以Mat的形式存储
void create_a_Mat_() {

	// int rows, int cols,int dtype, int color
	Mat mymat1(3, 2, CV_8UC3, Scalar(0, 0, 255));

	// Size为3，2
	Mat  mymat2(Size(3, 2), CV_8UC3, Scalar(255, 0, 0));
	Mat  mymat3(mymat2);
	Mat mymat4(mymat1.size(), CV_8UC3, Scalar(0, 255, 0));
	cout << "mymat1 is :" << endl << mymat1 << endl << endl;
	cout << "mymat2 is :" << endl << mymat2 << endl << endl;
	//使用create函数
	Mat mymat5;
	mymat5.create(3,3, CV_8UC3);

	// 构造一些特殊的矩阵

	Mat mymat6 = Mat::zeros(Size(4, 3), CV_32F);
	Mat mymat7 = Mat::eye(Size(4, 4), CV_32F); //默认单位矩阵
	Mat mymat8 = Mat::ones(Size(4, 3), CV_32F);
	cout << "Zeros :" << endl << mymat6 << endl << endl;
	cout << "Eye :" << endl << mymat7 << endl << endl;
	cout << "Ones :" << endl << mymat8 << endl << endl;

   // 赋值给新的矩阵，但不是数据共享
	Mat tempMat1;
	mymat7.copyTo(tempMat1);
	Mat tempMat2;
	tempMat2 = mymat8.clone();
	Mat temprow; Mat tempcol;
	temprow = mymat1.row(0).clone();
	tempcol = mymat1.col(1).clone();


	// 自定义的Mat

	Mat m1 = (Mat_<double>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
	cout << "m1 is :" << m1 << endl;
	
	

}

// 格式化输出,不同风格 ：Python ,Matlab, Numpy.
void print_in_different_ways()
{

	//使用函数randu()生成随机数,随机数范围为0-255
	Mat R = Mat(3, 2, CV_8UC3);
	randu(R, Scalar::all(0), Scalar::all(255));

	//以默认格式输出
	cout << "R(Default) = " << endl << " " << R << endl << endl;

	//以Python格式输出
	cout << "R(Python) = " << endl <<format(R, Formatter::FMT_PYTHON) << endl << endl;

	//以CSV格式输出
	cout << "R(CSV) = " << endl << format(R, Formatter::FMT_CSV) << endl << endl;

	//以Numpy格式输出
	cout << "R(Numpy) = " << endl << format(R, Formatter::FMT_NUMPY) << endl << endl;

	//以MATLAB的格式输出
	cout << "R(C) = " << endl << format(R, Formatter::FMT_MATLAB) << endl << endl;
}