// 5_video_capture.cpp: 定义控制台应用程序的入口点。
// use the vedio capture
// date: 2018/03/24
// author: ihaoming

#include "stdafx.h"
#include<iostream>
#include<opencv2/opencv.hpp>

//namespace
using namespace std;
using namespace cv;


int main()
{
	//open the video
	VideoCapture capture("./test_video.avi");
	if (capture.isOpened())
	{
		for (; ;)
		{
			Mat frame;
			//capture >> frame;
			if (capture.read(frame) == true)
			{
				imshow("test_video", frame);
				waitKey(30);	//delay 30ms
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		cout << "can't open the video!" << endl;
		getchar();
		return -1;
	}
	return 0;
}

