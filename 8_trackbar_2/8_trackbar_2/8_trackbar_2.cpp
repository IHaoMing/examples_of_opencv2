// 8_trackbar_2.cpp: 定义控制台应用程序的入口点。
// example or trackbar: the picture linear mixing
// date: 2018/03/28
// author: ihaoming

//include file
#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

//namespace
using namespace cv;
using namespace std;

//global value
Mat g_src_image1;
Mat g_src_image2;
Mat g_dst_image;

const string window_name = "create_trackbar_and_picture_linear_mixing";
const string trackbar_name = "alphe";

const int g_max_alpha_value = 100;
int g_alpha_value_slider = 0;
double g_a_alpha_value = 0.0;
double g_b_alpha_value = 0.0;

//declare function
void on_change_alpha(int, void*);

int main()
{
	g_src_image1 = imread("./clock.jpg");
	g_src_image2 = imread("./gun.jpg");

	if (g_src_image1.data == NULL)
	{
		cout << "can't open the file!" << endl;
		return -1;
	}
	if (g_src_image2.data == NULL)
	{
		cout << "can't open the file!" << endl;
		return -1;
	}
	if (g_src_image1.size() != g_src_image2.size())
	{
		cout << "images not equal!" << endl;
		return -1;
	}

	g_alpha_value_slider = 70;

	//create the window
	namedWindow(window_name, 1);

	//create trackbar
	createTrackbar(trackbar_name, window_name, &g_alpha_value_slider, g_max_alpha_value, on_change_alpha);

	on_change_alpha(g_alpha_value_slider, 0);

	waitKey(0);


	return 0;
}


void on_change_alpha(int, void*)
{
	//calculate the g_a_alpha_value
	g_a_alpha_value = (double)g_alpha_value_slider / g_max_alpha_value;
	//g_b_alpha_value
	g_b_alpha_value = 1.0 - g_a_alpha_value;
	addWeighted(g_src_image1, g_a_alpha_value, g_src_image2, g_b_alpha_value, 0.0, g_dst_image);
	//show dst_image
	imshow(window_name, g_dst_image);
}

