// HW4_level1: »ÉªOÀH¾÷±¼¸¨
// Auther: M11125016 ¿½±j

#include "opencv2/opencv.hpp" // load opencv library
#include <iostream> // load C++ library

using namespace cv;
using namespace std;

// to make the image to binary
// the reason to use void is there isn't a return value
void cvt2Bin(const cv::Mat& inputimage, cv::Mat& outputimage) {
	cvtColor(inputimage, outputimage, COLOR_BGR2GRAY);  // covert color to gray
	threshold(outputimage, outputimage, 10, 255, THRESH_BINARY);  // threshold the image
}

// Define a marco of coins
#define COINS 20  // total 20 coins
cv::RNG rng(clock());

int main(void) {
	// void the container of raw image
	cv::Mat imC1, imC5, imC10, imC50;
	// read image
	imC1 = imread("data/c01.png");
	imC5 = imread("data/c05.png");
	imC10 = imread("data/c10.png");
	imC50 = imread("data/c50.png");

	// void the container of binary image
	cv::Mat imC1Bin, imC5Bin, imC10Bin, imC50Bin;
	// covert image to binary
	cvt2Bin(imC1, imC1Bin);
	cvt2Bin(imC5, imC5Bin);
	cvt2Bin(imC10, imC10Bin);
	cvt2Bin(imC50, imC50Bin);

	// load the image
	cv::VideoCapture cap("data/moving.mp4");
	if (!cap.isOpened()) {
		cout << "Can't catch the video!" << endl;
		return -1;
	}
	
	// Create a container for video size
	cv::Size vidSize(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));
	// Create a container for video frame count
	int frameCount = cap.get(CAP_PROP_FRAME_COUNT);

	// Creat a video writer to save video
	cv::VideoWriter writer("data/drop.mp4", cv::VideoWriter::fourcc('x', '2', '6', '4'), 60, vidSize);
	if (!writer.isOpened()) {
		cout << "File could not be created for writing." << endl;
		return -1;
	}


	namedWindow("video");

	// Void container for random coin
	int start[COINS][3];  // 2 dimesion, [coint count], [rondom properties]
	for (int i = 0; i < COINS; i++) {
		start[i][0] = rng.uniform(0, frameCount - 100);  // random the coin in the video frame
		start[i][1] = rng.uniform(1, 5);  // random coin type
		start[i][2] = rng.uniform(0, vidSize.width - 150);  // random horizontal position, 150 is the maximan width for the coin
	}

	// Run the video with the coin
	for (int f = 0; f < frameCount; f++) {
		cv::Mat img_bg;
		cap >> img_bg;
		if (img_bg.empty()) {
			cout << " -- No captured image for the video! --" << endl;
			break;
		}

		for (int j = 0; j < COINS; j++) {
			int y = 5 * (f - start[j][0]);
			if (y > 0 && y < vidSize.height - 150) {
				// Swith coin type
				switch (start[j][1]) {
					case 1: {
						cv::Rect roi1(start[j][2], y, imC1.cols, imC1.rows);
						imC1.copyTo(img_bg(roi1), imC1Bin);
						break;
						}
					case 2: {
						cv::Rect roi2(start[j][2], y, imC5.cols, imC5.rows);
						imC5.copyTo(img_bg(roi2), imC5Bin);
						break;
					}
					case 3: {
						cv::Rect roi3(start[j][2], y, imC10.cols, imC10.rows);
						imC10.copyTo(img_bg(roi3), imC10Bin);
						break;
					}
					case 4: {
						cv::Rect roi4(start[j][2], y, imC50.cols, imC50.rows);
						imC50.copyTo(img_bg(roi4), imC50Bin);
						break;
					}
				}
			}
		}
		imshow("video", img_bg);
		waitKey(10);
		writer << img_bg;
	}

	cout << "Video has been saved as drop.mp4" << endl;
		
	return 0;
}