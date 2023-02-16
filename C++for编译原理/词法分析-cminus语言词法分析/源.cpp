#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>
#include<fstream>
#define sfName "test.txt"
#define tfName "output.txt"
typedef int sInt;
using namespace std;

FILE *source;
FILE *target;
int trans[3][3] = { 0,1,2,1,1,3 };


long beginp[5];   //��¼�ļ�ָ��Ŀ�ʼλ�ã�Ϊ�������
long endp[5];    //��¼�ļ�ָ��Ľ���λ��
char idStr[80] = "";   //�����ʶ���м�ֵ
int state[5] = { 0 }; //��ͬ�Ǻ����͵�״̬
char unaryOP[16] = { '+','-','*','/','<','>','=',';',',','(',')','[',']','{','}','!' }; //����һԪ�����
const char* p[32] = { 
	"auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "f1r", "goto", "if", "int", "long",
	"register", "return", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned", "void",
	"volatile", "while" 
};  //ϵͳ������
const char* strToken[7] = { "ID","NUM","OP","FUCN","RESW","ERROR","COM" };
typedef enum { ID, NUM, OP, FUCN, RESW, ERROR, COM }tokenType; //�Ǻ�����

void clearState()
{
	memset(state, 0, sizeof(state));
	memset(idStr, '\0', sizeof(idStr));
	memset(beginp, 0, sizeof(beginp));
	memset(endp, 0, sizeof(endp));
}

void strPrintf(long begin, long end, tokenType t)
{
	bool isComment = false;
	int k;
	char s[200] = "";
	long len = end - begin;
	//printf("%d %d\n",begin,end);
	fseek(source, -len, 1);//�ļ�ָ�����
	for (int i = 0; i < len; i++)
	{
		s[i] = fgetc(source);
	}
	//fseek(source,len,1); //�ļ�ָ���λ
	switch (t)
	{
	case ID:
		k = 0; break;
	case NUM:
		k = 1; break;
	case OP:
		k = 2; break;
	case FUCN:
		k = 3; break;
	case RESW:
		k = 4; break;
	case ERROR:
		k = 5; break;
	case COM:
		k = 6;
		isComment = true; break;
	default:cout << "��������\n";
	}
	//printf("%s\n",s);
	if (isComment)
	{
		fprintf(target, "%s\n", s);
		printf("%s\n", s);
	}

	else
	{
		fprintf(target, "<%s,%s>\n", strToken[k], s);
		printf("<%s,%s>\n", strToken[k], s);
	}
}

void unaryPrintf(char s, tokenType t)
{
	int k;
	switch (t)
	{
	case ID:
		k = 0; break;
	case NUM:
		k = 1; break;
	case OP:
		k = 2; break;
	case FUCN:
		k = 3; break;
	case RESW:
		k = 4; break;
	case ERROR:
		k = 5; break;
	case COM:
		k = 6; break;
	default:cout << "��������\n";
	}
	//cout<<strToken[k]<<endl;
	fprintf(target, "<%s,%c>\n", strToken[k], s);
	printf("<%s,%c>\n", strToken[k], s);
}

bool isOperator(char ch)
{
	for (int i = 0; i < 16; i++)
	{
		if (ch == unaryOP[i])
			return true;
	}
	return false;
}

bool isLiter(char ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_')
	{
		return true;
	}
	else
		return false;
}
void op_comment(char ch, int i)//�ж�ע������
{
	bool isexit = false; //������ע��ʱ��������ѭ��
						 //tokenType t=COM;
	while (!feof(source))
	{
		switch (state[i])
		{
		case 0:
			if (ch == '/')//����˺�������ʼ�ĵ�һ�����Ŷ���'/'
			{
				state[i] = 1;
				beginp[i] = ftell(source) - 1;//�õ���ǰ�ļ�ָ���ǰһλ��
			}
			break;
		case 1:
			if (ch == '*')
			{
				state[i] = 2;
			}
			else
			{
				isexit = true; //˵������ע�ͣ������˳�
				unaryPrintf('/', OP);//��һ������
				fseek(source, -1L, 1); //����һ���ֽڣ���Ϊ����case0������ռ���һλ
			}
			break;
		case 2:
			if (ch == '*')
			{
				state[i] = 3;
			}
			else
			{
				state[i] = 2;//������ע������
			}
			break;
		case 3:
			if (ch == '/')
			{
				state[i] = 4;
				endp[i] = ftell(source);
				strPrintf(beginp[i], endp[i], COM);
				isexit = true;                               //back
			}
			else state[i] = 2;
			break;
		}
		if (isexit) return;//back;
		ch = fgetc(source);
	}
}

void number(char ch, int i)//DFA-NUM
{
	
	beginp[i] = ftell(source) - 1;

	int end = 0;//��ʼΪ��̬
	int flag;
	while (!feof(source))
	{
		if (ch >= '0' && ch <= '9')
		{
			flag = 0;
		}
		else if(isLiter(ch)){
			flag = 1;
		}
		else {
			flag = 2;
		}
		end = trans[end][flag];
		endp[i] = ftell(source);
		if(end == 2){//�޷�����̬
			fseek(source, -1L, 1); //����,��������һ���ַ�
			strPrintf(beginp[i], endp[i], NUM);
			return;
		}
		else if (end == 3) {
			fseek(source, -1L, 1); //����,��������һ���ַ�
			strPrintf(beginp[i], endp[i], ERROR);
			return;
		}
		ch = fgetc(source);
	}
}

void op_operator(char ch, int i)
{
	bool isReturn = false;
	while (!feof(source))
	{
		if (ch == '+' || ch == '-' || ch == '*' || ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
		{
			state[i] = 1;
			unaryPrintf(ch, OP);
			isReturn = true;
		}
		else
		{
			switch (state[i])//���·��Ŵ��ڶ�Ԫ���
			{
			case 0:
				beginp[i] = ftell(source) - 1;
				switch (ch)
				{
				case '<':
					state[i] = 2;
					break;
				case '>':
					state[i] = 4;
					break;
				case '=':
					state[i] = 6;
					break;
				case '!':
					state[i] = 8;
					break;
				default:cout << "data error!\n";
				}
				break;
			case 2:
				if (ch == '=')
				{
					state[i] = 3;
					endp[i] = ftell(source);
					strPrintf(beginp[i], endp[i], OP);
					isReturn = true;
				}
				else
				{
					//����һԪ������
					state[i] = 2;
					fseek(source, -1L, 1);//����һ���ַ�
					unaryPrintf('<', OP);
					isReturn = true;
				}
				break;
			case 4:
				if (ch == '=')
				{
					state[i] = 5;
					endp[i] = ftell(source);
					strPrintf(beginp[i], endp[i], OP);
					isReturn = true;
				}
				else
				{
					//����һԪ������
					state[i] = 4;
					fseek(source, -1L, 1);//����һ���ַ�
					unaryPrintf('>', OP);
					isReturn = true;
				}
				break;
			case 6:
				if (ch == '=')
				{
					state[i] = 7;
					endp[i] = ftell(source);
					strPrintf(beginp[i], endp[i], OP);
					isReturn = true;
				}
				else
				{
					//����һԪ������
					state[i] = 6;
					fseek(source, -1L, 1);//����һ���ַ�
					unaryPrintf('=', OP);
					isReturn = true;
				}
				break;
			case 8:
				if (ch == '=')
				{
					state[i] = 9;
					endp[i] = ftell(source);
					strPrintf(beginp[i], endp[i], OP);
					isReturn = true;
				}
				else
				{
					//����һԪ������
					state[i] = 8;
					fseek(source, -1L, 1);//����һ���ַ�
					unaryPrintf('!', OP);
					isReturn = true;
				}
				break;
			default:cout << "data error!\n";
			}
		}
		if (isReturn) return;
		ch = fgetc(source);
	}
}


bool isResw(char* s)
{
	for (int i = 0; i < 32; i++)
	{
		if (strcmp(s, p[i]) == 0)
			return true;
	}
	return false;
}

void identifier(char ch, int i)
{
	
	beginp[i] = ftell(source);
	int end = 0;//��ʼ̬Ϊ��̬
	int flag;
	long len = 0;

	while (!feof(source))
	{
		if (isLiter(ch))
		{
			flag = 0;
			endp[i] = ftell(source);
		}
		else if (ch >= '0' && ch <= '9') {
			flag = 1;
			endp[i] = ftell(source);
		}
		else {
			flag = 2;
			endp[i] = ftell(source);
		}
		end = trans[end][flag];
		if (end == 2) {//�޷�����̬����һ���Ϸ�����ĸ��ɵĴ�
			long enter = 1;
			if (ch == '\n') enter = 2;
			fseek(source, -enter, 1);//����һ�����������ַ�
			len = endp[i] - beginp[i];
			/*if (ch == '\n') 
				fseek(source, -2, 1);*/
			fseek(source, -len, 1); //����,��������һ���ַ�
			for (int j = 0; j < len; j++)
			{
				idStr[j] = fgetc(source);

			}
			if (isResw(idStr)) //����Ǳ����֣��ͱ����˳�
			{
				strPrintf(beginp[i], endp[i], RESW);
				return;
			}
			if (ch == '(')
			{
				strPrintf(beginp[i], endp[i], FUCN);
				return;
			}
			else
			{
				strPrintf(beginp[i], endp[i], ID);
				return;
			}
		}
		else if (end == 3) {
			fseek(source, -1L, 1); //����,��������һ���ַ�
			strPrintf(beginp[i], endp[i], ERROR);
			return;
		}
		ch = fgetc(source);
	}
}

void startScanner()
{
	char ch = fgetc(source);
	while (!feof(source))
	{
		if (ch == ' ' || ch == '\n' || ch == '\t')
		{
			;//����ַ�Ϊ���л��߿ո�ֱ������
		}
		else if (ch == '/')
		{
			op_comment(ch, 0);//����ע��
			clearState(); //���״̬��Ϣ
		}
		else if (ch >= '0'&&ch <= '9')
		{
			number(ch, 1); //��������
			clearState();
		}
		else if (isOperator(ch))
		{
			op_operator(ch, 2); //������������ҵ�
			clearState();
		}
		else if (isLiter(ch))
		{
			identifier(ch, 3); //�����־��
			clearState();
		}
		else
		{
			unaryPrintf(ch, ERROR);
		}
		ch = fgetc(source);
	}
}

int main()
{
	if ((source = fopen(sfName, "r")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}
	if ((target = fopen(tfName, "w")) == NULL)
	{
		fprintf(stderr, "�ļ�д��ʧ�ܣ�\n");
		exit(0);
	}
	startScanner();//��ʼɨ���ļ� entrance
	fclose(source);
	fclose(target);
	cout << "д��ɹ�" << endl;
	system("pause");
	return 0;
}