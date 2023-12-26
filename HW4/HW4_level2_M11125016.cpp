// HW4_Level2: 偵測 drop.mp4 視訊中，掉落的銅板，並計算其總金額。(註：沒偵測到眼睛時不算)
// 1.設定參數
// 2.偵測視訊中的人臉與人眼
// 3.有偵測到人眼時，對掉落的銅板做 HoughCircles 偵測
// 4.繪製人臉/人眼框
// 5.繪製銅板圓形框，以及人眼到圓心的雷射光
// 6.用直方圖統計每個水平區間，曾經偵測到圓心的最高金額(根據其半徑)
// 7.輸出含有偵測框﹑雷射光、偵測金額的視訊
// 8.根據直方圖，統計銅板的總金額

#include "opencv2/opencv.hpp"  // load opencv library
#include <iostream>  // load standarf library

using namespace cv;  // constant namespace of opencv
using namespace std;  // constant namespace of standard

// GLOBAL VARIABLE
cv::Mat frame;  // container of video frame
int show_rect = 1;  // shows the face/ eyes parameter
int frame_count = 0;  // frame count for video

bool showDraw = true, showHis = true;

cv::VideoCapture cap("data/drop.mp4");  // // Coins randomly drop object as cap
cv::Size vidSize(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));  //  video size
cv::VideoWriter writer("data/output.mp4", cv::VideoWriter::fourcc('x', '2', '6', '4'), 60, vidSize); // write video
cv::CascadeClassifier face_cascade;  // detect face object
cv::CascadeClassifier eyes_cascade;  // detect eyes object

vector<Rect> faces;  // vector object of face rectangle
vector<Rect> eyes;  // vector object of eyes rectangle
vector<Vec3f> circles;  // vector object of coins circle
float binW = 10;  // length of each horizontal mapping of the histogram corespoding to the width of the image (pixel)

/* 子程式原型宣告 */
vector<Rect> detectFace(Mat); //人臉偵測
vector<Rect> detectEye(Mat);  //人眼偵測
vector<Vec3f> detectCircle(Mat); //銅板圓形偵測
Mat boxFace(Mat, vector<Rect>); //人臉框繪製
Mat drawCircle(Mat, vector<Vec3f>); //銅板圓框繪製
Mat drawEye(Mat, Rect, vector<Rect>); //人眼框繪製

int main(int, char** argv) {
	cout << "--Instruction--" << endl;
	cout << "esc for leaving" << endl;
	cout << "h for closing the histogram, retype can open" << endl;
	cout << "r for closing the box for detecting, retype can open" << endl;

	//! [load the cascades]
	if (!face_cascade.load("data/haarcascade_frontalface_alt.xml")) {
		cout << "--(!)Error loading face cascade" << endl;
		return -1;
	}
	if (!eyes_cascade.load("data/haarcascade_eye_tree_eyeglasses.xml")) {
		cout << "--(!)Error laoding eyes cascade" << endl;
		return -1;
	}
	if (!writer.isOpened()) {
		cout << "--(!)Can't write the frame" << endl;
		return -1;
	}
	//! [load the cascades]

	//! [hist_amout_init]
	// Conastan a matrix call object as 0 value with [1, visdeo width]
	cv::Mat hist = cv::Mat::zeros(1, cvRound(vidSize.width / binW), CV_32FC1);
	//! [hist_amout_init]


	namedWindow("Video");  // named a windows as Video
	namedWindow("Histogram");  // named a windows as Histogram

	// Read the video stream
	while (cap.isOpened()) {
		cap.read(frame);
		if (frame.empty()) {
			cout << "The frame can't open" << endl;
			break;
		}

		//! [Detect the face]
		// output rectangle if detected the face
		faces = detectFace(frame);
		// start if there is faces
		if (!faces.empty()) {
			// start if the parameter of face/eyes isn't 0
			if (show_rect) {
				// if there's faces show the box
				if (showDraw) { 
					boxFace(frame, faces);
				}
				// Creat a roi for the face area
				cv::Mat faceRoi = frame(faces[0]);
				eyes = detectEye(faceRoi);
				if (showDraw) {
					drawEye(frame, faces[0], eyes);
				}
			}
		}
		//! [Detect the face]
		
		//! [Detect Circle]
		if (!eyes.empty() && !(frame_count % 5)) {
			circles = detectCircle(frame);
			if (circles.size() > 0) {
				drawCircle(frame, circles);
				//! [save_amount_in_hist]
				for (size_t i = 0; i < circles.size(); i++) {
					int cir_x = circles[i][0];  // x of num i circle center
					int cir_y = circles[i][1];  // y of num i circle center
					int cir_r = circles[i][2];  // radius of num i circle
					// Create a container to store the position
					cv::Point eyes_cor(eyes[0].x + eyes[0].width / 2, eyes[0].y + eyes[0].height / 2);
					cv::line(frame, eyes_cor, cv::Point(cir_x, cir_y), cv::Scalar(0, 0, 255), 1, LINE_AA);
					// distinguish the coin amount by using radius of circle
					int coinAmount;
					if (cir_r <= 47) {
						coinAmount = 1;
					}
					else if (cir_r > 47 && cir_r <= 60) {
						coinAmount = 5;
					}
					else if (cir_r > 60 && cir_r <= 67) {
						coinAmount = 10;
					}
					else {
						coinAmount = 50;
					}
					// text the coin amount if the coin is detected
					cv::putText(frame,
						"+" + std::to_string(coinAmount),
						Point(cvRound(cir_x) - cir_r, cvRound(cir_y) - cir_r - 10),
						FONT_HERSHEY_SIMPLEX,
						1,
						cv::Scalar(255, 255, 0),
						3);

					// Find the index first. If there isn't any input in the index.
					// That means the current amount in that index is 0.
					int idx = cvRound(cir_x / binW);
					if (idx >= 0 && idx < hist.cols) {
						int currentMaxAmount = hist.at<float>(0, idx);
						int newMaxAmount = MAX(currentMaxAmount, coinAmount);
						hist.at<float>(idx) = newMaxAmount;
					}
				}
				//! [save_amount_in_hist]
			}
		}
		//! [Detect Circle]

		// text the string in the right botton corner
		cv::putText(frame,
			"Total Amount:",
			Point(vidSize.width - 175, vidSize.height - 50),
			FONT_HERSHEY_COMPLEX,
			0.7,
			cv::Scalar(100, 155, 155),
			2);
		// text the total amount from sumrize the histogram matix in the right botton corner
		cv::putText(frame,
			to_string(int(sum(hist).val[0])),
			Point(vidSize.width - 175, vidSize.height - 20),
			FONT_HERSHEY_COMPLEX,
			0.7,
			cv::Scalar(0, 0, 255),
			2);
		
		imshow("Video", frame);  
		writer << frame;  // writer video

		// Resize the histogram matrix and show it out
		// The reason that using the squard and divide 5 is let the color more clear 
		cv::Mat histCtn;
		cv::resize(hist, histCtn, Size(), 8, 40, INTER_NEAREST);
		cv::sqrt(histCtn, histCtn);
		histCtn /=5;

		imshow("Histogram", histCtn);

		char key = (char)waitKey(10);
		if (key == 27) {
			break;
		}
		switch (char(key)) {
		case 'r':
			showDraw = !showDraw;
			break;
		case 'h':
			showHis = !showHis;
			if (!showHis) {
				destroyWindow("Histogram");
				cout << "Histogram windows is closed" << endl;
			}
			else {
				namedWindow("Histogram");
				cout << "Histogram windows is opened" << endl;
			}
			break;
		}		
		frame_count += 1;  // frame add one
	}

	cout << "Congrats for finished the game. Total amount: " << int(sum(hist).val[0]) << endl;
	destroyAllWindows();
	return 0;
}

//! [Detection]
// Detect face position (x, y, w, h)
vector<Rect> detectFace(cv::Mat frame) {
	vector<Rect> faces;
	cv::Mat frameGray;
	cvtColor(frame, frameGray, COLOR_BGR2GRAY);
	equalizeHist(frameGray, frameGray);
	// Detect faces
	face_cascade.detectMultiScale(frameGray, faces, 1.5, 4, 0 | CASCADE_SCALE_IMAGE, cv::Size(80, 80));
	//face_cascade.detectMultiScale(frameGray, faces, 1.6, 4, 0 | CASCADE_SCALE_IMAGE, cv::Size(80, 80));

	return faces;
}

// Detect eye position
vector<Rect> detectEye(cv::Mat faceROI) {
	vector<Rect> eyes;
	cv::Mat frameGray;
	cvtColor(frame, frameGray, COLOR_BGR2GRAY);
	equalizeHist(frameGray, frameGray);
	// detect eyes
	eyes_cascade.detectMultiScale(frameGray, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, cv::Size(20, 20));
	return eyes;
}

vector<Vec3f> detectCircle(Mat frame) {
	cv::Mat gray;
	vector<Vec3f> circles;
	cv::cvtColor(frame, gray, COLOR_BGR2GRAY);
	cv::GaussianBlur(gray, gray, Size(5, 5), 2, 2);
	cv::HoughCircles(gray, circles, HOUGH_GRADIENT, 1.3, gray.rows / 120, 150, 100, 40, 90);
	return circles;
}
//! [Detection]

//! [Drawing]
Mat boxFace(cv::Mat frame, vector<Rect> faces) {
	if (faces.size() > 0) {
		for (size_t i = 0; i < faces.size(); i++) {
			int x = faces[i].x;
			int y = faces[i].y;
			int w = faces[i].width;
			int h = faces[i].height;
			rectangle(frame, Point(x, y), Point(x + w, y + h), cv::Scalar(255, 0, 255), 1, LINE_AA);
		}
	}
	return frame;
}

Mat drawEye(cv::Mat frame, Rect face, vector<Rect> eyes) {
	if (eyes.size() > 0) {
		for (size_t i = 0; i < eyes.size(); i++) {
			int x = eyes[i].x;
			int y = eyes[i].y;
			int w = eyes[i].width;
			int h = eyes[i].height;
			rectangle(frame, Point(x, y), Point(x + w, y + h), cv::Scalar(255, 255, 0), 1, LINE_AA);
		}
	}
	return frame;
}

Mat drawCircle(cv::Mat frame, vector<Vec3f> circles) {
	for (size_t i = 0; i < circles.size(); i++) {
		Vec3i c = circles[i];
		Point center = Point(cvRound(c[0]), cvRound(c[1]));
		int radius =  cvRound(c[2]);
		circle(frame, center, radius, cv::Scalar(255, 0, 0), 2, LINE_AA);
	}
	return frame;
}
//! [Drawing]