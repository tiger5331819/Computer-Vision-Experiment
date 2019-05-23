#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat srcImage, dstImage;//原始图和效果图
int StructElementSize = 3; //结构元素(内核矩阵)的尺寸

void erode(int, void*)
{
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * StructElementSize + 1, 2 * StructElementSize + 1), Point(StructElementSize, StructElementSize));

	//进行腐蚀操作
	erode(srcImage, dstImage, element);
	//显示效果图
	imshow("腐蚀", dstImage);
}

int main()
{
	printf("\n\n\t\t\t	 此为实验示例程序\n");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n\t\t\t   当前实验为：形态学滤波：腐蚀");
	printf("\n\n  ----------------------------------------------------------------------------\n");

	srcImage = imread("1.jpg");
	if (!srcImage.data) { cout << "读取错误！无法读取到图像！" << endl; return false; }

	//显示原图
	imshow("原图", srcImage);

	//创建窗口
	namedWindow("腐蚀");
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * StructElementSize + 1, 2 * StructElementSize + 1), Point(StructElementSize, StructElementSize));
	erode(srcImage, dstImage, element);
	imshow("腐蚀", dstImage);

	//创建轨迹条
	createTrackbar("内核尺寸", "腐蚀", &StructElementSize, 21, erode);

	waitKey(0);
	return 0;
}