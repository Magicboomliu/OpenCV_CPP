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
	//输入一张灰度图像
	string myimage = "images/person.jpg";
	Mat DTrump = imread(myimage,0);

	//                 Step1 调整图片的尺寸
	//当图像尺寸为2、3、5的倍数时可以得到最快的处理速度，
	//所以通过getOptimalDFTSize()函数获取最佳DFT变换尺寸，
	//之后再结合copyMakeBorder()函数对图像进行扩充。
	int optimal_rows = getOptimalDFTSize(DTrump.rows);
	int  optimal_cols = getOptimalDFTSize(DTrump.cols);


	// 填充该图像，在下面和右边填充需要的行和列
	Mat padded_image;
	copyMakeBorder(DTrump, padded_image, 0, optimal_cols - DTrump.cols, 0, optimal_rows - DTrump.rows, BORDER_CONSTANT, Scalar::all(0));
	cout << "填充is OK" << endl;
	// 为实部与虚部分配空间

	//傅里叶变换的结果是复数，
	//这就意味着经过傅里叶变换每个图像值都会变成两个值，
	//此外其频域(frequency domains)范围比空间域(spatial counterpart)范围大很多。
	//我们通常以浮点型数据格式对结果进行存储。
	//因此我们将输入图像转换为这种类型，通过另外的通道扩充图像。
	Mat pl[] = {Mat_<float>(padded_image),Mat::zeros(padded_image.size(), CV_32F) };
	Mat complex;
	merge(pl, 2, complex);
	
	


	// 进行fouier transform
	dft(complex, complex);

	// 分离实部和虚部，将复数值计算幅度值（实部虚部算数平方和平法根）
	split(complex, pl);
	magnitude(pl[0], pl[1], pl[0]);
	Mat magnitudeImage = pl[0];

	// 使用exp函数，进行缩放
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);


	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows&-2));

	// 重新排列是个原点位于中心
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;

	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));  //左上
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));// 右上
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));// 左下
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));// 右下

	// 象限交换
	Mat temp;
	q0.copyTo(temp);
	q3.copyTo(q0);
	temp.copyTo(q3);

	q1.copyTo(temp);
	q2.copyTo(q1);
	temp.copyTo(q2);


	// 归一化
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);
	imshow("频率幅度图", magnitudeImage);
	imshow("原图", DTrump);
	waitKey(0);




}