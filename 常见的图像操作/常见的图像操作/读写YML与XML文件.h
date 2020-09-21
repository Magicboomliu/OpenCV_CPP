#pragma once
#include<iostream>
#include<opencv2\opencv.hpp>
#include<time.h>
#include<string>
#include<vector>
#include<map>
using namespace std;
using namespace cv;
// дXML�ļ�����yaml
void wirte_XML(int i)
{
	string verison;
	// ����һ���ļ�������ʼд�����
	if (i == 1) {
		verison = "test.xml";
	}
	else
	{
		verison = "test.yaml";
	}
	FileStorage fs(verison
, FileStorage::WRITE);
	// д��һ������
	fs << "framecout" << 5;

	// д��һ������
	Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	fs << "cameraMatrix" << cameraMatrix;
	
	// д��һ��vector
	fs << "features" << "[";
	fs << 1312 << 123 << 3123 << 888 << 313 << 187 << "]";

	// д��һ��mapping
	fs << "mapping" << "{";
	fs << "one" << 1 << "two" << 2 << "}";

	// �ر��ļ�
	fs.release();
}

// ��ȡһ��XML�ļ�

void read_XML()
{

	FileStorage fs("test.xml", FileStorage::READ);
	// ��ȡ����
	int framecout;
	fs["framecout"] >> framecout;
	cout << framecout << endl;

	// ��ȡ����
	Mat mymat;
	fs["cameraMatrix"] >> mymat;



	//��ȡmap��vec

	FileNode mp=fs["mapping"];

	cout << (int)mp["one"] << "one" << endl;
	cout << (int)mp["two"] << "one" << endl;;

	FileNode vec = fs["features"];

	for (FileNodeIterator it = vec.begin();it != vec.end();it++)
	{
		cout << (int)(*it) << endl;
	}
	fs.release();
	
}