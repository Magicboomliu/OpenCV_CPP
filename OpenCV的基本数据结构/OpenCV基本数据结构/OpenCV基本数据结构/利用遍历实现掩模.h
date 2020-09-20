#pragma once
#include<opencv2\opencv.hpp>
#include<string>
#include<opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

void togeta_mask()
{
	string image_path_trump = "images/person.jpg";

	Mat trump = imread(image_path_trump);
	Mat Result;
	Result.create(trump.size(), trump.type());


	int rows = trump.rows;
	int cols = trump.cols * trump.channels();

	for (int i = 1; i < rows-1;i++) {

		uchar* previous_row = trump.ptr<uchar>(i - 1);
		uchar* current_row = trump.ptr<uchar>(i);
		uchar* next_row = trump.ptr<uchar>(i+1);

		uchar* output = Result.ptr<uchar>(i);
		for (int j = trump.channels();j < (trump.cols-1)*trump.channels();j++)
		{
			// 空间掩模
			output[j]=saturate_cast<uchar>(8 * current_row[j] - current_row[j - trump.channels()] -
		 current_row[j+ trump.channels()] - next_row[j] - previous_row[j]);

		}
	} 
	Result.row(0).setTo(Scalar(0));                 //设置第一行所有元素值为0
	Result.row(Result.rows - 1).setTo(Scalar(0));     //设置最后一行所有元素值为0
	Result.col(0).setTo(Scalar(0));                 //设置第一列所有元素值为0
	Result.col(Result.cols - 1).setTo(Scalar(0));     //设置最后一列所有元素值为0

	imshow("Sharpen", Result);
	imshow("orginal", trump);
	waitKey(0);


}