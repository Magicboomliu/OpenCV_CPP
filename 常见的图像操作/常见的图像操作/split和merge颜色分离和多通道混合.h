#pragma once
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<string>
#include<vector>
using namespace std;
using namespace cv;

void split_channels()
{
	// image path
	string image_path1 = "images/anime.jpg";
	Mat mypic = imread(image_path1, 1);
	
	vector<Mat> channels;
	
	// ����ΪBGR
	split(mypic, channels);
	// ��ȡBGRͨ��
	Mat ImageBlue = channels.at(0);
	Mat ImageGreen = channels.at(1);
	Mat ImageRed = channels.at(2);
	
	//�ϲ�ͨ��
	Mat merges;
	merge(channels, merges);

}