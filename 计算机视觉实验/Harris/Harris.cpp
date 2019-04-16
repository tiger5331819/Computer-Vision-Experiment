#include<iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat src, gray;
int thresh = 0; //阈值

static void CornerHarris(int, void*)
{
	Mat dst;//目标图
	Mat norm;//归一化后的图
	Mat scalede;//线性变换后的八位无符号整型的图
	Mat src1 = src.clone();

	////置零当前需要显示的两幅图，即清除上一次调用此函数时他们的值
	//dstImage = Mat::zeros(src.size(), CV_32FC1);
	//g_srcImage1 = g_srcImage.clone();

	//进行角点检测
	cornerHarris(gray, dst, 2, 3, 0.04, BORDER_DEFAULT);

	// 归一化与转换
	normalize(dst, norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(norm, scalede);//将归一化后的图线性变换成8位无符号整型 

	// 将检测到的，且符合阈值条件的角点绘制出来
	for (int j = 0; j < norm.rows; j++)
	{
		for (int i = 0; i < norm.cols; i++)
		{
			if ((int)norm.at<float>(j, i) > thresh + 80)
			{
				circle(src1, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scalede, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}
	//显示窗口
	imshow("Harris角点检测结果", scalede);
	imshow("最终结果", src1);
}
int main()
{
	printf("\n\n\t\t\t	 此为实验示例程序\n");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n\t\t\t   当前实验为：Harris角点检测");
	printf("\n\n  ----------------------------------------------------------------------------\n");


	//载入原始图  
	src = imread("1.jpg", 1);
	if (!src.data) { cout << "读取错误！无法读取到图像！" << endl; return false; }
	imshow("原始图", src);

	//将原图像转换为灰度图像
	cvtColor(src, gray, COLOR_BGR2GRAY);

	//创建窗口和滚动条
	namedWindow("最终结果", 1);
	createTrackbar("阈值: ", "最终结果", &thresh, 100, CornerHarris);
	CornerHarris(0, 0);

	waitKey(0);
	return 0;
}

