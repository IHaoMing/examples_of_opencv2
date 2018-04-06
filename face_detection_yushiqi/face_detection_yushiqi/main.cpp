// description: use the ShiqiYu's libfacedetection to test the facedetection
// author: ihaoming
// date: 2018/04/06

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "facedetect-dll.h"

#pragma comment(lib,"libfacedetect.lib")
//#pragma comment(lib,"libfacedetect-x64.lib")

//define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000
using namespace cv;
static void get_fps(Mat& frame, double t);
static void color2gray(Mat camer_frame, Mat& gray);

int main(int argc, char* argv[])
{

	VideoCapture capture;
	capture.open(0);
	Mat image;

	while (true)
	{
		//step1: open the video
		//---------------------------------------------------------------------------
		if (capture.isOpened())
		{
			capture >> image;

			if (image.empty())
			{
				fprintf(stderr, "Can not load the image file %s.\n", argv[1]);
				return -1;
			}

			//step2: get the gray image
			//--------------------------------------------------------------------------
			Mat gray;
			//cvtColor(image, gray, CV_BGR2GRAY);
			color2gray(image, gray);

			double t = (double)cv::getTickCount();

			//step3: start detection
			//----------------------------------------------------------------------------------------
			int * pResults = NULL;
			//pBuffer is used in the detection functions.
			//If you call functions in multiple threads, please create one buffer for each thread!
			unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
			if (!pBuffer)
			{
				fprintf(stderr, "Can not alloc buffer.\n");
				return -1;
			}

			int doLandmark = 1;

			///////////////////////////////////////////
			// frontal face detection / 68 landmark detection
			// it's fast, but cannot detect side view faces
			//////////////////////////////////////////
			//!!! The input image must be a gray one (single-channel)
			//!!! DO NOT RELEASE pResults !!!
			pResults = facedetect_frontal(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
				1.2f, 2, 48, 0, doLandmark);

			printf("%d faces detected.\n", (pResults ? *pResults : 0));
			Mat result_frontal = image.clone();

			//step4: print the detection results
			for (int i = 0; i < (pResults ? *pResults : 0); i++)
			{
				short * p = ((short*)(pResults + 1)) + 142 * i;
				int x = p[0];
				int y = p[1];
				int w = p[2];
				int h = p[3];
				int neighbors = p[4];
				int angle = p[5];

				printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x, y, w, h, neighbors, angle);
				rectangle(result_frontal, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
				if (doLandmark)
				{
					//step5: draw the dection mark
					//------------------------------------------------------------------------------------------------
					for (int j = 0; j < 68; j++)
						circle(result_frontal, Point((int)p[6 + 2 * j], (int)p[6 + 2 * j + 1]), 1, Scalar(0, 255, 0));
				}
			}

			t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();	// t(ms)
			get_fps(result_frontal, t / 10);

			//step6: show the result
			//------------------------------------------------------------------------------------------------------
			imshow("Results_frontal", result_frontal);

			int k = waitKey(10);
			if (k == 27) //press 'esc' to quit
			{
				break;
			}
		}
	}

	return 0;
}

static void get_fps(Mat& frame, double t)
{
	double fps = 1.0 / t;
	char s[10];
	sprintf_s(s, "%.2f", fps);		//opencv3 use the sprintf will error
	std::string fps_string("FPS:");
	fps_string += s;

	cv::putText(
		frame,
		fps_string,
		cv::Point(5, 20),
		cv::FONT_HERSHEY_SIMPLEX,
		0.5,
		cv::Scalar(0, 0, 255)
	);
}

static void color2gray(Mat camer_frame, Mat& gray)
{
	//image from pc has 3 channels(BGR) the mobile device has 4 channels(BGRA)
	if (camer_frame.channels() == 3)
	{
		cvtColor(camer_frame, gray, CV_BGR2GRAY);
	}
	else if (camer_frame.channels() == 4)
	{
		cvtColor(camer_frame, gray, CV_BGRA2GRAY);
	}
	else
	{
		gray = camer_frame;
	}
}