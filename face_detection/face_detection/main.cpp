// description: opencv official example face detection
// author: ihaoming
// date: 2018/04/06

//included files
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<stdio.h>

//namespace 
using namespace std;
using namespace cv;

//the face and eye cascade name
const string face_cascade_name = "haarcascade_frontalface_alt.xml";
const string eye_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
const string window_name = "face-detection";

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

RNG rng(12345);

static void detect_and_display(Mat& frame);
static void color2gray(Mat camer_frame, Mat& gray);
static void get_fps(Mat& frame, double t);


int main(int, char**)
{
	VideoCapture capture;
	Mat frame;

	//step1: load the cascades
	if (!face_cascade.load(face_cascade_name))
	{
		cout << "failed to load the cascade!" << endl;
		getchar();
		return -1;
	}
	if (!eyes_cascade.load(eye_cascade_name))
	{
		cout << "failed to load the cascade!" << endl;
		getchar();
		return -1;
	}

	//step2: open the video
	capture.open(0);

	while (true)
	{

		//if (cv::waitKey(50) == 30) { break; }
		if (capture.isOpened())
		{
			capture >> frame;

			if (frame.empty())
			{
				cout << "No captured!" << endl;
				break;
			}
			else
			{
				double t = (double)cv::getTickCount();
				detect_and_display(frame);
				t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();	// t(ms)
				get_fps(frame, t / 10);

			}

			// display the result
			imshow(window_name, frame);

			int c = waitKey(10);
			if (c == 27)//prees 'esc' to quit
			{
				break;
			}
		}

	}

	return 0;
}

static void detect_and_display(Mat& frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;

	//step1: change the color frameto gray
	color2gray(frame, frame_gray);

	//step2: histogram equalization
	equalizeHist(frame_gray, frame_gray);

	//step3: face detction
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	//step4: eye detection
	for (size_t i = 0; i < faces.size(); i++)
	{
		//draw the rectangle
		cv::rectangle(frame, faces[i], Scalar(255, 0, 255), 2, 8, 0);

		//get the face roi
		Mat face_roi = frame_gray(faces[i]);
		std::vector<Rect> eyes;

		//detect the eyes in the face roi
		eyes_cascade.detectMultiScale(face_roi, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			//draw cicles
			Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
			int raduis = cvRound((eyes[j].width + eyes[j].height) * 0.25);
			circle(frame, eye_center, raduis, Scalar(255, 0, 0), 3, 8, 0);
		}
	}
}

static void color2gray(Mat camer_frame, Mat& gray)
{
	//image from pc has 3 channels(BGR£©£¬ the mobile device has 4 channels(BGRA)
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