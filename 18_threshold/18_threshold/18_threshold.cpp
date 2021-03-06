// threshold.cpp : 定义控制台应用程序的入口点。
// description: use the threshold function
// author: ihaoming
// date: 2018/04/03

//#included files
#include "stdafx.h"
#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

//namespace
using namespace std;
using namespace cv;

const string WINDOW_NAME = "threshold";
const string TYPE_TRACKBAR_NAME = "method type";
const string THESHOLD_TRACKBAR_NAME = "threshold";

//global variables
int g_threshold_value = 128;			//the default threshold value
int g_method_type = 1;				    //the default method type
Mat g_gray_image;

//declare functions 
void on_threshold(int, void* src_image);
int _tmain(int argc, _TCHAR* argv[])
{
	//step1: read a source image
	Mat src_image = imread("./lena.jpg");
	if (src_image.empty())
	{
		cout << "failed to load the image!" << endl;
		getchar();
		return -1;
	}

	//step2: color conversion
	cvtColor(src_image, g_gray_image, CV_RGB2GRAY);

	//step3: create the window
	namedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE);

	//step4: create the trackbar
	createTrackbar(TYPE_TRACKBAR_NAME, WINDOW_NAME, &g_threshold_value, 255, on_threshold);

	createTrackbar(THESHOLD_TRACKBAR_NAME, WINDOW_NAME, &g_method_type, 4, on_threshold);

	//step5: on_threshold
	on_threshold(0, 0);

	waitKey(0);

	return 0;
}

void on_threshold(int, void* src_image)
{
	//step1: declare the destination Mat
	Mat dst_image;

	//step2: use the threshold function
	threshold(g_gray_image, dst_image, g_threshold_value, 255, g_method_type);

	//step3: show the result
	imshow(WINDOW_NAME, dst_image);
}