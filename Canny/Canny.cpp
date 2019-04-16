#include<iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat srcImage, final,image2;//存储图片的Mat类型
int MeanBlurValue = 1;  //均值滤波参数值
int CannyValue = 3;		//Canny低阈值

static void Cannyfunc(int, void*)
{
	//使用均值滤波来降噪
	blur(srcImage, image2, Size(MeanBlurValue + 1, MeanBlurValue + 1));

	//运行Canny算子
	Canny(image2, final, (double)CannyValue, (double)CannyValue*2);

	//使用Canny算子输出的边缘图final作为掩码，来将原图srcImage拷到目标图image中
	Mat image;
	srcImage.copyTo(image, final);

	//显示窗口
	imshow("Canny边缘检测", image);
}

int main()
{
	printf("\n\n\t\t\t	 此为实验示例程序\n");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n\t\t\t   当前实验为：Canny边缘检测");
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//载入原始图  
	srcImage = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图
	if (!srcImage.data) { cout << "读取错误！无法读取到图像！" << endl; return false; }

	//显示原始图 
	imshow("原始图", srcImage);

	namedWindow("Canny边缘检测", 1);

	// 将原图像转换为灰度图像
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);

	//创建轨迹条
	createTrackbar("中值参数：", "Canny边缘检测", &MeanBlurValue, 40, Cannyfunc);
	createTrackbar("Canny：", "Canny边缘检测", &CannyValue, 10, Cannyfunc);
	Cannyfunc(0, 0);
	waitKey(0);

	return 0;
}