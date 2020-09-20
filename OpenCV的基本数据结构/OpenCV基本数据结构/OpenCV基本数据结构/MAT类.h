#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<string>
#include<opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

// ��opencv�� ��ͼ�λ����Ǿ�����Ҫ��Mat����ʽ�洢
void create_a_Mat_() {

	// int rows, int cols,int dtype, int color
	Mat mymat1(3, 2, CV_8UC3, Scalar(0, 0, 255));

	// SizeΪ3��2
	Mat  mymat2(Size(3, 2), CV_8UC3, Scalar(255, 0, 0));
	Mat  mymat3(mymat2);
	Mat mymat4(mymat1.size(), CV_8UC3, Scalar(0, 255, 0));
	cout << "mymat1 is :" << endl << mymat1 << endl << endl;
	cout << "mymat2 is :" << endl << mymat2 << endl << endl;
	//ʹ��create����
	Mat mymat5;
	mymat5.create(3,3, CV_8UC3);

	// ����һЩ����ľ���

	Mat mymat6 = Mat::zeros(Size(4, 3), CV_32F);
	Mat mymat7 = Mat::eye(Size(4, 4), CV_32F); //Ĭ�ϵ�λ����
	Mat mymat8 = Mat::ones(Size(4, 3), CV_32F);
	cout << "Zeros :" << endl << mymat6 << endl << endl;
	cout << "Eye :" << endl << mymat7 << endl << endl;
	cout << "Ones :" << endl << mymat8 << endl << endl;

   // ��ֵ���µľ��󣬵��������ݹ���
	Mat tempMat1;
	mymat7.copyTo(tempMat1);
	Mat tempMat2;
	tempMat2 = mymat8.clone();
	Mat temprow; Mat tempcol;
	temprow = mymat1.row(0).clone();
	tempcol = mymat1.col(1).clone();


	// �Զ����Mat

	Mat m1 = (Mat_<double>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
	cout << "m1 is :" << m1 << endl;
	
	

}

// ��ʽ�����,��ͬ��� ��Python ,Matlab, Numpy.
void print_in_different_ways()
{

	//ʹ�ú���randu()���������,�������ΧΪ0-255
	Mat R = Mat(3, 2, CV_8UC3);
	randu(R, Scalar::all(0), Scalar::all(255));

	//��Ĭ�ϸ�ʽ���
	cout << "R(Default) = " << endl << " " << R << endl << endl;

	//��Python��ʽ���
	cout << "R(Python) = " << endl <<format(R, Formatter::FMT_PYTHON) << endl << endl;

	//��CSV��ʽ���
	cout << "R(CSV) = " << endl << format(R, Formatter::FMT_CSV) << endl << endl;

	//��Numpy��ʽ���
	cout << "R(Numpy) = " << endl << format(R, Formatter::FMT_NUMPY) << endl << endl;

	//��MATLAB�ĸ�ʽ���
	cout << "R(C) = " << endl << format(R, Formatter::FMT_MATLAB) << endl << endl;
}