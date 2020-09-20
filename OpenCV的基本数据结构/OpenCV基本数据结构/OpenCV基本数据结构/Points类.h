#pragma once
#include<opencv2\opencv.hpp>
#include<string>
#include<opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

void create_some_points()
{
	//1.默认构造函数
	Point2i p1;//数据为[0,0], 表示一个二维的点
	Point3f p2;//数据为[0,0,0], 便是一个三维的点
	cout << p1 << '\n' << p2 << endl;

	//2.赋值构造函数
	Point3f p3(1, 2, 3);//数据为[1,2,3]
	Point3f p4(p3);//数据为[1,2,3]
	cout << p3 << "\n" << p4 << endl;

	//3,带参数的构造函数
	Point2i p5(1, 2);//数据为[1,2]
	Point3f p6(1.1, 1.2, 1.3);//数据为[1.1,1.2,1.3]
	cout << p5 << '\n' << p6 << endl;

	//4，隐式类型转换,转换为Vec3f
	Vec3f v = p6;//数据为[1.1,1.2,1.3]
	cout << v << endl;

	//5,成员函数访问
	cout << p5.x << '\t' << p5.y << endl;
	cout << p6.x << '\t' << p6.y << '\t' << p6.z << endl;

	//6.点乘 --可以用来计算两个向量之间的夹角
	Point3f p7(2.0f, 3.0f, 4.0f);
	float value = p6.dot(p7);  // 向量的内积
	cout << value << endl;

	//7.十字相乘 仅仅适用与三维点影像
	//结果返回两个向量的垂直向量
	Point3f p8(1, 0, 0);//x方向的单位向量
	Point3f p9(0, 1, 0);//Y方向的单位向量
	Point3f p10 = p8.cross(p9);//计算出来的Z方向的单位向量
	cout << p10 << endl;

	//8.判断点是否在矩阵内 仅仅适用与二维点
	Rect2f r(0, 0, 1, 1);//注意，这个构造函数是(x,y,width,height)X坐标系向右为正，Y坐标系向上为正
	Point2f p(0.5, 0.5);
	bool bValue = p.inside(r);//返回为true
	cout << bValue << endl;;
	p.x = 2;
	bValue = p.inside(r);//返回为false
	cout << bValue << endl;



}