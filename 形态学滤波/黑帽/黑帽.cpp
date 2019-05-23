#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
int main()
{
	printf("\n\n\t\t\t	 此为实验示例程序\n");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n\t\t\t   当前实验为：形态学滤波：黑帽");
	printf("\n\n  ----------------------------------------------------------------------------\n");

	Mat dstImage;
	Mat srcImage = imread("1.jpg");
	if (!srcImage.data) { cout << "读取错误！无法读取到图像！" << endl; return false; }

	//显示原图
	imshow("原图", srcImage);

	//创建窗口
	namedWindow("黑帽");
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行形态学操作
	morphologyEx(srcImage, dstImage, MORPH_BLACKHAT, element);
	//显示效果图  
	imshow("黑帽", dstImage);

	waitKey(0);
	return 0;
}