// 9_blur.cpp: 定义控制台应用程序的入口点。
// use the box filter 
// date: 2018/03/29
// author: ihaoming

#include "stdafx.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>


using namespace std;
using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat src_image = imread("./lena.jpg");
	if (src_image.data == NULL)
	{
		cout << "can't open the file!" << endl;
		getchar();
		return -1;
	}

	imshow("original image", src_image);

	Mat dst_image;

	blur(src_image, dst_image, Size(7, 7));

	imshow("out image", dst_image);

	waitKey(0);

	return 0;
}


