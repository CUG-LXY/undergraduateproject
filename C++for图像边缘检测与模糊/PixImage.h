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
	PixImage();//构造函数
	PixImage(Mat mat);//构造函数重载
	void Read(string a);//读取图片
	void getpix();//得到像素强度的调用函数
	void getPixel(int Len, int Wid);//得到图片某像素点的红绿蓝强度
	void Mod();//修改像素函数的调用函数
	void Modifypx(uchar x, uchar y, uchar num1,uchar num2,uchar num3);//修改像素
	Mat Fuzzy(int times);//模糊函数
	inline uchar Conv(Mat mt, int x, int y,int k, double kernel[3][3]);//卷积计算，输入任意矩阵input，从input[x][y]处开始计算卷积得到并返回 
	void EdgeDetection(string a);//边缘检测
	inline int Conv1(Mat mt, int x, int y, int kernel_x[3][3], int kernel_y[3][3]);//边缘检测中的卷积计算,设置为内联函数，更快速
	void CreatTiff(string a);//创建tif文件
	void PrintPic();  //输出图片
	int getLength();//得到数组长度
	int getWidth();//得到数组宽度
	void change();//修改长宽的调用函数
	void Change(int Len, int Wid);//修改长宽
private:
	Mat mt;
};


//构造函数
PixImage::PixImage(){}
PixImage::PixImage(Mat mat)//构造函数重载
{
	mt = mat;
}

//读取图片函数
void PixImage::Read(string a)
{
	
	mt = imread(a);

}
//得到像素点的调用函数
void PixImage::getpix()
{
	cout << "图片长度为" << mt.cols << "，图片宽度为" << mt.rows << "。请不要超过这个范围" << endl;
	cout << "请输入你想得到的像素点位置" << endl;
	int num1, num2;
	cin >> num1 >> num2;
	getPixel(num1, num2);
}
//得到某一点的像素
void PixImage::getPixel(int Len, int Wid)
{
	cout << "(" << Len << "," << Wid << ")" << "点的像素值为" << int(mt.at<Vec3b>(Len, Wid)[0]) << "," << int(mt.at<Vec3b>(Len, Wid)[1]) << "," << int(mt.at<Vec3b>(Len, Wid)[2]) << endl;
}
//修改像素函数的调用函数
void PixImage::Mod()
{
	cout << "图片长度为" << mt.cols << "，图片宽度为" << mt.rows << "。请不要超过这个范围" << endl;
	cout << "请输入你需要修改像素的位置" << endl;
	int x, y;
	cin >> x >> y;
	getPixel(x, y);
	cout << "请输入你需要修改的三个值" << endl;
	int num1, num2, num3;
	cin >> num1 >> num2 >> num3;
	Modifypx(x, y, num1, num2, num3);
	getPixel(x, y);
	cout << "已修改完成！" << endl;
}

//修改像素
void PixImage::Modifypx(uchar x,uchar y,uchar num1,uchar num2,uchar num3)//对(x,y)处的三个像素值进行修改
{
	mt.at<Vec3b>(x,y)[0] = num1;
	mt.at<Vec3b>(x, y)[1] = num2;
	mt.at<Vec3b>(x, y)[2] = num3;
}


//模糊函数，递归
Mat PixImage::Fuzzy(int times)
{
	if (times == 0)//递归函数出口
	{
		return mt;
	}
	double kernel[3][3] = { {0.0947416,0.118318,0.0947416},{0.118318,0.147761,0.118318},{0.0947416,0.118318,0.0947416} };//卷积核kernel 矩阵
	Mat img = mt;
	for (int i = 0; i < mt.rows; i++) //计算卷积
	{
		for (int j = 0; j < mt.cols; j++) {
			for (int k = 0; k < 3; k++)//彩色图片是三通道，所有需要计算三次
			{
					img.at<Vec3b>(i, j)[k] = Conv(mt, i, j, k, kernel);
			}
		}

	}
	
	return Fuzzy(times - 1);
}


//卷积计算，输入任意矩阵input，从input[x][y]处开始计算卷积得到并返回 
inline uchar PixImage::Conv(Mat mt, int x, int y,int k, double kernel[3][3]) {
	uchar count = 0;
	uchar output[3][3] = { 0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			if (i + x >= mt.rows || j + y >= mt.cols)//对边界情况进行考虑
			{
				output[i][j] = mt.at<Vec3b>(abs(x-i), abs(y-j  ))[k] * kernel[i][j];//卷积计算
				count += output[i][j];
			}
			else {
				output[i][j] = mt.at<Vec3b>(i + x , j + y )[k] * kernel[i][j];//卷积计算
				count += output[i][j];
			}
		}
	}
	return count;
}



//边缘检测
void PixImage::EdgeDetection(string a)//字符串a为读取文件路径
{
	int kernel_x[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	int kernel_y[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	mt = imread(a, 0);
	//PrintPic();
	Mat img = mt;
	for (int i = 0; i < mt.rows; i++) //计算卷积
	{
		for (int j = 0; j < mt.cols; j++) {
			img.at<uchar>(i, j) =Conv1(mt, i, j, kernel_x, kernel_y);
		}
	}
	//PrintPic();
}

//边缘检测中的卷积计算
inline int PixImage::Conv1(Mat mt, int x, int y, int kernel_x[3][3], int kernel_y[3][3]) {
	int output_x[3][3] = { 0 };
	int output_y[3][3] = { 0 };
	int count_x = 0, count_y = 0;
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			if (i + x >= mt.rows || j + y >= mt.cols)//对边界情况进行考虑
			{
				output_x[i][j] =  mt.at<uchar>(abs(x - i), abs(y - j)) * kernel_x[j][i];//卷积计算
				count_x += output_x[i][j];
				output_y[i][j] =  mt.at<uchar>(abs(x - i), abs(y - j)) * kernel_y[j][i];
				count_y += output_y[i][j];
			}
			else {
				output_x[i][j] = mt.at<uchar>(x + i, y + j) * kernel_x[j][i];//卷积计算
				count_x += output_x[i][j];
				output_y[i][j] = mt.at<uchar>(x + i, y + j) * kernel_y[j][i];
				count_y += output_y[i][j];
			}
		}
	}
	count = abs(count_x) + abs(count_y);
	if (count > 255)count = 255;//防止结果超过0-255
	else if (count < 0)count = 0;
	return count;
}


//创建tif文件
void PixImage::CreatTiff(string a)
{
	imwrite(a, mt);//字符串a为写入文件的路径
}


//输出图片
void PixImage::PrintPic()
{
	namedWindow("test");
	imshow("test", mt);
	waitKey(100);
}


//得到长度
int PixImage::getLength()
{
	return mt.cols+1;//从0开始，实际长度比cols值大1
}

//得到宽度
int PixImage::getWidth()
{
	return mt.rows+1;//从0开始，实际宽度比rows值大1
}
//修改长宽的调用函数
void PixImage::change()
{
	cout << "图片长度为" << getLength() << ",图片宽度为" << getWidth();
	cout << ",请不要超过这个范围" << endl;
	cout << "请输入你需要修改的长和宽的值" << endl;
	int num1, num2;
	cin >> num1 >> num2;
	Change(num1, num2);
	cout << "图片长度为" << mt.cols << ",图片宽度为" << mt.rows;
}
//修改图像长宽
void PixImage::Change(int Len, int Wid)
{
	mt.cols = Len;
	mt.rows = Wid;
}