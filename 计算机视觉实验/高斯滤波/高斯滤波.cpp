#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat srcImage, dstImage;//存储图片的Mat类型
int GaussianBlurValue = 1;  //高斯滤波参数值

static void GaussianBlur(int, void*)
{
	//高斯滤波操作
	GaussianBlur(srcImage, dstImage, Size(GaussianBlurValue * 2 + 1, GaussianBlurValue * 2 + 1), 0, 0);
	//显示窗口
	imshow("高斯滤波", dstImage);
}

int main()
{
	printf("\n\n\t\t\t	 此为实验示例程序\n");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n\t\t\t   当前实验为：高斯滤波");
	printf("\n\n  ----------------------------------------------------------------------------\n");
	// 载入原图
	srcImage = imread("1.jpg");
	if (!srcImage.data) { cout << "读取错误！无法读取到图像！" << endl; return false; }

	//显示原图
	imshow("原图", srcImage);

	//创建窗口
	namedWindow("高斯滤波",1);
	//创建轨迹条
	createTrackbar("参数：", "高斯滤波", &GaussianBlurValue, 40, GaussianBlur);
	GaussianBlur(0, 0);

	waitKey(0);
	return 0;
}