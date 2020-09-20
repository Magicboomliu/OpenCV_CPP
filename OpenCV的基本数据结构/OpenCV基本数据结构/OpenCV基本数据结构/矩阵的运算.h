#pragma once
#include<opencv2\opencv.hpp>
#include<string>
#include<opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

// 有关矩阵的运算, 注意在进行运算时候，最好将Mat的数据类型转化为浮点数。

void basic_math_on_Matrix()
{
	//创建一个单位矩阵
	Mat m1 = Mat::eye(Size(4,4), CV_8UC1);
	Mat m2 = (Mat_<int>(4, 4) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 15, 16);
	m2.convertTo(m2, CV_8UC1);

	cout <<"M1:     " <<m1<< endl << endl;
	cout << "M2:     " << m2 << endl << endl;
	Mat outcome;
	
	// (1) 矩阵加法
	/*outcome = m1 + m2;*/
	cout << "矩阵加法    " << "outcome is: " << endl;
	add(m1, m2, outcome);
	cout << outcome << endl << endl;

	// (2) 矩阵减法
	//outcome = m2 - m1;
	cout << "矩阵减法    " << "outcome is: " << endl;
	subtract(m2, m1, outcome);
	cout << outcome << endl<<endl;

	//(3)矩阵乘法
	m1.convertTo(m1, CV_32F);
	m2.convertTo(m2, CV_32F);
	outcome = m1 * m2;


	cout << "矩阵乘法  " << "outcome is " << endl;
	cout << outcome << endl << endl;

	int result;
	result = m1.dot(m2);
	cout << "矩阵点乘法  " << "outcome is " << endl;
	cout << result << endl << endl;

	outcome = m1.mul(m2);
	cout << "矩阵对应位置相乘  " << "outcome is " << endl;
	cout << outcome << endl << endl;

	//（4）矩阵的类型转换
	m1.convertTo(m1, CV_32F);

	// (5) 矩阵的转置
	m2.t();
	
	//(6)矩阵翻转
	int flipCode = 1;
	flip(m2, outcome,  flipCode);//flipCode=0是上下翻转，>0时左右翻转,<0时一起来
	 
	// (7)矩阵求逆
	invert(m1, outcome);
	cout << "矩阵M1的可逆矩阵  " << "outcome is " << endl;
	cout << outcome << endl << endl;

	// (8)矩阵的特征值与特征向量
	Mat eigenValues;
	Mat eigenVectors;

	eigen(m1, eigenValues, eigenVectors);

	cout << "矩阵M1的特征值  " << " is " << endl;
	cout << eigenValues << endl << endl;

	cout << "矩阵M1的特征向值  " << " is " << endl;
	cout << eigenVectors << endl << endl;

	
	// 求矩阵的行列式的值和trace
	double h;
	h = determinant(m1);

	cout << "矩阵M1的行列式的值  " << " is " << endl;
	cout << h << endl << endl;

	Scalar h2 = trace(m1);

	cout << "矩阵M1的trace  " << " is " << endl;
	cout << h2 << endl << endl;

}