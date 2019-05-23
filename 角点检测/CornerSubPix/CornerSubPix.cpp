#include<iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat g_srcImage, g_grayImage;
int thresh = 0; //阈值

void CornerSubPix(int, void*)
{
	if (thresh <= 1) { thresh = 1; }
	vector<Point2f> corners;
	double qualityLevel = 0.01;//角点检测可接受的最小特征值
	double minDistance = 10;//角点之间的最小距离

	Mat copy = g_srcImage.clone();

	//进行Shi-Tomasi角点检测
	goodFeaturesToTrack(g_grayImage,corners,thresh,qualityLevel,minDistance);

	//绘制检测到的角点
	RNG g_rng(12345);//随机器
	int r = 4;
	for (unsigned int i = 0; i < corners.size(); i++)
	{
		//以随机的颜色绘制出角点
		circle(copy, corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255),
			g_rng.uniform(0, 255)), -1, 8, 0);
	}

	//显示窗口
	imshow("亚像素级角点检测", copy);

	//亚像素角点检测的参数设置
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);

	//计算出亚像素角点位置
	cornerSubPix(g_grayImage, corners, winSize, zeroZone, criteria);

	//输出角点信息
	//for (int i = 1; i < corners.size(); i++)
	//{
	//	cout << " \t>>精确角点坐标[" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
	//}

}
int main()
{
	printf("\n\n\t\t\t	 此为实验示例程序\n");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n\t\t\t   当前实验为：亚像素级角点检测");
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//载入源图像并将其转换为灰度图
	g_srcImage = imread("1.jpg", 1);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

	//创建窗口和滑动条，并进行显示和回调函数初始化
	namedWindow("亚像素级角点检测", WINDOW_AUTOSIZE);
	createTrackbar("最大角点数", "亚像素级角点检测", &thresh, 500, CornerSubPix);
	imshow("原始图像", g_srcImage);
	CornerSubPix(0, 0);

	waitKey(0);
	return(0);
}
