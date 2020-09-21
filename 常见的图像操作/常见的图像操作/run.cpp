#include<iostream>
using namespace std;
#include "ROI获取与更改.h"
#include "图像对比度亮度.h"
#include "图像的离散傅里叶变换.h"
#include"读写YML与XML文件.h"
int main(int argc, char**argv)
{

	//useROI();

	/*adjust_brightness_and_contrast();*/

	//Fourier_transform();
	wirte_XML(1);
	
	read_XML();
	
	system("pause");
	return 0;
}