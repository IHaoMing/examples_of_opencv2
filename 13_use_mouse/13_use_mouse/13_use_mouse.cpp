// 13_use_mouse.cpp: 定义控制台应用程序的入口点。
// date: 2018/03/30
// author: ihaoming

//include file
#include "stdafx.h"
#include<iostream>
#include<opencv2/opencv.hpp>

//namespace
using namespace std;
using namespace cv;

//declare function
static void draw_rectangle(cv::Mat& image, cv::Rect box);
void on_mouse_handle(int event, int x, int y, int flag, void* prama);


//delcare global variable
const string window_name = "use mouse";
RNG g_rng(12345);
bool g_drawing_box = false;
Rect g_rectangle;

int main()
{

	g_rectangle = Rect(-1, -1, 0, 0);
	Mat src_image(600, 800, CV_8UC3);
	Mat temp_image;
	src_image.copyTo(temp_image);
	src_image = Scalar::all(0);

	//set the mouse call back function
	namedWindow(window_name);
	setMouseCallback(window_name, on_mouse_handle, (void*)&src_image);

	while (true)
	{
		src_image.copyTo(temp_image);
		if (g_drawing_box)
		{
			draw_rectangle(temp_image, g_rectangle);
		}
		imshow(window_name, temp_image);
		//press the 'esc' to quit
		if (waitKey(10) == 27)
		{
			break;
		}
	}
	return 0;
}


//draw rectangle
static void draw_rectangle(cv::Mat& image, cv::Rect box)
{
	cv::rectangle(image, box, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}

//mouse callback function
void on_mouse_handle(int event, int x, int y, int flag, void* prama)
{
	Mat image = *(Mat*)prama;

	switch (event)
	{
		// the mouse move message
	case EVENT_MOUSEMOVE:
		if (g_drawing_box)
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
		break;

		//the left button down message
	case EVENT_LBUTTONDOWN:
		//while the left button down, drawing box can be true
		g_drawing_box = true;
		//and record the coordinate
		g_rectangle = Rect(x, y, 0, 0);

		break;
		//the left button up message
	case EVENT_LBUTTONUP:
		//while left button up ,drawing box should be false
		g_drawing_box = false;

		//while the width or height less than 0
		if (g_rectangle.width < 0)
		{
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}
		if (g_rectangle.height < 0)
		{
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}

		//call the function to draw
		draw_rectangle(image, g_rectangle);
		break;
	default:
		break;
	}

}