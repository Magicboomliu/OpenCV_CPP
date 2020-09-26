#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;

// ��˹��������������˹�������ĺ��壺

//(1)��˹������(Gaussianpyramid): �������²�������Ҫ��ͼ�������
//��Ҫ���Ⱦ����ȥ��ż���к�ż����


//(2)������˹������(Laplacianpyramid) : �����ӽ������Ͳ�ͼ���ؽ��ϲ�δ����ͼ��
//������ͼ������Ҳ����Ԥ��в���Զ�ͼ��������̶ȵĻ�ԭ��
//��ϸ�˹������һ��ʹ�á�ÿһ�㶼�ǲв�

// ����ͼ�������
void pyramid()
{
	String path = "images/street.jpg";
   // ����һ�����飬��4��˹�������
	Mat GuassianPyramid[4];
	GuassianPyramid[0] = imread(path);
	
	// ����һ��Gaussian Pyramid Array
	for (int i = 1;i < 4;i++)
	{
		pyrDown(GuassianPyramid[i - 1], GuassianPyramid[i],
		Size(GuassianPyramid[i - 1].cols / 2, GuassianPyramid[i - 1].rows / 2));
	}
	// ����һ�� Laplace Pyramid Array
	Mat LaplacePyramid[3];
	for (int i = 0;i < 3;i++)
	{
		Mat upsample_Image;
		// �ϲ���
		pyrUp(GuassianPyramid[i + 1], upsample_Image, Size(GuassianPyramid[i + 1].cols * 2, GuassianPyramid[i + 1].rows * 2));

		Mat residual;
		resize(upsample_Image, upsample_Image, Size(GuassianPyramid[i].size()));

		residual = GuassianPyramid[i] - upsample_Image;

		LaplacePyramid[i] = residual;

	}

	 //��ʾ��˹������
	int height = GuassianPyramid[0].rows;
	int width = 0;
	for (int i = 0;i < 4;i++) {

		width += GuassianPyramid[i].cols;
	
	}
	Mat black_holder(height, width, CV_8UC3,Scalar::all(0));
	//ÿ������ʼ������
	int X_beigin = 0;
	int y_beigin = 0;

	// ���ȶ���һ������
	Mat imageROI;
    imageROI = black_holder(Rect(X_beigin, y_beigin, GuassianPyramid[0].cols, GuassianPyramid[0].rows));
	
	GuassianPyramid[0].copyTo(imageROI);
	
	for (int i = 1;i < 4; i++) {
		X_beigin += GuassianPyramid[i-1].cols;
		Mat imageROI = black_holder(Rect(X_beigin, y_beigin, GuassianPyramid[i].cols, GuassianPyramid[i].rows));
		 GuassianPyramid[i].copyTo(imageROI);
	}
	
	imshow("Gaussian Pyrmaid ͼ�������", black_holder);

	//white_holder
	int wheight = GuassianPyramid[0].rows;
	int wwidth = 0;
	for (int i = 0;i < 3;i++) {

		wwidth += LaplacePyramid[i].cols;

	}
	Mat white_holder(height, width, CV_8UC3, Scalar::all(255));

	int xx_bei=0;
	int yy_bei=0;


	// ImageROI

	Mat wImageROI = white_holder(Rect(xx_bei, yy_bei, LaplacePyramid[0].cols, LaplacePyramid[0].rows));

	LaplacePyramid[0].copyTo(wImageROI);

	for (int i = 1;i < 3;i++)
	{
		xx_bei += LaplacePyramid[i - 1].cols;
		Mat wImageROI = white_holder(Rect(xx_bei, yy_bei, LaplacePyramid[i].cols, LaplacePyramid[i].rows));

		LaplacePyramid[i].copyTo(wImageROI);

	}

	imshow("Laplace������ ", white_holder);


	waitKey(0);

}