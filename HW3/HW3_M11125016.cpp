//HW3: �H���s�� Level3 �{�����e����
// 
//0511�ݸѨM����
//1.Ĳ�o��onMouse��A�A�i��onTrackbar�ƥ�|�L�k��waitkey���X�A�]�|�L�k�A�I
//2.onTrakcer�n�i�H�ϥ�onMouse�ʧ@�᪺�v��


#include "opencv2/opencv.hpp" //���J�Ҧ� openCV �禡�w

using namespace cv; //�]�wopenCV�禡���R�W�Ŷ�
using namespace std; //�]�w�з�C++�禡���R�W�Ŷ�

// Global variables
Mat src_img, img_neg, smoothed_output, neg_output;
string winName = "Tracker app";

const int slider_max = 100; // cont define a constant value that can't be change
int slider1 = 0; // �վ�쪺�w�]�ȡA��ƫ��A
int slider2 = 0; // �վ�쪺�w�]�ȡA��ƫ��A

vector<Point> point;
bool first_point_is_drawned = false;
bool line_linked = true;


//�Ʊ�^�I�禡
void onTrackbar(int pos, void*) {
	double alpha, beta;
	Mat src_clone, img_HSV, mask, img_Guss, img_masked, smoothed_output_clone; // �ŧi hsv�v���P����B�n

	src_clone = src_img.clone();
	img_masked = src_img.clone();

	// �� cvtColor() �Nsrc_clone�ഫ��HSV�Ŷ�
	cvtColor(src_clone, img_HSV, COLOR_BGR2HSV); 
	
	// �� inRange() �禡���ͽ���B�n�AHSV�d��U��(0, 20, 80)�A�W��(40, 255, 255)
	inRange(img_HSV, Scalar(0, 20, 80), Scalar(40, 255, 255), mask);

	// �إ�13x13����ε��c������B�n�i��G�k
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(13, 13)); 	
	erode(mask, mask, element);

	// img_HSV��17x17�������ҽk GaussianBlur�A�o��ҽk�ƪ��v��
	GaussianBlur(src_clone, img_Guss, Size(17, 17), 0, 0); 

	// img_guss is masked by mask, then output img_masked
	img_Guss.copyTo(img_masked, mask); 

	// �ھ�slider1���ƭȡA��addWeighted()��src_clone�Pimg_masked���[�v�V�X�A���G�Osmoothed_output
	alpha = (double)slider1 / slider_max;
	beta = (1.0 - alpha);
	addWeighted(src_clone, beta, img_masked, alpha, 0.0, smoothed_output); 


	// Negative ROI
	int pos_x;
	smoothed_output_clone = smoothed_output.clone();
	img_neg = smoothed_output.clone();
	
	// ��slider�ưʮɡApos_x�|�o��Ӽv���ưʹ�������ҡA�ô��Ѥ@�Ӧ�m�ϦV���ĪG
	if (slider2 > 0) {
		pos_x = (img_neg.size().width / slider_max) * slider2;
		Rect roi(0, 0, pos_x, img_neg.size().height);
		cout << "roi: " << roi << endl;
		bitwise_not(smoothed_output_clone, smoothed_output_clone);
		smoothed_output_clone(roi).copyTo(img_neg(roi));
		neg_output = img_neg.clone();
	} else {
		neg_output = smoothed_output;
	}
	imshow(winName, neg_output);
}

//�ƹ��^�I�禡�A�аѦ�cv27�d��
static void onMouse(int event, int x, int y, int flags, void*) {
	// �P�_�Ϥ��O�_���}�l�i��ƹ��s�u�A��s�u�s�_�ӫ�|���X�j��
	if (!line_linked) return;

	// �p�G�b�S���g�LonTrackBar�ƥ�A�]�i�H�����I���e��
	if (neg_output.empty()) {
		neg_output = src_img.clone();
	}

	// �I������i�H�O���I
	if (event == EVENT_LBUTTONDOWN) {
		Point new_pt = Point(x, y);
		cout << new_pt << endl;
		// �p�G<vector>point�S����ơA���N�|�N�Ĥ@����Ʃ�J�A��first_point_is_drawned��boolean�ܦ�True
		if (point.empty()) {
			point.push_back(new_pt);
			circle(neg_output, new_pt, 7, Scalar(0, 255, 255), -1);
			first_point_is_drawned = true;
		}
		else {
			point.push_back(new_pt);
			Point& end = point.back();
			double dis = norm(new_pt - point[0]);
			cout << dis << endl;
			// ���I���Z���p��20�A�Bfirst_point_is_drawned�Otrue�h�|����o�@�q
			if (dis <= 20 && first_point_is_drawned) {
				point.back() = point[0];
				line(neg_output, point[point.size() - 2], point[0], Scalar(255, 255, 255), 2);
				line_linked = false;
			}
			// �_�h�|�~��e�u
			else {
				line(neg_output, point[point.size() - 2], new_pt, Scalar(255, 255, 255), 2);
				circle(neg_output, new_pt, 7, Scalar(0, 255, 255), -1);
			}
		}
		imshow(winName, neg_output);
	}
}


int main(int, char** argv)
{
	cout << "�ϥλ���" << endl;
	cout << "Click lefy mouse to point the mark on the image, until the shape is completed" << endl;
	cout << "Can press 'r' or empty to reset the image, or" << endl;
	cout << "Press 'q' or 'esc' to leave" << endl;
	

	// Ū��argv[1]���|/�ɦW���v��
	src_img = imread(argv[1], 1);

	// �T�w�v���O�_�iŪ
	if (src_img.empty()) {
		std::cout << "Could not read the image" << endl;
	}

	// �����R�W�A��Ū����l�v��
	namedWindow(winName);
	imshow(winName, src_img);
	// �إ�"���Ƥ�"�վ��A�վ��ܼƬO slider1
	createTrackbar("Smooth", winName, &slider1, slider_max, onTrackbar);

	// �إ�"�ϥ�"�վ��A�վ��ܼƬO slider2
	createTrackbar("Negative", winName, &slider2, slider_max, onTrackbar);

	// ��l�Ʒƹ��^�I�禡  (�i�Ѧ�cv27�d��)
	setMouseCallback(winName, onMouse, NULL); // ��l�Ʒƹ��^�I�禡

	
	// while(1)�L���j��A��waitKey()Ū�X���r��(��ASCII�X)�@�����}�έ��m���ﶵ
	while (true) {
		int key = waitKey(0);
		if (key == 27 || key == 'q') {
			break;
		}
		else if (key == 'r' || key == ' ') {
			point.clear();
			neg_output = img_neg;
			first_point_is_drawned = false;
			line_linked = true;
			key = waitKey(0);
			imshow(winName, src_img);
		}
	}
	return 0;
}
