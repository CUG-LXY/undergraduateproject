#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<string>
#include<fstream>
using namespace std;


char terms(char* ss)//���й�Լ
{
	string s[10][2];
	int k = 0;//k�����ж��ٸ�����ʽ
	ifstream wenfa("wenfa.txt");//�����ķ�
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
				s[k][0] += str.substr(0, i);//���ʽ��ߺ��ұ߷ֿ��洢
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
				return (char)s[i][0][0];//�ñ��ʽ��ߴ����ұ�
			}
		}
		string::iterator it=s1.begin();     //ָ��string��ĵ��������������Ϊָ��
		s1.erase(it);          //ɾ��it����һ���ַ�  
	}
	return '\0';
}


int find(int a, int b)   //���ȹ�ϵ��
{
	ifstream output("output.txt");
	string str;
	getline(output, str);
	const int len = str.length();//��ȡ����ĳ�����Ϊlen
	//��̬�����ά����
	int **table;
	table = new int*[len];
	for (int i = 0; i < len; i++)
	{
		table[i] = new int[len];//����len*len�ľ���
	}
	//�����ֶ���table��
	for (int i = 0; i < len; i++)
		for (int j = 0; j < len; j++) output >> table[i][j];
	output.close();
	//for (int i = 0; i < len; i++)
		//for (int j = 0; j < len; j++)
			//cout << table[i][j] << endl;
	return table[a - 1][b - 1];

}

//��ȡoutput.txt�еĵ�һ�еõ����ȹ�ϵ������к��еķ��ţ��ú������ظ÷��ŵ�λ�ã���������find�����в������ȹ�ϵ
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
			n = i + 1;//���ظ÷��ŵ�λ��
			break;
		}
	if (i == len)n = 0;//û���ҵ��÷���
	output.close();
	return n;
}




int judge(char* p, int k, char *curr)//�жϱ��ʽ�Ƿ�Ϸ�
{

	if (k == 1 && p[k] == '#' && (*curr == '+' || *curr == '*'))//�����ǰ��û�в�����
	{
		return 0;
	}
	if ((*curr == '+' || *curr == '*') && (*(curr + 1) == '+' || *(curr + 1) == '*'))//�������������
	{
		return 0;
	}
	if (*curr == '#' && (*(curr - 1) == '+' || *(curr - 1) == '*'))//���������û�в�����
	{
		return 0;
	}
	return 1;//�Ϸ�����1
}

int test()
{
	int  k;                   //ջ��
	char s[30] = { '\0' };      //����ջ
	char *ss;
	char in_c[50] = { '\0' };   //���봮
	char *curr;                //ָ��ǰ�������
	int  j;
	char q;
	int  flag;
	int  n;

	while (1)
	{
		printf("��������Ҫ��Լ���ַ���,�ԡ�#��������");
		scanf("%s", in_c);
		n = 1;          //��¼����
		k = 1;

		s[k] = '#';
		s[k + 1] = '\0';    //��ʼ��
		ss = s + 1;
		curr = in_c;


		printf("\n����\tջ���ַ�\t\t���ȹ�ϵ\t��ǰ����\tʣ�����봮\t\t\t�ƽ����Լ\n");
		while (1)
		{
			if (judge(s, k, curr) == 0)
			{
				printf("\n����\n");
				break;
			}

			if (relocat(s[k]))
				j = k;
			else
				j = k - 1;
			flag = find(relocat(s[j]), relocat(*curr));
			if (flag == 2)  //���s[j] > ��ǰ�����ַ�
			{
				do
				{
					q = s[j];
					if (relocat(s[j - 1]))
						j--;
					else
						j = j - 2;
				} while (find(relocat(s[j]), relocat(q)) != 1);
				printf("(%d)\t%-24s>\t\t%c\t\t%-32s��Լ\n", n++, ss, *curr, curr + 1);
				k = j + 1;
				char g = terms(s);//���й�Լ����g���ر��ʽ���
				if (g != '\0')
				{
					s[k] = g;//ֻҪg��Ϊ�գ�������ߴ����ұߣ�����Լ
					s[k + 1] = '\0';
				}
				continue;
			}
			else if (flag == 1)//1С�ڣ������ƽ�
			{
				printf("(%d)\t%-24s<\t\t%c\t\t", n++, ss, *curr);
				k++;
				s[k] = *curr;
				s[k + 1] = '\0';
				curr++;
				printf("%-32s�ƽ�\n", curr);
				continue;
			}
			else if (flag == 0)//0����
			{
				if (s[j - 1] == '#')//����
				{
					printf("(%d)\t%-24s=\t\t#\t\t\t\t\t\t����\n", n, ss);//��Լ�ɹ������ܸ����봮
					printf("\n��Լ�ɹ���\n");
					break;
				}
				else
				{
					printf("(%d)\t%-24s=\t\t%c\t\t", n++, ss, *curr);//����������ƽ�
					k++;
					s[k] = *curr;
					s[k + 1] = '\0';
					curr++;
					printf("%-32s�ƽ�\n", curr);
					continue;
				}
			}
			else//-1�ǿգ����޹�ϵ������
			{
				printf("(%d)\t%-24s��\t\t%c\t\t%-32s\\\n", n++, ss, *curr, curr + 1);
				printf("\n����\n");
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
