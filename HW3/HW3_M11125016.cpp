//HW3: 人像編輯 Level3 程式內容提示
// 
//0511待解決項目
//1.觸發完onMouse後，再進行onTrackbar事件會無法按waitkey跳出，也會無法再點
//2.onTrakcer要可以使用onMouse動作後的影像


#include "opencv2/opencv.hpp" //載入所有 openCV 函式庫

using namespace cv; //設定openCV函式的命名空間
using namespace std; //設定標準C++函式的命名空間

// Global variables
Mat src_img, img_neg, smoothed_output, neg_output;
string winName = "Tracker app";

const int slider_max = 100; // cont define a constant value that can't be change
int slider1 = 0; // 調整桿的預設值，整數型態
int slider2 = 0; // 調整桿的預設值，整數型態

vector<Point> point;
bool first_point_is_drawned = false;
bool line_linked = true;


//滑桿回呼函式
void onTrackbar(int pos, void*) {
	double alpha, beta;
	Mat src_clone, img_HSV, mask, img_Guss, img_masked, smoothed_output_clone; // 宣告 hsv影像與膚色遮罩

	src_clone = src_img.clone();
	img_masked = src_img.clone();

	// 用 cvtColor() 將src_clone轉換至HSV空間
	cvtColor(src_clone, img_HSV, COLOR_BGR2HSV); 
	
	// 用 inRange() 函式產生膚色遮罩，HSV範圍下界(0, 20, 80)，上界(40, 255, 255)
	inRange(img_HSV, Scalar(0, 20, 80), Scalar(40, 255, 255), mask);

	// 建立13x13的圓形結構元素對遮罩進行腐蝕
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(13, 13)); 	
	erode(mask, mask, element);

	// img_HSV做17x17的高斯模糊 GaussianBlur，得到模糊化的影像
	GaussianBlur(src_clone, img_Guss, Size(17, 17), 0, 0); 

	// img_guss is masked by mask, then output img_masked
	img_Guss.copyTo(img_masked, mask); 

	// 根據slider1的數值，用addWeighted()對src_clone與img_masked做加權混合，結果是smoothed_output
	alpha = (double)slider1 / slider_max;
	beta = (1.0 - alpha);
	addWeighted(src_clone, beta, img_masked, alpha, 0.0, smoothed_output); 


	// Negative ROI
	int pos_x;
	smoothed_output_clone = smoothed_output.clone();
	img_neg = smoothed_output.clone();
	
	// 當slider滑動時，pos_x會得到該影像滑動像素的比例，並提供一個色彩反向的效果
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

//滑鼠回呼函式，請參考cv27範例
static void onMouse(int event, int x, int y, int flags, void*) {
	// 判斷圖片是否有開始進行滑鼠連線，當連線連起來後會跳出迴圈
	if (!line_linked) return;

	// 如果在沒有經過onTrackBar事件，也可以直接點擊畫面
	if (neg_output.empty()) {
		neg_output = src_img.clone();
	}

	// 點擊左鍵可以記錄點
	if (event == EVENT_LBUTTONDOWN) {
		Point new_pt = Point(x, y);
		cout << new_pt << endl;
		// 如果<vector>point沒有資料，那就會將第一筆資料放入，並first_point_is_drawned的boolean變成True
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
			// 當點的距離小於20，且first_point_is_drawned是true則會執行這一段
			if (dis <= 20 && first_point_is_drawned) {
				point.back() = point[0];
				line(neg_output, point[point.size() - 2], point[0], Scalar(255, 255, 255), 2);
				line_linked = false;
			}
			// 否則會繼續畫線
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
	cout << "使用說明" << endl;
	cout << "Click lefy mouse to point the mark on the image, until the shape is completed" << endl;
	cout << "Can press 'r' or empty to reset the image, or" << endl;
	cout << "Press 'q' or 'esc' to leave" << endl;
	

	// 讀取argv[1]路徑/檔名的影像
	src_img = imread(argv[1], 1);

	// 確定影像是否可讀
	if (src_img.empty()) {
		std::cout << "Could not read the image" << endl;
	}

	// 視窗命名，並讀取原始影像
	namedWindow(winName);
	imshow(winName, src_img);
	// 建立"平滑化"調整桿，調整變數是 slider1
	createTrackbar("Smooth", winName, &slider1, slider_max, onTrackbar);

	// 建立"反白"調整桿，調整變數是 slider2
	createTrackbar("Negative", winName, &slider2, slider_max, onTrackbar);

	// 初始化滑鼠回呼函式  (可參考cv27範例)
	setMouseCallback(winName, onMouse, NULL); // 初始化滑鼠回呼函式

	
	// while(1)無限迴圈，用waitKey()讀出的字元(或ASCII碼)作為離開或重置的選項
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
