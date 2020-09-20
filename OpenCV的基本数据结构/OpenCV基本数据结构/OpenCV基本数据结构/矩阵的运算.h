#pragma once
#include<opencv2\opencv.hpp>
#include<string>
#include<opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

// �йؾ��������, ע���ڽ�������ʱ����ý�Mat����������ת��Ϊ��������

void basic_math_on_Matrix()
{
	//����һ����λ����
	Mat m1 = Mat::eye(Size(4,4), CV_8UC1);
	Mat m2 = (Mat_<int>(4, 4) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 15, 16);
	m2.convertTo(m2, CV_8UC1);

	cout <<"M1:     " <<m1<< endl << endl;
	cout << "M2:     " << m2 << endl << endl;
	Mat outcome;
	
	// (1) ����ӷ�
	/*outcome = m1 + m2;*/
	cout << "����ӷ�    " << "outcome is: " << endl;
	add(m1, m2, outcome);
	cout << outcome << endl << endl;

	// (2) �������
	//outcome = m2 - m1;
	cout << "�������    " << "outcome is: " << endl;
	subtract(m2, m1, outcome);
	cout << outcome << endl<<endl;

	//(3)����˷�
	m1.convertTo(m1, CV_32F);
	m2.convertTo(m2, CV_32F);
	outcome = m1 * m2;


	cout << "����˷�  " << "outcome is " << endl;
	cout << outcome << endl << endl;

	int result;
	result = m1.dot(m2);
	cout << "�����˷�  " << "outcome is " << endl;
	cout << result << endl << endl;

	outcome = m1.mul(m2);
	cout << "�����Ӧλ�����  " << "outcome is " << endl;
	cout << outcome << endl << endl;

	//��4�����������ת��
	m1.convertTo(m1, CV_32F);

	// (5) �����ת��
	m2.t();
	
	//(6)����ת
	int flipCode = 1;
	flip(m2, outcome,  flipCode);//flipCode=0�����·�ת��>0ʱ���ҷ�ת,<0ʱһ����
	 
	// (7)��������
	invert(m1, outcome);
	cout << "����M1�Ŀ������  " << "outcome is " << endl;
	cout << outcome << endl << endl;

	// (8)���������ֵ����������
	Mat eigenValues;
	Mat eigenVectors;

	eigen(m1, eigenValues, eigenVectors);

	cout << "����M1������ֵ  " << " is " << endl;
	cout << eigenValues << endl << endl;

	cout << "����M1��������ֵ  " << " is " << endl;
	cout << eigenVectors << endl << endl;

	
	// ����������ʽ��ֵ��trace
	double h;
	h = determinant(m1);

	cout << "����M1������ʽ��ֵ  " << " is " << endl;
	cout << h << endl << endl;

	Scalar h2 = trace(m1);

	cout << "����M1��trace  " << " is " << endl;
	cout << h2 << endl << endl;

}