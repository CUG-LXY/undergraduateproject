#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace cv;
using namespace std;


//typedef unsigned char uchar;

class PixImage {
public:
	friend class RunLengthEncoding;
	PixImage();//���캯��
	PixImage(Mat mat);//���캯������
	void Read(string a);//��ȡͼƬ
	void getpix();//�õ�����ǿ�ȵĵ��ú���
	void getPixel(int Len, int Wid);//�õ�ͼƬĳ���ص�ĺ�����ǿ��
	void Mod();//�޸����غ����ĵ��ú���
	void Modifypx(uchar x, uchar y, uchar num1,uchar num2,uchar num3);//�޸�����
	Mat Fuzzy(int times);//ģ������
	inline uchar Conv(Mat mt, int x, int y,int k, double kernel[3][3]);//������㣬�����������input����input[x][y]����ʼ�������õ������� 
	void EdgeDetection(string a);//��Ե���
	inline int Conv1(Mat mt, int x, int y, int kernel_x[3][3], int kernel_y[3][3]);//��Ե����еľ������,����Ϊ����������������
	void CreatTiff(string a);//����tif�ļ�
	void PrintPic();  //���ͼƬ
	int getLength();//�õ����鳤��
	int getWidth();//�õ�������
	void change();//�޸ĳ���ĵ��ú���
	void Change(int Len, int Wid);//�޸ĳ���
private:
	Mat mt;
};


//���캯��
PixImage::PixImage(){}
PixImage::PixImage(Mat mat)//���캯������
{
	mt = mat;
}

//��ȡͼƬ����
void PixImage::Read(string a)
{
	
	mt = imread(a);

}
//�õ����ص�ĵ��ú���
void PixImage::getpix()
{
	cout << "ͼƬ����Ϊ" << mt.cols << "��ͼƬ���Ϊ" << mt.rows << "���벻Ҫ���������Χ" << endl;
	cout << "����������õ������ص�λ��" << endl;
	int num1, num2;
	cin >> num1 >> num2;
	getPixel(num1, num2);
}
//�õ�ĳһ�������
void PixImage::getPixel(int Len, int Wid)
{
	cout << "(" << Len << "," << Wid << ")" << "�������ֵΪ" << int(mt.at<Vec3b>(Len, Wid)[0]) << "," << int(mt.at<Vec3b>(Len, Wid)[1]) << "," << int(mt.at<Vec3b>(Len, Wid)[2]) << endl;
}
//�޸����غ����ĵ��ú���
void PixImage::Mod()
{
	cout << "ͼƬ����Ϊ" << mt.cols << "��ͼƬ���Ϊ" << mt.rows << "���벻Ҫ���������Χ" << endl;
	cout << "����������Ҫ�޸����ص�λ��" << endl;
	int x, y;
	cin >> x >> y;
	getPixel(x, y);
	cout << "����������Ҫ�޸ĵ�����ֵ" << endl;
	int num1, num2, num3;
	cin >> num1 >> num2 >> num3;
	Modifypx(x, y, num1, num2, num3);
	getPixel(x, y);
	cout << "���޸���ɣ�" << endl;
}

//�޸�����
void PixImage::Modifypx(uchar x,uchar y,uchar num1,uchar num2,uchar num3)//��(x,y)������������ֵ�����޸�
{
	mt.at<Vec3b>(x,y)[0] = num1;
	mt.at<Vec3b>(x, y)[1] = num2;
	mt.at<Vec3b>(x, y)[2] = num3;
}


//ģ���������ݹ�
Mat PixImage::Fuzzy(int times)
{
	if (times == 0)//�ݹ麯������
	{
		return mt;
	}
	double kernel[3][3] = { {0.0947416,0.118318,0.0947416},{0.118318,0.147761,0.118318},{0.0947416,0.118318,0.0947416} };//�����kernel ����
	Mat img = mt;
	for (int i = 0; i < mt.rows; i++) //������
	{
		for (int j = 0; j < mt.cols; j++) {
			for (int k = 0; k < 3; k++)//��ɫͼƬ����ͨ����������Ҫ��������
			{
					img.at<Vec3b>(i, j)[k] = Conv(mt, i, j, k, kernel);
			}
		}

	}
	
	return Fuzzy(times - 1);
}


//������㣬�����������input����input[x][y]����ʼ�������õ������� 
inline uchar PixImage::Conv(Mat mt, int x, int y,int k, double kernel[3][3]) {
	uchar count = 0;
	uchar output[3][3] = { 0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			if (i + x >= mt.rows || j + y >= mt.cols)//�Ա߽�������п���
			{
				output[i][j] = mt.at<Vec3b>(abs(x-i), abs(y-j  ))[k] * kernel[i][j];//�������
				count += output[i][j];
			}
			else {
				output[i][j] = mt.at<Vec3b>(i + x , j + y )[k] * kernel[i][j];//�������
				count += output[i][j];
			}
		}
	}
	return count;
}



//��Ե���
void PixImage::EdgeDetection(string a)//�ַ���aΪ��ȡ�ļ�·��
{
	int kernel_x[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	int kernel_y[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	mt = imread(a, 0);
	//PrintPic();
	Mat img = mt;
	for (int i = 0; i < mt.rows; i++) //������
	{
		for (int j = 0; j < mt.cols; j++) {
			img.at<uchar>(i, j) =Conv1(mt, i, j, kernel_x, kernel_y);
		}
	}
	//PrintPic();
}

//��Ե����еľ������
inline int PixImage::Conv1(Mat mt, int x, int y, int kernel_x[3][3], int kernel_y[3][3]) {
	int output_x[3][3] = { 0 };
	int output_y[3][3] = { 0 };
	int count_x = 0, count_y = 0;
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			if (i + x >= mt.rows || j + y >= mt.cols)//�Ա߽�������п���
			{
				output_x[i][j] =  mt.at<uchar>(abs(x - i), abs(y - j)) * kernel_x[j][i];//�������
				count_x += output_x[i][j];
				output_y[i][j] =  mt.at<uchar>(abs(x - i), abs(y - j)) * kernel_y[j][i];
				count_y += output_y[i][j];
			}
			else {
				output_x[i][j] = mt.at<uchar>(x + i, y + j) * kernel_x[j][i];//�������
				count_x += output_x[i][j];
				output_y[i][j] = mt.at<uchar>(x + i, y + j) * kernel_y[j][i];
				count_y += output_y[i][j];
			}
		}
	}
	count = abs(count_x) + abs(count_y);
	if (count > 255)count = 255;//��ֹ�������0-255
	else if (count < 0)count = 0;
	return count;
}


//����tif�ļ�
void PixImage::CreatTiff(string a)
{
	imwrite(a, mt);//�ַ���aΪд���ļ���·��
}


//���ͼƬ
void PixImage::PrintPic()
{
	namedWindow("test");
	imshow("test", mt);
	waitKey(100);
}


//�õ�����
int PixImage::getLength()
{
	return mt.cols+1;//��0��ʼ��ʵ�ʳ��ȱ�colsֵ��1
}

//�õ����
int PixImage::getWidth()
{
	return mt.rows+1;//��0��ʼ��ʵ�ʿ�ȱ�rowsֵ��1
}
//�޸ĳ���ĵ��ú���
void PixImage::change()
{
	cout << "ͼƬ����Ϊ" << getLength() << ",ͼƬ���Ϊ" << getWidth();
	cout << ",�벻Ҫ���������Χ" << endl;
	cout << "����������Ҫ�޸ĵĳ��Ϳ��ֵ" << endl;
	int num1, num2;
	cin >> num1 >> num2;
	Change(num1, num2);
	cout << "ͼƬ����Ϊ" << mt.cols << ",ͼƬ���Ϊ" << mt.rows;
}
//�޸�ͼ�񳤿�
void PixImage::Change(int Len, int Wid)
{
	mt.cols = Len;
	mt.rows = Wid;
}