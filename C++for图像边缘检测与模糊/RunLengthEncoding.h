#pragma once
#ifndef RUNLENGTHENCODING_H
#define RUNLENGTHENCODING_H
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include"PixImage.h"


struct runNode {
	uchar data;//����
	int num;//����
	runNode* lnode;//����
	runNode* rnode;//�ҽ��
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
	RunLengthEncoding();//����ɫͼ��ת�����γ̱���Ĺ��캯��
	RunLengthEncoding(PixImage& img); //�ô洢��ɫͼ�������Ϊ�����Ĺ��캯��
	~RunLengthEncoding();//��������
	void insert(int data, int num);//����һ���½��
	bool check();//�����������Ч��
	PixImage toPixImage();//���γ̱���ת����ͼ��
	bool ChangePixel();//���γ̱����и�������
	void visit();//����˫������
	void visit(runNode* curr, int& sum);//˫������ı�������������
private:
	runNode* first;//ͷ���
	int nodesum = 0;//�������
	int Length = 0;//ͼ�񳤶�
	int Width = 0;//ͼ����
	int channel;//ͼ��ͨ������1����Ҷ�ͼƬ��3�����ɫͼƬ
};

RunLengthEncoding::RunLengthEncoding()//����ɫͼ��ת�����γ̱���Ĺ��캯��
{
	channel = 3;
	//channel = 1;
	first = new runNode;
	first->rnode = first->lnode = first;
	int i, j, k;
	cv::Mat img = cv::imread("��ɫͼ��.tiff");
	int sum = 1;//���ڱ���������ͬ���ص�ĸ���
	uchar c;//��������Ҫ��������ص�����
	/*
	Length = img.cols;
	Width = img.rows;
	for (i = 0; i < img.rows; i++)//��ά����ת����
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
			else if ((img.at<uchar>(i, j) != img.at<uchar>(i, j + 1)) && ((j + 1) == img.cols - 1))//�������һ�����ص�����ǰ������ص㲻ͬ
			{
				insert(c, sum);
				c = img.at<uchar>(i, j);
				insert(c, 1);//�����һ�����ص����
				sum = 1;
			}
			else if ((img.at<uchar>(i, j) != img.at<uchar>(i, j + 1)) && ((j + 1) != img.cols - 1))
			{
				insert(c, sum);
				sum = 1;
			}
		}
		insert(0, 0);//��־һ�н���
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
		for (j = 0, k = 0; j < img.cols; j++)//һ�����ص������̺���ͨ��������ȡֵ
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

	for (i = 0; i < Width; i++)//��ά����ת����
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
			else if ((pic[i][j] != pic[i][j + 1]) && ((j + 1) == (Length - 1)))//�������һ�����ص�����ǰ������ص㲻ͬ
			{
				insert(c, sum);
				c = pic[i][j + 1];
				insert(c, 1);//�����һ�����ص����
				sum = 1;
			}
			else if ((pic[i][j] != pic[i][j + 1]) && ((j + 1) != (Length - 1)))
			{
				insert(c, sum);
				sum = 1;
			}
		}
		insert(0, 0);//��־һ�н���
	}
	delete[]pic;

}

RunLengthEncoding::RunLengthEncoding(PixImage& img)//�ô洢��ɫͼ�������Ϊ�����Ĺ��캯��
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
		for (j = 0, k = 0; j < img.mt.cols; j++)//һ�����ص������̺���ͨ��������ȡֵ
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
	int sum = 1;//���ڱ���������ͬ���ص�ĸ���
	uchar c;//��������Ҫ��������ص�����
	for (i = 0; i < Width; i++)//��ά����ת����
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
			else if ((pic[i][j] != pic[i][j + 1]) && ((j + 1) == (Length - 1)))//�������һ�����ص�����ǰ������ص㲻ͬ
			{
				insert(c, sum);
				c = pic[i][j + 1];
				insert(c, 1);//�����һ�����ص����
				sum = 1;
			}
			else if ((pic[i][j] != pic[i][j + 1]) && ((j + 1) != (Length - 1)))
			{
				insert(c, sum);
				sum = 1;
			}
		}
		insert(0, 0);//��־һ�н���
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
void RunLengthEncoding::insert(int data, int num)//����һ���½��

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
		else if (cols != Width)return false;//�Ƿ������ĳһ�е����ؿ����������ͬ
		else cols = 0;
		else if (cols1 == 0)cols1 = cols;
		else if (cols1 != cols)	return false;//�Ƿ������ÿһ�е������ص㲻ͬ
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
			return false;//�Ƿ����,��(4,6)������(4,7)
		}
	}
	return true;

}

PixImage RunLengthEncoding::toPixImage()
{
	int i, j, sum, k;
	runNode*curr;
	uchar** pic = new uchar*[Width];
	for (i = 0; i < Width; i++)//�洢ͼ��Ķ�ά����
	{
		pic[i] = new uchar[Length];
	}
	curr = first->rnode;
	sum = curr->num;

	i = 0;
	j = 0;
	for (i = 0; i < Width; i++)//����ת����
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
	while (curr->rnode != first&&i<Width&&j<Length)//����ת����
	{

		if (curr->num == 0)//һ�н���
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
	if (channel == 3)//��ͨ����ɫͼƬ
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
	else//�Ҷ�ͼƬ
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

bool RunLengthEncoding::ChangePixel()//���γ̱����и�������
{
	cout << "ͼƬ�������ص�Ϊ:";
	cout << Width << "*" << Length / channel << ",";
	cout << "Ϊ" << channel << "ͨ��" << "ͼƬ" << endl;

	int loc, loc1, loc2, sum = 0, n;
	int c, temp;
	char ch;
	while (1)
	{
		cout << "��Ҫ���ĵ����ص�λ��Ϊ(�� �У�:";
		cin >> loc1;
		cin >> loc2;
		loc = loc1 * Length + loc2;
		cout << "��������Ϊ:";
		cin >> c;
		runNode*curr, *bef;
		curr = first->rnode;
		bef = first;
		n = loc;
		while (n > 0)
		{
			if (sum == loc - 1)//Ҫ�޸ĵĵط��պ�Ϊ�˽���ʾ�����ص㷶Χ�ĵ�һ��
			{
				if (c == bef->data)//�޸ĺ��������ǰһ��������ͬ
				{
					bef->num++;
					curr->num--;
					break;
				}
				else //�޸ĺ���ǰһ�����ز�ͬ
				{
					curr->num--;
					runNode* newNode = new runNode(c, 1);//����һ���µ����ؽ��
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
				if (sum > loc)//Ҫ�޸ĵ����ص�Ϊ�����ؽ���м䲿��
				{
					int sum1 = loc - (sum - curr->num);
					int sum2 = sum - loc;
					curr->num = sum1;
					temp = curr->data;
					runNode* newNode1 = new runNode(c, 1);//����һ���µ����ؽ��
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
				else if (sum == loc)//Ҫ�޸ĵ����ص�Ϊ�����ؽ�����һ��
				{
					if (c == curr->rnode->data)//�޸ĺ���������һ������������ͬ
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
						runNode* newNode = new runNode(c, 1);//����һ���µ����ؽ��
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
		cout << "��������������y" << endl;
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
	if (sum == nodesum)cout << "�����γ̱���ɹ�" << endl;
	else cout << "�����γ̱���ʧ��" << endl;
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
