#include <opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>


using namespace cv;
using namespace std;

static Mat GrayScaling(Mat image);
static Mat ConvertBinary(Mat image_gray);

int main(int argc, char* argv[])
{
	Mat image;
	Mat image_gray;
	Mat image_binary;
	image = imread("shape.jpg", IMREAD_COLOR);
	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", image);

	GrayScaling(image);
	ConvertBinary(image_gray);


	//find contour

	waitKey(0);

	return 0;

}

static Mat GrayScaling(Mat image) {

	Mat image_gray;

	/// Copy image
	image.copyTo(image_gray);

	int y = image.rows;
	int x = image.cols;

	/// Convert to gray
	float fGray = 0.0f;
	float chBlue, chGreen, chRed;


	for (int j = 0; j < y; j++) {

		for (int i = 0; i < x; i++) {

			//GrayScale using Luna Component

			chBlue = (float)(image.at<Vec3b>(j, i)[0]);
			chGreen = (float)(image.at<Vec3b>(j, i)[1]);
			chRed = (float)(image.at<Vec3b>(j, i)[2]);

			fGray = 0.2126f * chRed + 0.7152f * chGreen + 0.0722f * chBlue;

			if (fGray < 0.0) fGray = 0.0f;
			if (fGray > 255.0) fGray = 255.0f;

			image_gray.at<Vec3b>(j, i)[0] = (int)fGray;
			image_gray.at<Vec3b>(j, i)[1] = (int)fGray;
			image_gray.at<Vec3b>(j, i)[2] = (int)fGray;

		}

	}

	namedWindow("Image Grayed", WINDOW_AUTOSIZE);
	imshow("Image Grayed", image_gray);

	return image_gray;

}


static Mat ConvertBinary(Mat image_gray) {

	Mat image_binary;

	/// Copy image
	image_binary.copyTo(image_gray);

	int y = image_gray.rows;
	int x = image_gray.cols;
	int thresh = 128;

	for (int i = 0; i < image_gray.rows; i++) {
		for (int j = 0; j < image_gray.cols; j++) {
			if (image_gray.at<uchar>(i, j) < thresh)
				image_binary.at<uchar>(i, j) = 0;
			else
				image_binary.at<uchar>(i, j) = 255;

		}
	}

	return image_binary;

}



