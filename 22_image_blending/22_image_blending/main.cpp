// description£ºbasic image blending
// author: ihaoming
// date: 2018/04/06

//included files
#include<opencv2/core/core.hpp>
#include<highgui/highgui.hpp>
#include<iostream>

//namesapce 
using namespace std;
using namespace cv;

//declare functions
static void linear_blend();
static void roi_blend();
static void roi_addimage();

int main(int, char**)
{
	//linear_blend();
	roi_blend();
	//roi_addimage();

	waitKey(0);
	return 0;
}

static void linear_blend()
{
	//step1: read tow source images
	Mat src_image1 = imread("./clock.jpg");
	Mat src_image2 = imread("./gun.jpg");
	Mat dst_image;

	if(src_image1.empty() || src_image2.empty())
	{
		cout<<"failed to load the images!"<<endl;
		getchar();
		return;
	}
	//step2: get the alpha and beta
	double alpha = 0.5;
	double beta = 1 - alpha;
	//step3: call the addWeighted function to blend
	addWeighted(src_image1, alpha, src_image2, beta, 0.0, dst_image);

	//step4: display the dst_image
	imshow("dst_image", dst_image);



}

static void roi_addimage()
{
	//step1: read the big and small images;
	Mat big_image = imread("./clock.jpg");
	Mat small_image =  imread("./boy.jpg");

	if(big_image.empty() || small_image.empty())
	{
		cout<<"failed to load the images!"<<endl;
		getchar();
		return;
	}
	//step2: set the roi of the big image
	Mat roi = big_image(Rect(300, 200, small_image.cols, small_image.rows));
	//step3: load mask image

	Mat mask = imread("./boy.jpg",IMREAD_GRAYSCALE ); //must be gray image
	//step4: copy the  mask to roi
	small_image.copyTo(roi, mask);

	//step5: display result
	namedWindow("roi_addimage");
	imshow("roi_addimage", big_image);
}

static void roi_blend()
{
	//step1: read the big and small images;
	Mat big_image = imread("./clock.jpg");
	Mat small_image =  imread("./boy.jpg");

	if(big_image.empty() || small_image.empty())
	{
		cout<<"failed to load the images!"<<endl;
		getchar();
		return;
	}
	//step2: set the roi of the big image
	Mat roi = big_image(Rect(300, 200, small_image.cols, small_image.rows));

	//step3: roi linear blending
	addWeighted(roi, 0.5, small_image, 0.5, 0.0, roi);
	
	//step4: dispaly the result
	imshow("roi linear blend", big_image);
}