// HW4_Level2: ���� drop.mp4 ���T���A�������ɪO�A�íp����`���B�C(���G�S�����체���ɤ���)
// 1.�]�w�Ѽ�
// 2.�������T�����H�y�P�H��
// 3.��������H���ɡA�ﱼ�����ɪO�� HoughCircles ����
// 4.ø�s�H�y/�H����
// 5.ø�s�ɪO��ήءA�H�ΤH�����ߪ��p�g��
// 6.�Ϊ���ϲέp�C�Ӥ����϶��A���g�������ߪ��̰����B(�ھڨ�b�|)
// 7.��X�t�������ءN�p�g���B�������B�����T
// 8.�ھڪ���ϡA�έp�ɪO���`���B

#include "opencv2/opencv.hpp"  // load opencv library
#include <iostream>  // load standarf library

using namespace cv;  // constant namespace of opencv
using namespace std;  // constant namespace of standard

// GLOBAL VARIABLE
cv::Mat frame;  // container of video frame
int show_rect = 1;  // shows the face/ eyes parameter
int frame_count = 0;  // frame count for video

cv::VideoCapture cap("data/drop.mp4");  // // Coins randomly drop object as cap
cv::Size vidSize(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));  //  video size
//cv::VideoWriter writer("data/dropndetect.mp4", cv::VideoWriter::fourcc('x', '2', '6', '4'), 60, vidSize); // write video
cv::CascadeClassifier face_cascade;  // detect face object
cv::CascadeClassifier eyes_cascade;  // detect eyes object

vector<Rect> faces;  // vector object of face rectangle
vector<Rect> eyes;  // vector object of eyes rectangle
vector<Vec3f> circles;  // vector object of coins circle
float binW = 10;  // length of each horizontal mapping of the histogram corespoding to the width of the image (pixel)

/* �l�{���쫬�ŧi */
vector<Rect> detectFace(Mat); //�H�y����
vector<Rect> detectEye(Mat);  //�H������
vector<Vec3f> detectCircle(Mat); //�ɪO��ΰ���
Mat boxFace(Mat, vector<Rect>); //�H�y��ø�s
Mat drawCircle(Mat, vector<Vec3f>); //�H����ø�s
Mat drawEye(Mat, Rect, vector<Rect>); //�ɪO���ø�s

int main(int, char** argv) {
	//! [load the cascades]
	if (!face_cascade.load("data/haarcascade_frontalface_alt.xml")) {
		cout << "--(!)Error loading face cascade" << endl;
		return -1;
	}
	if (!eyes_cascade.load("data/haarcascade_eye_tree_eyeglasses.xml")) {
		cout << "--(!)Error laoding eyes cascade" << endl;
		return -1;
	}

	/*if (!writer.isOpened()) {
		cout << "--(!)Can't write the frame" << endl;
		return -1;
	}*/
	//! [load the cascades]

	// Read the video sream
	while (cap.isOpened()) {
		cap.read(frame);
		if (frame.empty()) {
			cout << "The frame can't open" << endl;
			break;
		}
		
		//! [Detect the face]
		// output rectangle if detected the face


		//! [Detect Circle]



		imshow("video", frame);
		//writer << frame;
		int c = waitKey(10);
		
		frame_count += 1;  // frame add one
	}

	destroyAllWindows();
	return 0;
}

//! [Detection]
// Detect face, eye position


// Detect face position (x, y, w, h)
vector<Rect> detectFace(cv::Mat frame) {
	vector<Rect> faces;
	cv::Mat frameGray;
	cvtColor(frame, frameGray, COLOR_BGR2GRAY);
	equalizeHist(frameGray, frameGray);
	// Detect faces
	face_cascade.detectMultiScale(frameGray, faces, 1.5, 4, 0 | CASCADE_SCALE_IMAGE, cv::Size(80, 80));
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
	cv::GaussianBlur(gray, gray, Size(9, 9), 2, 2);
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
			/*Point eyeCenter(face.x + eyes[i].x + eyes[i].width / 2, face.y + eyes[i].y + eyes[i].height / 2);
			int radius = cvRound((eyes[i].width + eyes[i].height) * 0.25);
			circle(frame, eyeCenter, radius, cv::Scalar(255, 255, 0), 1, LINE_AA);*/
			//int x = face.x + eyes[i].x;
			//int y = face.y + eyes[i].y;
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