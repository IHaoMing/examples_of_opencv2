// pyrUp_and_pyrDown.cpp : 定义控制台应用程序的入口点。
// use the pyrUp and pyrDown function
// date: 2018/04/03
// author: ihaoming

//included files
#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

//namespace 
using namespace std;
using namespace cv;


int _tmain(int argc, _TCHAR* argv[])
{
	//step1: read the source image
	Mat src_image = imread("./lena.jpg");

	if (src_image.empty())
	{
		cout << "failed to load image!" << endl;
		getchar();
		return -1;
	}
	//step2: show the source image
	imshow("src_image", src_image);

	Mat pyr_up_image, pyr_down_image;

	//step3: use the pyrUp and pyrDown function
	pyrUp(src_image, pyr_up_image, Size(src_image.cols * 2, src_image.rows * 2));
	pyrDown(src_image, pyr_down_image, Size(src_image.cols / 2, src_image.rows / 2));

	//step4: imshow the destination images
	imshow("pyr_up_image", pyr_up_image);
	imshow("pyr_down_image", pyr_down_image);

	waitKey(0);
	return 0;
}

