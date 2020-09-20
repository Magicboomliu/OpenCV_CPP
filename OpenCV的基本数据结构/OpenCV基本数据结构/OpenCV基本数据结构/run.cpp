#include<iostream>
#include<string>
#include"MAT类.h"
#include"Points类.h"
#include"矩阵的运算.h"
#include "Scalar为矩阵赋值.h"
#include"OpenCV颜色空间转换.h"
#include "遍历每一个像素.h"
#include"利用遍历实现掩模.h"
#include"Opencv画图.h"
int main(int argc, char*argv)
{

	// Mat类的创建
	//create_a_Mat_();
	// 不同风格的输出模式
	//print_in_different_ways();

	// Points类
	//create_some_points();
	
    // 矩阵四则元素
	/*basic_math_on_Matrix();*/

	// Scalar为矩阵赋值
	//use_scalar();

	// cvtColor()函数
	//change_COLOR();

	// 遍历元素
	//traverse_pixels_in_matrix();

	// sharpen exercise
	//togeta_mask();

	draws();
	system("pause");
	return 0;
}