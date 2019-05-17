#include<iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat g_srcImage, g_grayImage;
int thresh = 0; //阈值


void Shi_Tomasi(int, void*)
{
	if (thresh <= 1) { thresh = 1; }

	vector<Point2f> corners;
	double qualityLevel = 0.01;//角点检测可接受的最小特征值
	double minDistance = 10;//角点之间的最小距离
	Mat copy = g_srcImage.clone();

	//进行Shi-Tomasi角点检测
	goodFeaturesToTrack(g_grayImage,corners,thresh,qualityLevel,minDistance);

	//绘制检测到的角点
	int r = 4;
	RNG g_rng(12345);//随机器
	for (int i = 0; i < corners.size(); i++)
	{
		//绘制角点
		circle(copy, corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255),g_rng.uniform(0, 255)), -1, 8, 0);
	}
	//输出角点信息
	//for (int i = 1; i < corners.size(); i++)
	//{
	//	cout << " \t>>精确角点坐标[" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
	//}
	//显示窗口
	imshow("Shi-Tomasi角点检测", copy);
}
int main()
{
	printf("\n\n\t\t\t	 此为实验示例程序\n");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n\t\t\t   当前实验为：Harris角点检测");
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//载入源图像并将其转换为灰度图
	g_srcImage = imread("1.jpg", 1);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

	namedWindow("Shi-Tomasi角点检测", 1);
	createTrackbar("最大角点数", "Shi-Tomasi角点检测", &thresh, 500, Shi_Tomasi);

	imshow("原始图像", g_srcImage);
	Shi_Tomasi(0, 0);

	waitKey(0);
	return 0;
}