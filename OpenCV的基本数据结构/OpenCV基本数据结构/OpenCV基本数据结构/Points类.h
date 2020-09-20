#pragma once
#include<opencv2\opencv.hpp>
#include<string>
#include<opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

void create_some_points()
{
	//1.Ĭ�Ϲ��캯��
	Point2i p1;//����Ϊ[0,0], ��ʾһ����ά�ĵ�
	Point3f p2;//����Ϊ[0,0,0], ����һ����ά�ĵ�
	cout << p1 << '\n' << p2 << endl;

	//2.��ֵ���캯��
	Point3f p3(1, 2, 3);//����Ϊ[1,2,3]
	Point3f p4(p3);//����Ϊ[1,2,3]
	cout << p3 << "\n" << p4 << endl;

	//3,�������Ĺ��캯��
	Point2i p5(1, 2);//����Ϊ[1,2]
	Point3f p6(1.1, 1.2, 1.3);//����Ϊ[1.1,1.2,1.3]
	cout << p5 << '\n' << p6 << endl;

	//4����ʽ����ת��,ת��ΪVec3f
	Vec3f v = p6;//����Ϊ[1.1,1.2,1.3]
	cout << v << endl;

	//5,��Ա��������
	cout << p5.x << '\t' << p5.y << endl;
	cout << p6.x << '\t' << p6.y << '\t' << p6.z << endl;

	//6.��� --��������������������֮��ļн�
	Point3f p7(2.0f, 3.0f, 4.0f);
	float value = p6.dot(p7);  // �������ڻ�
	cout << value << endl;

	//7.ʮ����� ������������ά��Ӱ��
	//����������������Ĵ�ֱ����
	Point3f p8(1, 0, 0);//x����ĵ�λ����
	Point3f p9(0, 1, 0);//Y����ĵ�λ����
	Point3f p10 = p8.cross(p9);//���������Z����ĵ�λ����
	cout << p10 << endl;

	//8.�жϵ��Ƿ��ھ����� �����������ά��
	Rect2f r(0, 0, 1, 1);//ע�⣬������캯����(x,y,width,height)X����ϵ����Ϊ����Y����ϵ����Ϊ��
	Point2f p(0.5, 0.5);
	bool bValue = p.inside(r);//����Ϊtrue
	cout << bValue << endl;;
	p.x = 2;
	bValue = p.inside(r);//����Ϊfalse
	cout << bValue << endl;



}