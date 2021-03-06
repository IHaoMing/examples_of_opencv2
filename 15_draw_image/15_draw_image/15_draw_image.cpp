// 15_draw_image.cpp: 定义控制台应用程序的入口点。
// date: 2018/04/01
// author: ihaoming

//included files
#include "stdafx.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
//#include<opencv2/imgproc/imgproc.hpp>		//opencv3 shuld include this file

//namespace 
using namespace cv;
using namespace std;

//string constans
const string WINDOW_NAME1 = "draw_image1";
const string WINDOW_NAME2 = "draw_image2";
const int WINDOW_WIDTH = 600;

//declare fucntion
static void draw_ellipse(Mat image, double angle);		//draw the ellipse
static void draw_filled_circle(Mat image, Point center);	//	draw the filled circle
static void draw_polygon(Mat image);		//draw the polygon
static void draw_line(Mat image, Point start, Point end);	//draw the line


int main()
{
	//create blank Mat images
	Mat atom_image = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat rook_image = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	//-----------draw the atom image--------------------------------
	//draw ellipse
	draw_ellipse(atom_image, 90);
	draw_ellipse(atom_image, 0);
	draw_ellipse(atom_image, 45);
	draw_ellipse(atom_image, -45);

	//draw filled circle
	draw_filled_circle(atom_image, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

	//------------draw the rook image-------------------------------
	draw_polygon(rook_image);

	rectangle(
		rook_image,
		Point(0, 7 * WINDOW_WIDTH / 8),
		Point(WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar(0, 255, 255),
		-1,
		8
	);

	draw_line(rook_image, Point(0, 15 * WINDOW_WIDTH / 16), Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
	draw_line(rook_image, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
	draw_line(rook_image, Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 2, WINDOW_WIDTH));
	draw_line(rook_image, Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH));

	//show images
	imshow(WINDOW_NAME1, atom_image);
	moveWindow(WINDOW_NAME1, 0, 200);

	imshow(WINDOW_NAME2, rook_image);
	moveWindow(WINDOW_NAME2, WINDOW_WIDTH, 200);

	waitKey(0);
	return 0;
}

static void draw_filled_circle(Mat image, Point center)	//	draw the filled circle
{
	//the line's thickness and type
	int thickness = 2;
	int line_type = 8;

	circle(
		image,
		center,
		WINDOW_WIDTH / 32,
		Scalar(0, 0, 255),
		thickness,
		line_type
	);
}
static void draw_ellipse(Mat image, double angle)		//draw the ellipse
{

	//the line's thickness and type
	int thickness = 2;
	int line_type = 8;

	ellipse(image,
		Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
		Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
		angle,
		0,
		360,
		Scalar(255, 129, 0),
		thickness,
		line_type
	);
}
static void draw_line(Mat image, Point start, Point end)
{
	//the line's thickness and type
	int thickness = 2;
	int line_type = 8;

	line(image, start, end, Scalar(0, 0, 0), thickness, line_type);
}


static void draw_polygon(Mat image)		//draw the polygon
{
	int line_type = 8;

	//create some points
	Point rookPoints[1][20];
	rookPoints[0][0] = Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][1] = Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][2] = Point(3 * WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][3] = Point(11 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][4] = Point(19 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][5] = Point(3 * WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][6] = Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rookPoints[0][7] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][8] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][9] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][10] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][11] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][12] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][13] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][14] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][15] = Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rookPoints[0][16] = Point(WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][17] = Point(13 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][18] = Point(5 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][19] = Point(WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);

	const Point* ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };

	fillPoly(image,
		ppt,
		npt,
		1,
		Scalar(255, 255, 255),
		line_type
	);
}