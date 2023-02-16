#pragma once
#ifndef RUNLENGTHENCODING_H
#define RUNLENGTHENCODING_H
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include"PixImage.h"


struct runNode {
	uchar data;//像素
	int num;//个数
	runNode* lnode;//左结点
	runNode* rnode;//右结点
	runNode(runNode*l = NULL, runNode*r = NULL)
	{
		lnode = l;
		rnode = r;
	}
	runNode(uchar d, int n, runNode*l = NULL, runNode*r = NULL)
	{
		data = d;
		num = n;
		lnode = l;
		rnode = r;
	}
};

class RunLengthEncoding {
public:
	RunLengthEncoding();//将黑色图像转换成游程编码的构造函数
	RunLengthEncoding(PixImage& img); //用存储彩色图像的类作为参数的构造函数
	~RunLengthEncoding();//析构函数
	void insert(int data, int num);//插入一个新结点
	bool check();//遍历链表检查高效性
	PixImage toPixImage();//将游程编码转换成图像
	bool ChangePixel();//在游程编码中更改像素
	void visit();//遍历双向链表
	void visit(runNode* curr, int& sum);//双向链表的遍历，迭代函数
private:
	runNode* first;//头结点
	int nodesum = 0;//结点总数
	int Length = 0;//图像长度
	int Width = 0;//图像宽度
	int channel;//图像通道数，1代表灰度图片，3代表彩色图片
};

RunLengthEncoding::RunLengthEncoding()//将黑色图像转换成游程编码的构造函数
{
	channel = 3;
	//channel = 1;
	first = new runNode;
	first->rnode = first->lnode = first;
	int i, j, k;
	cv::Mat img = cv::imread("黑色图像.tiff");
	int sum = 1;//用于保存连续相同像素点的个数
	uchar c;//用来保存要插入的像素点数字
	/*
	Length = img.cols;
	Width = img.rows;
	for (i = 0; i < img.rows; i++)//二维数组转链表
	{
		for (j = 0; j < img.cols - 1; j++)
		{
			c = img.at<uchar>(i, j);
			if (img.at<uchar>(i, j) == img.at<uchar>(i, j + 1) && (j + 1) == (img.cols - 1))
			{
				sum++;
			}
			else if (img.at<uchar>(i, j) == img.at<uchar>(i, j + 1) && (j + 1) != (img.cols - 1))
			{
				sum++;
				insert(c, sum);
				sum = 1;
			}
			else if ((img.at<uchar>(i, j) != img.at<uchar>(i, j + 1)) && ((j + 1) == img.cols - 1))//此行最后一个像素点与其前面的像素点不同
			{
				insert(c, sum);
				c = img.at<uchar>(i, j);
				insert(c, 1);//将最后一个像素点插入
				sum = 1;
			}
			else if ((img.at<uchar>(i, j) != img.at<uchar>(i, j + 1)) && ((j + 1) != img.cols - 1))
			{
				insert(c, sum);
				sum = 1;
			}
		}
		insert(0, 0);//标志一行结束
	}
	*/
	Length = 3 * img.cols;
	Width = img.rows;
	uchar**pic = new uchar*[Width];
	for (i = 0; i < Width; i++)
	{
		pic[i] = new uchar[Length];
	}
	for (i = 0; i < Width; i++)
	{
		for (j = 0, k = 0; j < img.cols; j++)//一个像素点有蓝绿红三通道，依次取值
		{
			pic[i][k++] = img.at<Vec3b>(i, j)[0];
			pic[i][k++] = img.at<Vec3b>(i, j)[1];
			pic[i][k++] = img.at<Vec3b>(i, j)[2];
		}
	}
	/*
	cv::Mat mt(Width, Length / 3, CV_8UC3);
	for (i = 0; i < Width; i++)
	{
		for (j = 0, k = 0; j < (Length / 3); j++)
		{
			mt.at<Vec3b>(i, j)[0] = pic[i][k++];
			mt.at<Vec3b>(i, j)[1] = pic[i][k++];
			mt.at<Vec3b>(i, j)[2] = pic[i][k++];
		}
	}

	PixImage img1(mt);
	img1.PrintPic();
	*/

	for (i = 0; i < Width; i++)//二维数组转链表
	{
		for (j = 0; j < Length - 1; j++)
		{
			c = pic[i][j];
			if ((pic[i][j] == pic[i][j + 1]) && ((j + 1) != (Length - 1)))
			{
				sum++;
			}
			else if ((pic[i][j] == pic[i][j + 1]) && ((j + 1) == (Length - 1)))
			{
				sum++;
				insert(c, sum);
				sum = 1;
			}
			else if ((pic[i][j] != pic[i][j + 1]) && ((j + 1) == (Length - 1)))//此行最后一个像素点与其前面的像素点不同
			{
				insert(c, sum);
				c = pic[i][j + 1];
				insert(c, 1);//将最后一个像素点插入
				sum = 1;
			}
			else if ((pic[i][j] != pic[i][j + 1]) && ((j + 1) != (Length - 1)))
			{
				insert(c, sum);
				sum = 1;
			}
		}
		insert(0, 0);//标志一行结束
	}
	delete[]pic;

}

RunLengthEncoding::RunLengthEncoding(PixImage& img)//用存储彩色图像的类作为参数的构造函数
{
	channel = 3;
	first = new runNode;
	first->rnode = first->lnode = first;
	Length = 3 * img.mt.cols;
	Width = img.mt.rows;
	int i, j, k;
	uchar**pic = new uchar*[Width];
	for (i = 0; i < Width; i++)
	{
		pic[i] = new uchar[Length];
	}
	for (i = 0; i < Width; i++)
	{
		for (j = 0, k = 0; j < img.mt.cols; j++)//一个像素点有蓝绿红三通道，依次取值
		{
			pic[i][k++] = img.mt.at<Vec3b>(i, j)[0];
			pic[i][k++] = img.mt.at<Vec3b>(i, j)[1];
			pic[i][k++] = img.mt.at<Vec3b>(i, j)[2];
		}
	}
	/*
	cv::Mat mt(Width, Length / 3, CV_8UC3);
	for (i = 0; i < Width; i++)
	{
		for (j = 0, k = 0; j < (Length / 3); j++)
		{
			mt.at<Vec3b>(i, j)[0] = pic[i][k++];
			mt.at<Vec3b>(i, j)[1] = pic[i][k++];
			mt.at<Vec3b>(i, j)[2] = pic[i][k++];
		}
	}

	PixImage img1(mt);
	img1.PrintPic();
	*/
	int sum = 1;//用于保存连续相同像素点的个数
	uchar c;//用来保存要插入的像素点数字
	for (i = 0; i < Width; i++)//二维数组转链表
	{
		for (j = 0; j < Length - 1; j++)
		{
			c = pic[i][j];
			if ((pic[i][j] == pic[i][j + 1]) && ((j + 1) != (Length - 1)))
			{
				sum++;
			}
			else if ((pic[i][j] == pic[i][j + 1]) && ((j + 1) == (Length - 1)))
			{
				sum++;
				insert(c, sum);
				sum = 1;
			}
			else if ((pic[i][j] != pic[i][j + 1]) && ((j + 1) == (Length - 1)))//此行最后一个像素点与其前面的像素点不同
			{
				insert(c, sum);
				c = pic[i][j + 1];
				insert(c, 1);//将最后一个像素点插入
				sum = 1;
			}
			else if ((pic[i][j] != pic[i][j + 1]) && ((j + 1) != (Length - 1)))
			{
				insert(c, sum);
				sum = 1;
			}
		}
		insert(0, 0);//标志一行结束
	}
	delete[]pic;
}

RunLengthEncoding::~RunLengthEncoding()
{
	runNode*del;
	while (first->rnode != first)
	{
		del = first->rnode;
		first->rnode = del->rnode;
		del->rnode->lnode = first;
		delete del;
	}
	nodesum = 0;
	Width = 0;
	Length = 0;
}
void RunLengthEncoding::insert(int data, int num)//插入一个新结点

{
	runNode*newnode = new runNode(data, num);
	newnode->lnode = first->lnode;
	first->lnode = newnode;
	newnode->lnode->rnode = newnode;
	newnode->rnode = first;
	nodesum++;
}

bool RunLengthEncoding::check()
{
	runNode*curr, *bef;
	curr = first->rnode;
	bef = first;
	//int cols = 1, cols1 = 0;

	while (curr->rnode != first)
	{
		/*
		if (curr->num != 0)cols+=curr->num;
		else if (cols != Width)return false;//非法情况，某一行的像素宽度与其他不同
		else cols = 0;
		else if (cols1 == 0)cols1 = cols;
		else if (cols1 != cols)	return false;//非法情况，每一行的总像素点不同
		*/
		curr = curr->rnode;
		bef = bef->rnode;

		if (curr->num == 0 && curr->rnode != first)
		{
			bef = curr->rnode;
			curr = bef->rnode;
		}
		if ((curr->data) == (bef->data))
		{
			return false;//非法情况,如(4,6)后又有(4,7)
		}
	}
	return true;

}

PixImage RunLengthEncoding::toPixImage()
{
	int i, j, sum, k;
	runNode*curr;
	uchar** pic = new uchar*[Width];
	for (i = 0; i < Width; i++)//存储图像的二维数组
	{
		pic[i] = new uchar[Length];
	}
	curr = first->rnode;
	sum = curr->num;

	i = 0;
	j = 0;
	for (i = 0; i < Width; i++)//链表转数组
	{
		for (j = 0; j < Length; j++)
		{
			while (sum == 0)
			{
				curr = curr->rnode;
				sum = curr->num;
			}
			pic[i][j] = curr->data;
			sum--;
		}
	}
	/*
	while (curr->rnode != first&&i<Width&&j<Length)//链表转数组
	{

		if (curr->num == 0)//一行结束
		{
			i++;
			j = 0;
		}
		else while (sum > 0)
			{
				pic[i][j++] = curr->data;
				sum--;
			}
		curr = curr->rnode;
		sum = curr->num;
	}
	*/
	if (channel == 3)//三通道彩色图片
	{
		cv::Mat mt(Width, Length / 3, CV_8UC3);
		for (i = 0; i < Width; i++)
		{
			for (j = 0, k = 0; j < (Length / 3); j++)
			{
				mt.at<Vec3b>(i, j)[0] = pic[i][k++];
				mt.at<Vec3b>(i, j)[1] = pic[i][k++];
				mt.at<Vec3b>(i, j)[2] = pic[i][k++];
			}
		}

		PixImage img(mt);
		delete[]pic;
		return img;
	}
	else//灰度图片
	{
		//cv::Mat mt(Width, Length, CV_8UC1, pic);
		cv::Mat mt(Width, Length, CV_8UC1);
		for (i = 0; i < Width; i++)
		{
			for (j = 0; j < Length; j++)
			{
				mt.at<uchar>(i, j) = pic[i][j];
			}
		}
		PixImage img(mt);
		delete[]pic;
		return img;
	}
}

bool RunLengthEncoding::ChangePixel()//在游程编码中更改像素
{
	cout << "图片的总像素点为:";
	cout << Width << "*" << Length / channel << ",";
	cout << "为" << channel << "通道" << "图片" << endl;

	int loc, loc1, loc2, sum = 0, n;
	int c, temp;
	char ch;
	while (1)
	{
		cout << "想要更改的像素点位置为(行 列）:";
		cin >> loc1;
		cin >> loc2;
		loc = loc1 * Length + loc2;
		cout << "更改像素为:";
		cin >> c;
		runNode*curr, *bef;
		curr = first->rnode;
		bef = first;
		n = loc;
		while (n > 0)
		{
			if (sum == loc - 1)//要修改的地方刚好为此结点表示的像素点范围的第一个
			{
				if (c == bef->data)//修改后的像素与前一个像素相同
				{
					bef->num++;
					curr->num--;
					break;
				}
				else //修改后与前一个像素不同
				{
					curr->num--;
					runNode* newNode = new runNode(c, 1);//插入一个新的像素结点
					bef->rnode = newNode;
					newNode->lnode = bef;
					curr->lnode = newNode;
					newNode->rnode = curr;
					nodesum++;
					break;
				}
			}
			else
			{
				sum += curr->num;
				if (sum > loc)//要修改的像素点为此像素结点中间部分
				{
					int sum1 = loc - (sum - curr->num);
					int sum2 = sum - loc;
					curr->num = sum1;
					temp = curr->data;
					runNode* newNode1 = new runNode(c, 1);//插入一个新的像素结点
					bef = curr;
					curr = curr->rnode;
					bef->rnode = newNode1;
					newNode1->lnode = bef;
					curr->lnode = newNode1;
					newNode1->rnode = curr;
					nodesum++;
					runNode* newNode2 = new runNode(temp, sum2);
					bef = bef->rnode;
					bef->rnode = newNode2;
					newNode2->lnode = bef;
					curr->lnode = newNode2;
					newNode2->rnode = curr;
					nodesum++;
					break;
				}
				else if (sum == loc)//要修改的像素点为此像素结点最后一个
				{
					if (c == curr->rnode->data)//修改后的像素与后一个结点的像素相同
					{
						curr->num--;
						curr->rnode->num++;
						break;
					}
					else
					{
						curr->num--;
						bef = curr;
						curr = curr->rnode;
						runNode* newNode = new runNode(c, 1);//插入一个新的像素结点
						bef->rnode = newNode;
						newNode->lnode = bef;
						curr->lnode = newNode;
						newNode->rnode = curr;
						nodesum++;
						break;
					}
				}

			}
			n -= curr->num;
			bef = curr;
			curr = curr->rnode;
		}
		cout << "继续更改请输入y" << endl;
		cin >> ch;
		if (ch != 'y')break;
	}
	if (check() == true)return true;
	else return false;
}

void RunLengthEncoding::visit()
{
	int sum = 0;
	//visit(first,sum);
	runNode*curr = first;
	while (curr->rnode != first)
	{
		sum++;
		curr = curr->rnode;
	}
	if (sum == nodesum)cout << "遍历游程编码成功" << endl;
	else cout << "遍历游程编码失败" << endl;
}
void RunLengthEncoding::visit(runNode*curr, int &sum)
{
	if (curr->rnode != first)
	{
		sum++;
		visit(curr->rnode, sum);
	}

}

#endif // !RUNLENGTHENCODING_H
