#pragma once
#pragma once
#include<opencv2\opencv.hpp>
#include<string>
#include<opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

void use_scalar()
{
	Mat mymatSclar1(Size(3, 3), CV_8UC1, Scalar(1));
	Mat mymarSclar2 (3, 3, CV_8UC2, Scalar(1, 2));
	Mat mymatSclar3(3, 3, CV_8UC3, Scalar(1, 2,3));

	cout << mymatSclar1 << endl << endl;
	cout << mymarSclar2 << endl << endl;
	cout << mymatSclar3 << endl << endl;

	Mat BlueSc(Size(100,100), CV_8UC3, Scalar(0,0,255));
	Mat GreenSc(200,200, CV_8UC3, Scalar(0,255, 0));
	Mat RedSc(100,100, CV_8UC3, Scalar(255, 0, 0));

	imshow("Blue", BlueSc);
	imshow("Green", GreenSc);
	imshow("Red", RedSc);

	waitKey(0);


}