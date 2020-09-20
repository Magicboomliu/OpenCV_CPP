#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;

	const int g_nMaxAlphaValue = 100;  // Alpha������ֵΪ100
	int  g_nAlphaSlider;  //��������Ӧ�ı���

	// ����Ȩ�ر���
	double g_dAlphaValue;
	double g_BetaValue;

	Mat g_srcImage1;  // Ҫ���л�ϵĵ�һ��ͼƬ
	Mat g_srcImage2;  // Ҫ���л�ϵĵڶ���ͼƬ
	Mat g_dstImage;;  // ��Ϻ��ͼƬ
	
	// ���廬�����϶���Ļص�����
	void on_Trackbar( int, void* )//ע�����������void* ,����usrdata}
		
	{
		// ��������û�������AlphaValue��BetaValue��ֵ
		g_dAlphaValue = (double)g_nAlphaSlider / g_nMaxAlphaValue;
		g_BetaValue = (1.0 - g_dAlphaValue);
		// �������������л�ϣ��õ�merged_image������dstImage
		addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_BetaValue, 0.0, g_dstImage);
		imshow("���Ի�Ϻ��ͼƬ", g_dstImage);
	}

	void showImage() {
		// ����2��ͼƬ��same size
		g_srcImage1 = imread("images/street.jpg");
		g_srcImage2 = imread("images/person.jpg");
		// �ı�image2�Ĵ�С��ʹ����image1һ����
		resize(g_srcImage2, g_srcImage2, Size(g_srcImage1.cols, g_srcImage1.rows));

		// ��ʼ����������ֵ
		g_nAlphaSlider = 0;

		// �ڴ����Ĵ����У�����һ��trackerbar
		char TrackerBarName[50]; // ע�����������char����
		sprintf_s(TrackerBarName, "͸����Ϊ%d", g_nMaxAlphaValue);

		// Ҫ���߱�����������һ��ͬ���Ĵ���
		namedWindow("���Ի�Ϻ��ͼƬ");

		createTrackbar(TrackerBarName, "���Ի�Ϻ��ͼƬ", &g_nAlphaSlider,
			g_nMaxAlphaValue, on_Trackbar );


		// ���ص�ǰtrackerbar��λ��
		int pos;
		pos = getTrackbarPos(TrackerBarName, "���Ի�Ϻ��ͼƬ");
		cout << pos << endl;



		// ����ڻص���������ʾ, 0 Ĭ��Ϊuserdata
		on_Trackbar(g_nAlphaSlider, 0);



		waitKey(0);

	}







