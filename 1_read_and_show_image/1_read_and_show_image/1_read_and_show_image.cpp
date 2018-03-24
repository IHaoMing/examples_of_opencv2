// 1_read_and_show_image.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main()
{
	//read the image
	Mat image = imread("./clock.jpg");

	if (image.data != NULL)
	{
		//show the image
		imshow("clock", image);
		waitKey(0);
	}
	else
	{
		cout << "can't openc the file!" << endl;
		getchar();
	}
	return 0;
}

