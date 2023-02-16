#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<string>
#include<fstream>
using namespace std;


char terms(char* ss)//进行规约
{
	string s[10][2];
	int k = 0;//k计数有多少个产生式
	ifstream wenfa("wenfa.txt");//读入文法
	//wenfa.open("wenfa.txt");
	if (!wenfa.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	while (!wenfa.eof())
	{
		string str;
		getline(wenfa, str);
		for (int i = 0; i<str.length(); i++)
		{
			if (str[i] == '-'&&str[i + 1] == '>')
			{
				s[k][0] += str.substr(0, i);//表达式左边和右边分开存储
				s[k][1] += str.substr(i + 2);
				break;
			}
		}
		k++;
	}
	//for (int i = 0; i < k; i++)
		//cout << s[i][0] << "\t" << s[i][1] << endl;
	string s1 = "";
	int i = 1;
	while (ss[i]!='\0')
	{
		s1 += ss[i];
		i++;
	}
	while (!s1.empty())
	{
		for (int i = 0; i < k; i++)
		{
			if (s1 == s[i][1])
			{
				return (char)s[i][0][0];//用表达式左边代替右边
			}
		}
		string::iterator it=s1.begin();     //指向string类的迭代器，可以理解为指针
		s1.erase(it);          //删除it处的一个字符  
	}
	return '\0';
}


int find(int a, int b)   //优先关系表
{
	ifstream output("output.txt");
	string str;
	getline(output, str);
	const int len = str.length();//读取矩阵的长宽，均为len
	//动态申请二维数组
	int **table;
	table = new int*[len];
	for (int i = 0; i < len; i++)
	{
		table[i] = new int[len];//构造len*len的矩阵
	}
	//将数字读入table中
	for (int i = 0; i < len; i++)
		for (int j = 0; j < len; j++) output >> table[i][j];
	output.close();
	//for (int i = 0; i < len; i++)
		//for (int j = 0; j < len; j++)
			//cout << table[i][j] << endl;
	return table[a - 1][b - 1];

}

//读取output.txt中的第一列得到优先关系矩阵的行和列的符号，该函数返回该符号的位置，进而可在find函数中查找优先关系
int relocat(char c) 
{
	ifstream output("output.txt");
	string str;
	getline(output, str);
	int len = str.length();
	int n,i=0;
	for (i; i < len; i++)
		if (c == str[i])
		{
			n = i + 1;//返回该符号的位置
			break;
		}
	if (i == len)n = 0;//没有找到该符号
	output.close();
	return n;
}




int judge(char* p, int k, char *curr)//判断表达式是否合法
{

	if (k == 1 && p[k] == '#' && (*curr == '+' || *curr == '*'))//运算符前面没有操作数
	{
		return 0;
	}
	if ((*curr == '+' || *curr == '*') && (*(curr + 1) == '+' || *(curr + 1) == '*'))//运算符符号相邻
	{
		return 0;
	}
	if (*curr == '#' && (*(curr - 1) == '+' || *(curr - 1) == '*'))//运算符后面没有操作数
	{
		return 0;
	}
	return 1;//合法返回1
}

int test()
{
	int  k;                   //栈顶
	char s[30] = { '\0' };      //分析栈
	char *ss;
	char in_c[50] = { '\0' };   //输入串
	char *curr;                //指向当前输入符号
	int  j;
	char q;
	int  flag;
	int  n;

	while (1)
	{
		printf("请输入您要归约的字符串,以‘#’结束：");
		scanf("%s", in_c);
		n = 1;          //记录步骤
		k = 1;

		s[k] = '#';
		s[k + 1] = '\0';    //初始化
		ss = s + 1;
		curr = in_c;


		printf("\n步骤\t栈内字符\t\t优先关系\t当前符号\t剩余输入串\t\t\t移进或归约\n");
		while (1)
		{
			if (judge(s, k, curr) == 0)
			{
				printf("\n出错！\n");
				break;
			}

			if (relocat(s[k]))
				j = k;
			else
				j = k - 1;
			flag = find(relocat(s[j]), relocat(*curr));
			if (flag == 2)  //如果s[j] > 当前输入字符
			{
				do
				{
					q = s[j];
					if (relocat(s[j - 1]))
						j--;
					else
						j = j - 2;
				} while (find(relocat(s[j]), relocat(q)) != 1);
				printf("(%d)\t%-24s>\t\t%c\t\t%-32s归约\n", n++, ss, *curr, curr + 1);
				k = j + 1;
				char g = terms(s);//进行规约，给g返回表达式左边
				if (g != '\0')
				{
					s[k] = g;//只要g不为空，就用左边代替右边，即规约
					s[k + 1] = '\0';
				}
				continue;
			}
			else if (flag == 1)//1小于，继续移进
			{
				printf("(%d)\t%-24s<\t\t%c\t\t", n++, ss, *curr);
				k++;
				s[k] = *curr;
				s[k + 1] = '\0';
				curr++;
				printf("%-32s移进\n", curr);
				continue;
			}
			else if (flag == 0)//0等于
			{
				if (s[j - 1] == '#')//结束
				{
					printf("(%d)\t%-24s=\t\t#\t\t\t\t\t\t接受\n", n, ss);//规约成功，接受该输入串
					printf("\n归约成功！\n");
					break;
				}
				else
				{
					printf("(%d)\t%-24s=\t\t%c\t\t", n++, ss, *curr);//等于则继续移进
					k++;
					s[k] = *curr;
					s[k + 1] = '\0';
					curr++;
					printf("%-32s移进\n", curr);
					continue;
				}
			}
			else//-1是空，即无关系，报错
			{
				printf("(%d)\t%-24s无\t\t%c\t\t%-32s\\\n", n++, ss, *curr, curr + 1);
				printf("\n错误！\n");
				break;
			}

		}

	}

	return 0;
}
int main()
{
	test();
	return 0;
}
