// 16_use_pointer_access_pixel.cpp: 定义控制台应用程序的入口点。
// description: use the pointer to access pixels
// author: ihaoming
// date: 2018/04/03

//included files
#include "stdafx.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

//namespace 
using namespace std;
using namespace cv;

//declare function
static void color_reduce(Mat& input_image, Mat& output_image, int div);

int main()
{
	//step1: read and show the source image
	Mat src_image = imread("./clock.jpg");
	if (src_image.empty())
	{
		cout << "failed to load the image!" << endl;
		getchar();
		return -1;
	}
	namedWindow("src_image", WINDOW_AUTOSIZE);
	imshow("src_image", src_image);

	//step2: create the destination image
	Mat dst_image(src_image.size(), src_image.type());

	//step3: record start time
	double time0 = static_cast<double>(getTickCount());

	//step4: call the color reduce funtion
	color_reduce(src_image, dst_image, 32);

	//step5: record finish time
	time0 = ((double)getTickCount() - time0) / getTickFrequency();

	//step6: print the time
	cout << "Time-consuming:" << time0 << " ms" << endl;

	//step7: show the destination image
	imshow("dst_image", dst_image);
	waitKey(0);

	return 0;
}


static void color_reduce(Mat& input_image, Mat& output_image, int div)
{
	//step1: copy the input image to output image
	output_image = input_image.clone();

	//step2: calculate the row and col numbers
	int row_num = input_image.rows;
	int col_num = input_image.cols * input_image.channels();	//total cols 

																//step3: traverse all pixel values
	for (size_t i = 0; i < row_num; i++)
	{
		//get the first address of line i
		uchar* data = output_image.ptr<uchar>(i);

		for (size_t j = 0; j < col_num; j++)
		{
			//improcess every pixel
			data[j] = data[j] / div * div + div / 2;
		}
	}

}
