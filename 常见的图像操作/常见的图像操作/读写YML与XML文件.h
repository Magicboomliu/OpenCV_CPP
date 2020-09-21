#pragma once
#include<iostream>
#include<opencv2\opencv.hpp>
#include<time.h>
#include<string>
#include<vector>
#include<map>
using namespace std;
using namespace cv;
// 写XML文件或是yaml
void wirte_XML(int i)
{
	string verison;
	// 创建一个文件流，开始写入操作
	if (i == 1) {
		verison = "test.xml";
	}
	else
	{
		verison = "test.yaml";
	}
	FileStorage fs(verison
, FileStorage::WRITE);
	// 写入一个数据
	fs << "framecout" << 5;

	// 写入一个矩阵
	Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	fs << "cameraMatrix" << cameraMatrix;
	
	// 写入一个vector
	fs << "features" << "[";
	fs << 1312 << 123 << 3123 << 888 << 313 << 187 << "]";

	// 写入一个mapping
	fs << "mapping" << "{";
	fs << "one" << 1 << "two" << 2 << "}";

	// 关闭文件
	fs.release();
}

// 读取一个XML文件

void read_XML()
{

	FileStorage fs("test.xml", FileStorage::READ);
	// 读取数据
	int framecout;
	fs["framecout"] >> framecout;
	cout << framecout << endl;

	// 读取矩阵
	Mat mymat;
	fs["cameraMatrix"] >> mymat;



	//读取map和vec

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