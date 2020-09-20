#pragma once
#include<opencv2\opencv.hpp>
#include<string>
#include<opencv2\highgui\highgui.hpp>
#include<string>
using namespace std;
using namespace cv;

uchar sat(uchar c1){
	uchar s1=saturate_cast<uchar>(c1);
	return s1;
}


void traverse_pixels_in_matrix()
{
	
	string image_path = "images/street.jpg";
	Mat mystreet = imread(image_path, 1);


	Mat temp1 = mystreet.clone();
	// ��������һ�� ʹ��ָ����б���
	int myrow = mystreet.rows;
	int mycols = mystreet.cols *mystreet.channels();
	for (int i = 0;i < myrow;i++) 
	{
		uchar* col = temp1.ptr<uchar>(i);
		for (int j = 0;j < mycols;j++)
		{
			// ʹ��saturate_cast������ֹ���
			col[j] = saturate_cast<uchar>(col[j] * 2);
		}
	}
	imshow("After", temp1);

	// ���������� ʹ�õ�����
	Mat temp2 = mystreet.clone();
	Mat_<Vec3b>::iterator itbeign1 = temp2.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = temp2.end<Vec3b>();

	while (itbeign1 != itend)
	{
		// itbeign ��һ��Vec3b���͵�ָ�� ��ָ��BGR
		itbeign1++;
		(*itbeign1)[0]=saturate_cast<uchar>((*itbeign1)[0]*1.4);
		(*itbeign1)[1] = saturate_cast<uchar>((*itbeign1)[1] * 1.4);
		(*itbeign1)[2] = saturate_cast<uchar>((*itbeign1)[2] * 1.4);
	}

	imshow("After2", temp2);

	// �����ַ�ʽ��ʹ��at+[] ��̬��ȡ

	Mat temp3;
	temp3 = mystreet.clone();

	for (int i = 0;i < temp3.rows;i++)
	{

		for (int j = 0;j < temp3.cols;j++)
		{

			temp3.at<Vec3b>(i, j)[0] = 0;
			//temp3.at<Vec3b>(j, i)[0]=255;
	/*		temp3.at<Vec3b>(j,i)[1] = temp3.at<Vec3b>(j,i)[1] * 1.01;
			temp3.at<Vec3b>(j,i)[2] = temp3.at<Vec3b>(j,i)[2] * 1.01;*/

		}
	}

	imshow("afer", temp3);


	waitKey(0);



}