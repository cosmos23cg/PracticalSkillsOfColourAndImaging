/*HW3: 人像編輯 Level3 程式內容提示*/
#include "opencv2/opencv.hpp" //載入所有 openCV 函式庫

using namespace cv; //設定openCV函式的命名空間
using namespace std; //設定標準C++函式的命名空間

/*全域變數*/
Mat im1, im2, im3, im4, im5, im6;
 //調整桿的預設值(整數 int 型態)
 //上一次的滑鼠點擊(x,y)位置(Point 型態)
//滑鼠按下的位置是否是連線的起始點(整數 int 或布林 bool 型態)

/*滑桿回呼函式*/
void onTrackbar(int, void*) {
	//用 setTrackbarPos(滑桿名,視窗名,滑桿數值) 讀取slider1 (模糊混合)數值，不用也可以
	//用 setTrackbarPos(滑桿名,視窗名,滑桿數值) 讀取slider2 (反白範圍)數值，不用也可以

	//將 slider2 的數值換算成影像反白區域的寬
	//將 im1 複製成 im2
	//將 im1 複製成 im3
	//宣告 hsv影像與膚色遮罩 (Mat 型態)
	//用 cvtColor(輸入影像,輸出影像,色彩轉換參數) 將 im2 轉換至HSV空間
	//用 inRange(輸入影像,範圍下界,範圍上界,遮罩) 函式產生膚色遮罩，HSV範圍下界(0, 20, 80)，上界(40, 255, 255)
	//建立13x13的圓形結構元素 (可參考Tutorial/Image filtering/Morphology_1範例)
	//對膚色遮罩做腐蝕 erode(輸入影像,輸出影像,結構元素)
	//對im2做17x17的高斯模糊 GaussianBlur(輸入影像,輸出影像,濾鏡尺寸,0,0)
	//將 im2 的膚色遮罩部分，複製到 im3 (用 copyTo(影像,遮罩))
	//根據slider1的數值，用addWeighted()對im1與im3做加權混合，結果是im4 (可參考Tutorial/Basic/Addingimages範例)

	/*建立反白區域的 roi，注意防呆*/
	//將 im4 複製成 im5
	//將 im4 複製成 im6
	//用 bitwise_not(輸入影像,輸出影像) 將 im5 影像反白
	//用copyTo方法，將im5的 roi 區域複製到 im6 的 roi 區域(可參考cv26範例)

	 //用 imshow()顯示 im6 (可參考cv13範例)
}

/*滑鼠回呼函式 (請參考cv27,cv30,cv32範例) */
static void onMouse(int event, int x, int y, int flags, void*)
{
//....
}

/*主程式 (可參考Tutorial/Image filtering/Morphology_1範例)*/
int main(int, char** argv)
{
	cout<<"使用說明"<<endl<<endl; 
        
    //讀取argv[1]路徑/檔名的影像

	//確定影像是否可讀
	    //視窗命名
		//建立"平滑化"調整桿，調整變數是 slider1 (可參考Tutorial/Image filtering/Morphology_1範例)
		//建立"反白"調整桿，調整變數是 slider2
		//執行滑桿回呼函式(初始化)
		 

		//while(1)無限迴圈，用waitKey()讀出的字元(或ASCII碼)作為離開或重置的選項(可參考cv13範例)
		//.....
 
    return 0;
}
