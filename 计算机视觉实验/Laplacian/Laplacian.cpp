#include<iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
	
Mat src,src2,src_gray, dst, abs_dst;//创建矩阵
int GaussianBlurValue = 1;  //高斯滤波参数值

static void Laplacianfunc(int, void*)
{
	//高斯滤波操作
	GaussianBlur(src, src2, Size(GaussianBlurValue * 2 + 1, GaussianBlurValue * 2 + 1), 0, 0);
	//转换为灰度图
	cvtColor(src2, src_gray, COLOR_RGB2GRAY);
	//使用Laplace函数
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	//计算绝对值，并将结果转换成8位
	convertScaleAbs(dst, abs_dst);
	//显示窗口
	imshow("Laplacian边缘检测", abs_dst);
}

int main()
{
	printf("\n\n\t\t\t	 此为实验示例程序\n");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n\t\t\t   当前实验为：Laplacian边缘检测");
	printf("\n\n  ----------------------------------------------------------------------------\n");


	//载入原始图  
	src = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图
	if (!src.data) { cout << "读取错误！无法读取到图像！" << endl; return false; }

	//显示原始图 
	imshow("原始图", src);

	//创建窗口
	namedWindow("Laplacian边缘检测", 1);
	//创建轨迹条
	createTrackbar("参数：", "Laplacian边缘检测", &GaussianBlurValue, 5, Laplacianfunc);
	Laplacianfunc(0, 0);

	waitKey(0);
	return 0;
}

