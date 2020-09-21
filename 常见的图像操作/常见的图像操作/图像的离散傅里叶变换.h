#pragma once
#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
#include<vector>
using namespace std;
using namespace cv;

void Fourier_transform()
{
	//����һ�ŻҶ�ͼ��
	string myimage = "images/person.jpg";
	Mat DTrump = imread(myimage,0);

	//                 Step1 ����ͼƬ�ĳߴ�
	//��ͼ��ߴ�Ϊ2��3��5�ı���ʱ���Եõ����Ĵ����ٶȣ�
	//����ͨ��getOptimalDFTSize()������ȡ���DFT�任�ߴ磬
	//֮���ٽ��copyMakeBorder()������ͼ��������䡣
	int optimal_rows = getOptimalDFTSize(DTrump.rows);
	int  optimal_cols = getOptimalDFTSize(DTrump.cols);


	// ����ͼ����������ұ������Ҫ���к���
	Mat padded_image;
	copyMakeBorder(DTrump, padded_image, 0, optimal_cols - DTrump.cols, 0, optimal_rows - DTrump.rows, BORDER_CONSTANT, Scalar::all(0));
	cout << "���is OK" << endl;
	// Ϊʵ�����鲿����ռ�

	//����Ҷ�任�Ľ���Ǹ�����
	//�����ζ�ž�������Ҷ�任ÿ��ͼ��ֵ����������ֵ��
	//������Ƶ��(frequency domains)��Χ�ȿռ���(spatial counterpart)��Χ��ܶࡣ
	//����ͨ���Ը��������ݸ�ʽ�Խ�����д洢��
	//������ǽ�����ͼ��ת��Ϊ�������ͣ�ͨ�������ͨ������ͼ��
	Mat pl[] = {Mat_<float>(padded_image),Mat::zeros(padded_image.size(), CV_32F) };
	Mat complex;
	merge(pl, 2, complex);
	
	


	// ����fouier transform
	dft(complex, complex);

	// ����ʵ�����鲿��������ֵ�������ֵ��ʵ���鲿����ƽ����ƽ������
	split(complex, pl);
	magnitude(pl[0], pl[1], pl[0]);
	Mat magnitudeImage = pl[0];

	// ʹ��exp��������������
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);


	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows&-2));

	// ���������Ǹ�ԭ��λ������
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;

	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));  //����
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));// ����
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));// ����
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));// ����

	// ���޽���
	Mat temp;
	q0.copyTo(temp);
	q3.copyTo(q0);
	temp.copyTo(q3);

	q1.copyTo(temp);
	q2.copyTo(q1);
	temp.copyTo(q2);


	// ��һ��
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);
	imshow("Ƶ�ʷ���ͼ", magnitudeImage);
	imshow("ԭͼ", DTrump);
	waitKey(0);




}