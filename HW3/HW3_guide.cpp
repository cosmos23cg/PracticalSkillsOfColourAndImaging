/*HW3: �H���s�� Level3 �{�����e����*/
#include "opencv2/opencv.hpp" //���J�Ҧ� openCV �禡�w

using namespace cv; //�]�wopenCV�禡���R�W�Ŷ�
using namespace std; //�]�w�з�C++�禡���R�W�Ŷ�

/*�����ܼ�*/
Mat im1, im2, im3, im4, im5, im6;
 //�վ�쪺�w�]��(��� int ���A)
 //�W�@�����ƹ��I��(x,y)��m(Point ���A)
//�ƹ����U����m�O�_�O�s�u���_�l�I(��� int �Υ��L bool ���A)

/*�Ʊ�^�I�禡*/
void onTrackbar(int, void*) {
	//�� setTrackbarPos(�Ʊ�W,�����W,�Ʊ�ƭ�) Ū��slider1 (�ҽk�V�X)�ƭȡA���Τ]�i�H
	//�� setTrackbarPos(�Ʊ�W,�����W,�Ʊ�ƭ�) Ū��slider2 (�ϥսd��)�ƭȡA���Τ]�i�H

	//�N slider2 ���ƭȴ��⦨�v���ϥհϰ쪺�e
	//�N im1 �ƻs�� im2
	//�N im1 �ƻs�� im3
	//�ŧi hsv�v���P����B�n (Mat ���A)
	//�� cvtColor(��J�v��,��X�v��,��m�ഫ�Ѽ�) �N im2 �ഫ��HSV�Ŷ�
	//�� inRange(��J�v��,�d��U��,�d��W��,�B�n) �禡���ͽ���B�n�AHSV�d��U��(0, 20, 80)�A�W��(40, 255, 255)
	//�إ�13x13����ε��c���� (�i�Ѧ�Tutorial/Image filtering/Morphology_1�d��)
	//�ｧ��B�n���G�k erode(��J�v��,��X�v��,���c����)
	//��im2��17x17�������ҽk GaussianBlur(��J�v��,��X�v��,�o��ؤo,0,0)
	//�N im2 ������B�n�����A�ƻs�� im3 (�� copyTo(�v��,�B�n))
	//�ھ�slider1���ƭȡA��addWeighted()��im1�Pim3���[�v�V�X�A���G�Oim4 (�i�Ѧ�Tutorial/Basic/Addingimages�d��)

	/*�إߤϥհϰ쪺 roi�A�`�N���b*/
	//�N im4 �ƻs�� im5
	//�N im4 �ƻs�� im6
	//�� bitwise_not(��J�v��,��X�v��) �N im5 �v���ϥ�
	//��copyTo��k�A�Nim5�� roi �ϰ�ƻs�� im6 �� roi �ϰ�(�i�Ѧ�cv26�d��)

	 //�� imshow()��� im6 (�i�Ѧ�cv13�d��)
}

/*�ƹ��^�I�禡 (�аѦ�cv27,cv30,cv32�d��) */
static void onMouse(int event, int x, int y, int flags, void*)
{
//....
}

/*�D�{�� (�i�Ѧ�Tutorial/Image filtering/Morphology_1�d��)*/
int main(int, char** argv)
{
	cout<<"�ϥλ���"<<endl<<endl; 
        
    //Ū��argv[1]���|/�ɦW���v��

	//�T�w�v���O�_�iŪ
	    //�����R�W
		//�إ�"���Ƥ�"�վ��A�վ��ܼƬO slider1 (�i�Ѧ�Tutorial/Image filtering/Morphology_1�d��)
		//�إ�"�ϥ�"�վ��A�վ��ܼƬO slider2
		//����Ʊ�^�I�禡(��l��)
		 

		//while(1)�L���j��A��waitKey()Ū�X���r��(��ASCII�X)�@�����}�έ��m���ﶵ(�i�Ѧ�cv13�d��)
		//.....
 
    return 0;
}
