#include <iostream>
#include<iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	printf("\n\n\t\t\t	 此为实验示例程序\n");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n\t\t\t   当前实验为：Sobel边缘检测");
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//创建矩阵
	Mat x, y,dx, dy, dst;

	//载入原始图  
	Mat src = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图
	if (!src.data) { cout << "读取错误！无法读取到图像！" << endl; return false; }

	//显示原始图 
	imshow("原始图", src);

	//求X方向梯度
	Sobel(src, x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(x, dx);
	imshow("X方向Sobel", dx);

	//求Y方向梯度
	Sobel(src, y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(y, dy);
	imshow("Y方向Sobel", dy);

	//合并梯度(近似)
	addWeighted(dx, 0.5, dy, 0.5, 0, dst);
	imshow("所有方向Sobel", dst);

	waitKey(0);
	return 0;
}

