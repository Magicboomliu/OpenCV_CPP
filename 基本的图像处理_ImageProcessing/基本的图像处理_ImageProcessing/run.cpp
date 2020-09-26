#include<iostream>
using namespace std;
#include"opencv滤波操作.h"
#include"腐蚀erode和膨胀dilate.h"
#include"高斯金字塔和拉普拉斯金字塔.h"
#include"形态学运算.h"
#include "阈值化操作.h"
int main(int argc, char**argv)
{ 
	//opencv滤波操作
	//myblurs();
	//腐蚀erode和膨胀dilate
	/*erode_and_dilate();*/
	// 更多的形态学运算
	//morphlology_operation();

	// 图像金字塔
	/*pyramid();*/

	//阈值化操作
	Threshold_adjust();

	return 0;
}
