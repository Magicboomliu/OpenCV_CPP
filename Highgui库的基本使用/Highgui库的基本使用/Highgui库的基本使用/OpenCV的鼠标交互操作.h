#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;

#define WINDOWS_NAME "MYMOUSE"
//����һЩȫ�ֺ���

// ����¼��Ļص�����
void on_MouseHandle(int event, int x, int y, int flags, void*);

// ��һ�����Σ�
void DrawRectangle(Mat &img, Rect box);

// �����û����MYMOUSE
void ShowHelpText();

//����һЩȫ�ֱ���

Rect g_rectangle;
bool g_draw = false; //�Ƿ���л滭
RNG g_rng(12345);  // ����һ���������seed=12345
//ִ�к���
void play() {

	g_rectangle = Rect(-1, -1, 0, 0);
	
	Mat srcImage(600, 800, CV_8UC3), tempImage;
	
	srcImage.copyTo(tempImage);

	g_rectangle = Rect(-1, -1, 0, 0);
	
	// srcΪһ����ɫͼ��
	srcImage = Scalar::all(0);

	// �������ص�����
	namedWindow(WINDOWS_NAME);
	
	//�� srcimage���в����� void*�������Ϊ�û���Ϊ
	setMouseCallback(WINDOWS_NAME, on_MouseHandle, (void*)&srcImage);
    
	// ���л��Ƶ�ʶ���Ϊ�棬��ʼ����
	while (1)
	{
		srcImage.copyTo(tempImage); //���Ƶ���ʱ����
		if (g_draw) {
			//������
			DrawRectangle(tempImage, g_rectangle);

		}
		imshow(WINDOWS_NAME, tempImage);
		if (waitKey(10) == 27) { break; }

	}

}

//ʵ�����ص�����
void on_MouseHandle(int event, int x, int y, int flags, void* para) {
	// ��ַ����
	Mat& image = *(Mat*) para;
	
	// ����ʱ�����ͽ�����Ӧ
	switch (event)
	{
	case EVENT_MOUSEMOVE:   //����ƶ��¼�
	{ 
		// ���¾��εĴ�С
		if (g_draw) {
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
		break;
	case EVENT_LBUTTONDOWN:  // �����������¼�
	{
	      //����֤�����ڻ�ͼ
		g_draw = true;
		g_rectangle = Rect(x, y, 0, 0);// ��¼��ǰ����㣬��ʼ��rect����Ϊ0
	}	
		break;
	case EVENT_LBUTTONUP:  // ������̧��
		
	{
		//���ڻ滭����Ϊfalse
		g_draw = false;
		//�Գ��Ϳ�С��0�Ĵ���
		if (g_rectangle.width < 0) {

			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;

		}
		if (g_rectangle.height < 0) {

			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		//���û�ͼ����
		DrawRectangle(image, g_rectangle);
	}
		
		break;
	default:
		break;
	}
}

// ʵ�ֻ�ͼ����
void DrawRectangle(Mat &img, Rect box) {

	//tl()  : top left ���Ͻǵ�����      br(): bottom right ���½����
	int r = g_rng.uniform(0, 255);
	int g= g_rng.uniform(0, 255);
	int b = g_rng.uniform(0, 255);
	rectangle(img, box.tl(), box.br(), Scalar(r,g,b));

}