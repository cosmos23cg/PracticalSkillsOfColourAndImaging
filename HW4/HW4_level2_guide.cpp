//HW4_Level2: ���� drop.mp4 ���T���A�������ɪO�A�íp����`���B�C(���G�S�����체���ɤ���)
//1.�]�w�Ѽ�
//2.�������T�����H�y�P�H��
//3.��������H���ɡA�ﱼ�����ɪO�� HoughCircles ����
//4.ø�s�H�y/�H����
//5.ø�s�ɪO��ήءA�H�ΤH�����ߪ��p�g��
//6.�Ϊ���ϲέp�C�Ӥ����϶��A���g�������ߪ��̰����B(�ھڨ�b�|)
//7.��X�t�������ءN�p�g���B�������B�����T
//8.�ھڪ���ϡA�έp�ɪO���`���B

#include "opencv2/opencv.hpp" //���Jopencv�禡�w
#include <iostream> //���Jc++�禡�w
//#include "stdafx.h" //�p�G�M�׼��Y�ɸ̸̦�stdafx.h�A��l�{���ɦ�stdafx.cpp�A�ݥ[�J�o�@��C�p�G�O�űM�סA�h���Υ[�o�@��C

using namespace cv; //�ŧi opencv �禡�w���R�W�Ŷ�
using namespace std; //�ŧi C++�禡�w���R�W�Ŷ�

/* �ѼƳ]�w(�����ܼ�) */
Mat frame; //���T�v���e��(Mat class)
int show_rect = 1; //�O�_��ܤH�y/�H���ت��Ѽ�(int type)
int frame_count = 0; //���T�e���s���p�ƾ�(int type)
 //�����H���������T����(VideoCapture class), �i�Ѧ� cv/sleepDetection.cpp
 //���T�v���e,��(Size type)
//��X�������G�����T����(VideoWriter class)
//�H�y���p��������(CascadeClassifier class)
//�H�����p��������(CascadeClassifier class)
vector<Rect> faces; //�H�y�x�ήئV�q(Rect type)
vector<Rect> eyes; //�H���x�ήئV�q(Rect type)
vector<Vec3f> circles; //�ɪO��ΦV�q(Vec3f type)
float binW = 10; //����ϨC�Ӥ����϶���M�v���e�ת�����(���:����)

/* �l�{���쫬�ŧi */
vector<Rect> detectFace(Mat); //�H�y����
vector<Rect> detectEye(Mat);  //�H������
vector<Vec3f> detectCircle(Mat); //�ɪO��ΰ���
Mat boxFace(Mat, vector<Rect>); //�H�y��ø�s
Mat drawCircle(Mat, vector<Vec3f>); //�H����ø�s
Mat drawEye(Mat, Rect, vector<Rect>); //�ɪO���ø�s

/* �D�{�� */
int main(int, char** argv) {
	/* ���p���������l��(���Jxml�Ѽ�) */
	if (!faceCascade.load("data/haarcascade_frontalface_alt.xml")) { printf("--(!)Error loading face cascade\n"); return -1; };
	if (!eyes_cascade.load("data/haarcascade_eye_tree_eyeglasses.xml")) { printf("--(!)Error loading eyes cascade\n"); return -1; };
	if (!put.isOpened()) { return -1; };

	/* �έp���B������� hist ��l��*/
	//Mat class�A�s�x�}�A�e=���T�e/binW�A��=1�ACV_32FC1�榡

	//�p�G���T����i�HŪ���ɡA����while�j�餤�����e
	while (cap.isOpened()) {
		cap.read(frame); //Ū���e��
		if (frame.empty()) break; //�p�G�e��O�Ū��A���Xwhile�j��

		/* �����H�y */
		//�l�{�������H�y�A��X�H�y��

		//�p�G���H�y�ءA����U�C�ʧ@
		{
			 //�p�G��ܤH�y/�H���ت��ѼƫD0�A����U�Cø�Ϥl�{��
			{
				//�l�{��ø�s�H�y��
				//�l�{�������H��(�`�N�G�Ȱ���faces[0]�϶�)
				//�l�{��ø�s�H����
			}

			/* �������체�� �B ��U�e��s�����H5�l0��(�i�g��not(frame_count %5))... */
			{ 
				//�l�{�������e���������

				/* ���������(�w��)��... */
				if (circles.size() > 0) {
					 //�l�{��ø�s��ή�
					
					// for �j��A�ﰻ���쪺��ΡA�@�@ø�s�ӦۤH�����p�g�A��ܿ������B�A�æs�Jhist�����
					{						
						//��i�Ӷ�ζ�ߪ�x�y��(int type)
						//��i�Ӷ�ζ�ߪ�y�y��(int type)
						//��i�Ӷ�Ϊ��b�|(int type)

						//�p�Ⲵ�������߮y��(Point type)
						//ø�s�������ߪ�����p�g(line())

						/* �Q�εw���b�|�P�_���B */
						{ //�p�G���<=47�A���B=1
						}
						{ //�p�G���>47 && <=60�A���B=5
						}
						{ //�p�G���>60 && <=67�A���B=10
						}
						{ //�_�h�A���B=50
						}
						//�b�����W��A��putText()��ܪ��B
						//�ھڶ��x�y�п��hist���϶��A�p�G�w�����B����Ӱ϶����̰����B�A�h��s�����B�C�i��|�Ψ�at<float>, cvRound, MAX()
					}
				}
			}
		}

		/* ��ܼv�� */
		//�b�e���k�U���A��putText()��ܻɪO�`���B�C���G���B���r��i�� to_string(int(sum(hist).val[0]))
		imshow("frame", frame); //��ܻɪO�����e��
		put << frame; //�N�e���s�J�ݿ�X�����T����

		/* ��ܪ���� */
		//�إߪ���ϼv���e��(Mat class)
		//�Nhist�Aresize��j�C������V��j8���A������V��j40���A�βĤT�ؤ��t�k(�F���I���N�k)�A�i�Ѧ�cv_19
		//hist �v�������ƭȬO[0,1,5,10,50]�A���e���ݥX���t�t�O�A�]���N�ƭȶ}�ڸ� sqrt(src,dst)�C
		//���Nhist�v���ƭȰ��H5�A�A��ܸӼv���C���P���B���ɪO�A�N�e�{���P�����t�A���B�V���V�G�C

		/* ��L�B�z */
		int c=waitKey(10);
		//�� Esc (ascii 27��) ���} while �j��
		//�� 'r' �����H/���ت���ܪ��A, �i�Ѧ�Tutorial/camshiftDemo.cpp
		//�i���䥦����A�W�K�\��(�Ҧp�H�y�令���ήءB�H�y�G�ȤƵ�)�A���ݭn��cout�b command window�����Ϊk

		//�e��s���[1
	}
	
	//�b command window ����`���B(��int(sum(hist).val[0]))
	destroyAllWindows(); //�����Ҧ�����
	return 0;
}



// �����H�y����m (x, y, w, h)
vector<Rect> detectFace(Mat frame) {
	vector<Rect> faces;
	Mat frame_gray;
	//�ন�Ƕ��v��
	 //�H�y�h�ثׯ��p�����A�Ѽ�1.5, 4, 0, Size(80, 80)�A�аѦ�Tutorial/faceEyeDetection.cpp
	return faces;
}


// ������������m (x, y, w, h)
vector<Rect> detectEye(Mat faceROI) {
	Mat frame_gray;
	vector<Rect> eyes;
	//�ন�Ƕ��v��
	 //�H���h�ثׯ��p�����A�Ѽ�1.1, 2, 0, Size(20, 20)�A�аѦ�Tutorial/faceEyeDetection.cpp
	return eyes;
}	


// �����ꪺ��m (x, y, r)
vector<Vec3f> detectCircle(Mat frame) {
	Mat gray;
	vector<Vec3f> circles;
	cvtColor(frame, gray, COLOR_BGR2GRAY); //�ন�Ƕ��v��
	//�N�Ҷ갻���A�Ѽ�1.3, 120, 150, 100, 40, 90�C�аѾ\Tutorial/HoughCircle_Demo.cpp
	return circles;
}


// �e�X�H�y����m(�аѦ�Tutorial / faceEyeDetection.cpp)
Mat boxFace(Mat frame, vector<Rect> faces) {
	if (faces.size() > 0) {
		for (size_t i = 0; i < faces.size(); i++) {
			int x = faces[i].x;
			int y = faces[i].y;
			int w = faces[i].width;
			int h = faces[i].height;
			rectangle(frame, Point(x, y), Point(x + w, y + h), Scalar(255, 255, 0), 1, LINE_AA); 
		}
	}
	return frame;
}


// �e�X�ꪺ��m(�аѦ�cv_32)
Mat drawCircle(Mat frame, vector<Vec3f> circles) {
	{ //��for�j��ø�s circles ���C�@�Ӷ��
		//�i�λݭncvRound()�|�ˤ��J�����
		//��circle�A����A�u��=2
	}
	return frame;
}


// �e�X��������m
Mat drawEye(Mat frame, Rect face, vector<Rect> eyes) {
	{ //��for�j��ø�s eyes ����
		//�ݭn�Nface��x,y�y�Х[�Weyes��x,y�y��
		//��retangle �� circle�A�C��A�u��=1
	}
	return frame;
}


