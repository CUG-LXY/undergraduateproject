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


long beginp[5];   //记录文件指针的开始位置，为了做输出
long endp[5];    //记录文件指针的结束位置
char idStr[80] = "";   //保存标识符中间值
int state[5] = { 0 }; //不同记号类型的状态
char unaryOP[16] = { '+','-','*','/','<','>','=',';',',','(',')','[',']','{','}','!' }; //保存一元运算符
const char* p[32] = { 
	"auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "f1r", "goto", "if", "int", "long",
	"register", "return", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned", "void",
	"volatile", "while" 
};  //系统保留字
const char* strToken[7] = { "ID","NUM","OP","FUCN","RESW","ERROR","COM" };
typedef enum { ID, NUM, OP, FUCN, RESW, ERROR, COM }tokenType; //记号类型

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
	fseek(source, -len, 1);//文件指针回退
	for (int i = 0; i < len; i++)
	{
		s[i] = fgetc(source);
	}
	//fseek(source,len,1); //文件指针归位
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
	default:cout << "输入有误！\n";
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
	default:cout << "输入有误！\n";
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
void op_comment(char ch, int i)//判断注释内容
{
	bool isexit = false; //当不是注释时用于跳出循环
						 //tokenType t=COM;
	while (!feof(source))
	{
		switch (state[i])
		{
		case 0:
			if (ch == '/')//进入此函数，开始的第一个符号都是'/'
			{
				state[i] = 1;
				beginp[i] = ftell(source) - 1;//得到当前文件指针的前一位置
			}
			break;
		case 1:
			if (ch == '*')
			{
				state[i] = 2;
			}
			else
			{
				isexit = true; //说明不是注释，请求退出
				unaryPrintf('/', OP);//是一个除号
				fseek(source, -1L, 1); //回退一个字节，因为经过case0后向后收集了一位
			}
			break;
		case 2:
			if (ch == '*')
			{
				state[i] = 3;
			}
			else
			{
				state[i] = 2;//跳过被注释内容
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

	int end = 0;//初始为终态
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
		if(end == 2){//无法到终态
			fseek(source, -1L, 1); //回退,读到了下一个字符
			strPrintf(beginp[i], endp[i], NUM);
			return;
		}
		else if (end == 3) {
			fseek(source, -1L, 1); //回退,读到了下一个字符
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
			switch (state[i])//以下符号存在二元情况
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
					//属于一元操作符
					state[i] = 2;
					fseek(source, -1L, 1);//回退一个字符
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
					//属于一元操作符
					state[i] = 4;
					fseek(source, -1L, 1);//回退一个字符
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
					//属于一元操作符
					state[i] = 6;
					fseek(source, -1L, 1);//回退一个字符
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
					//属于一元操作符
					state[i] = 8;
					fseek(source, -1L, 1);//回退一个字符
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
	int end = 0;//初始态为终态
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
		if (end == 2) {//无法到终态但是一个合法的字母组成的串
			long enter = 1;
			if (ch == '\n') enter = 2;
			fseek(source, -enter, 1);//回退一个或是两个字符
			len = endp[i] - beginp[i];
			/*if (ch == '\n') 
				fseek(source, -2, 1);*/
			fseek(source, -len, 1); //回退,读到了下一个字符
			for (int j = 0; j < len; j++)
			{
				idStr[j] = fgetc(source);

			}
			if (isResw(idStr)) //如果是保留字，就保存退出
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
			fseek(source, -1L, 1); //回退,读到了下一个字符
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
			;//如果字符为换行或者空格，直接跳过
		}
		else if (ch == '/')
		{
			op_comment(ch, 0);//处理注释
			clearState(); //清楚状态信息
		}
		else if (ch >= '0'&&ch <= '9')
		{
			number(ch, 1); //处理数字
			clearState();
		}
		else if (isOperator(ch))
		{
			op_operator(ch, 2); //处理操作符，我的
			clearState();
		}
		else if (isLiter(ch))
		{
			identifier(ch, 3); //处理标志符
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
		printf("文件打开失败！\n");
		exit(0);
	}
	if ((target = fopen(tfName, "w")) == NULL)
	{
		fprintf(stderr, "文件写入失败！\n");
		exit(0);
	}
	startScanner();//开始扫描文件 entrance
	fclose(source);
	fclose(target);
	cout << "写入成功" << endl;
	system("pause");
	return 0;
}