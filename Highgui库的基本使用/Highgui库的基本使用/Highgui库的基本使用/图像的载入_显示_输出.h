#pragma once
#include<iostream>
using namespace std;
#include<string>
// ����ͷ�ļ���core����Լ�highgui ��hpp�ļ�
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

// ʹ��opencv�ı�׼�����ռ�cv
using namespace cv;
void show_and_save_image()
{
 /*    ��opencv���ļ���·�������������ģ������*/	

	string huihui_path = "images/anime.jpg";
    // ͼ��Ĭ��Ϊ��һ��Mat����
	Mat huihui = imread(huihui_path);   // Ĭ��Ϊ1����Ϊ����Ĳ�ɫͼ��
	// Ч����ͬ   Mat huihui = imread(huihui_path,1);	
	//��ʾ��ɫͼƬ
	/*Mat huihui_gray = imread(huihui_path, 0);*/
	// ��ʾ��Alphaͨ����ͼƬ
	//Mat huihui_alpha = imread(huihui_path, -1);

	namedWindow("����ħ��ʹ", WINDOW_AUTOSIZE); //����һ��������ħ��ʹ���Ĵ���
	
	imshow("����ħ��ʹ", huihui);  //չʾ����ͼƬ�����봰�ڵ���Ϣ


	/*  ͼ����ں� */
	Mat backgroud = imread("images/street.jpg");
	Mat foreground = imread("images/person.jpg");

	
	// �鿴ͼ��ĳߴ��ά��
	cout << foreground.size() << endl;   // ��һ��������cols,�ڶ���������rows
	cout << backgroud.dims << endl; //���ͼ���ά��,Ϊ2ά��
	//�鿴ͼ��Ŀ�ͳ�
	cout << backgroud.rows <<" "<< backgroud.cols << endl;
	//���¶���foregound�Ĵ�С��ע�����resize������Ҫʹ��imgprocͷ�ļ�
	resize(foreground, foreground, Size(100, 100));


	imshow("����ͼƬ", backgroud);
	imshow("ǰ��ͼƬ", foreground);

	// ����һ��ͼ��ROI    ,ǰ2������Ϊ��ʼ��Y��X���꣬����2������Ϊrect�ĸߺͿ�
	Mat ImageROI = backgroud(Rect(10, 10, foreground.cols, foreground.rows));


	// ��ImageROI�滻Ϊforeground
	// para1: ��һ��ͼƬ    para2:Ȩ��  para3: �ڶ���ͼƬ��para4Ȩ�� para5ÿ�����ؼ�ֵ�����һ��para6 ����Ԫ��
	addWeighted(ImageROI, 0.3, foreground, 0.5, 3, ImageROI);

	// ��Ӻ��Ч��
	imshow("��Ӻ��Ч��", backgroud);

	// �����ڱ���
	imwrite("after/merged.jpg", backgroud);

	waitKey(0); // �����������
	
}