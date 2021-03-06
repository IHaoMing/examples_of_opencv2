// 7_trackbar.cpp: 定义控制台应用程序的入口点。
// learn the trackbar
// date: 2018/03/24
// author: ihaoming

#include "stdafx.h"
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<assert.h>

//namespace 
using namespace cv;
using namespace std;

const string window_name = "example of trackbar";	//define the window name
void on_change_trackbar(int, void*);				//call back function

int main()
{
	Mat src_image = imread("./clock.jpg");
	if (src_image.data == NULL)
	{
		cout << "can't open the file!" << endl;
		getchar();
		return -1;
	}
	namedWindow(window_name);
	imshow(window_name, src_image);

	int pos_max_value = 30;
	int pos = 3;
	const string trackbar_name = "blur_size";


	createTrackbar(trackbar_name, window_name, &pos, pos_max_value, on_change_trackbar, &src_image);

	waitKey(0);
	return 0;
}

void on_change_trackbar(int pos, void* userdata)
{
	assert(userdata);
	Mat img = *(Mat*)userdata;					//type conversion
	Mat dst_image;

	if (pos % 2 == 0)
	{
		//the pos should be odd number
		pos -= 1;
	}
	if (pos > 0)
	{
		Size blur_size(pos, pos);
		blur(img, dst_image, blur_size);
		imshow(window_name, dst_image);
	}
}

