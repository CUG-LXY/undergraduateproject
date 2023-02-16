#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <iomanip>
#include<map>
#include<set>

using namespace std;
/*全局变量*/
string V[100][2]; //存储拆分后的文法
int vi = 0; //存储拆分后有多少行
int t = 0;

map<string, int>  letters;      //用来存放终结字符,顺便标码
int num_letters = 0;    //记录有多少字符
set<string>  c_letters;   //存放终结符
set<string>  uc_letters;   //存放非终结符
string FIRSTVT[20][2]; //存储firstvt集
string LASTVT[20][2]; //存储lastvt集
string str; //存储输入文法

/*函数*/
int matirc[20][20];    //简单优先关系表
void show_matric();		//显示优先矩阵
void fprint_matric(string file_path);	//打印优先矩阵
void R_equals();        //寻找=关系          
void R_less();			//寻找<关系
void R_more();			//寻找>关系
void R_esle();				//对#关系进行处理

void split(string a);		//拆分文法
void read_file(string file_path);//按行读取文件
int find_index(char a); //寻找字符a在firstvt或者lastvt中的位置
void get_start(); //获取非终结符
void print_firstvt(string t, string a); //打印非终极符为t的firstvt
void print_lastvt(string t, string a); //打印非终结符为t的lastvt
void get_lastvt(); //获取所有文法的lastvt
void get_firstvt(); //获取所有文法的firstvt
string get_cur_lastvt(char c, int a); //获取当前字符的lastvt，并放入序号为a的lastvt中
string get_cur_firstvt(char c, int a); //获取当前字符的firstvt，并放入序号为a的firstvt中
void add_lastvt(char c, int a); //判断字符串c是否在序号为a的lastvt中，没有则加入
void add_firstvt(string b, int a); //判断字符串b是否在序号为a的firstvt中，没有则加入


int main(int argv, char* arg[])
{
	cout.setf(std::ios::left);
	read_file("wenfa.txt");
	cout << "拆分后文法:" << endl;
	for (int i = 0; i < vi; ++i)
	{
		cout << V[i][0] << "->" << V[i][1] << endl;
	}

	/*将各字符放入容器中*/
	for (int i = 0; i < vi; i++) {
		string::iterator iter = V[i][0].begin();
		string t;
		t.push_back(*iter);
		c_letters.insert(t);
		for (int j = 0, lenth = 0; j < 2; j++) {
			;
			for (auto c : V[i][j]) {		 //遍历每个string，取出char，放入letter集合中
				string tem;
				tem.push_back(c);
				//cout << tem << endl;
				if (letters.insert(pair<string, int>(tem, num_letters)).second == true) {
					num_letters++;
				}

			}
		}
	}

	for (int i = 0; i < 20; i++) {			//初始化优先表
		for (int j = 0; j < 20; j++) {
			matirc[i][j] = -1;
		}
	}

	cout << "非终结符:" << endl;
	get_start();
	for (int j = 0; j < t; ++j)
	{
		cout << FIRSTVT[j][0] << endl;
	}
	cout << "FIRSTVT:" << endl;
	get_firstvt();
	for (int k = 0; k < t; ++k)
	{
		print_firstvt(FIRSTVT[k][0], FIRSTVT[k][1]);
	}
	cout << "LASTVT:" << endl;
	get_lastvt();
	for (int k = 0; k < t; ++k)
	{
		print_lastvt(LASTVT[k][0], LASTVT[k][1]);
	}
	//cout << FIRSTVT[1][1] << endl;
	R_equals();
	R_less();
	R_more();
	R_esle();
	show_matric();
	fprint_matric("output.txt");
	return 0;
}

void show_matric() {
	cout << " \t";
	for (int i = 0; i < num_letters; i++) {														//先排列横轴
		for (map<string, int>::iterator it = letters.begin(); it != letters.end(); it++) {
			if (it->second == i) {
				cout << it->first << "\t";
			}
		}
	}
	cout << endl;
	cout << endl;
	for (int j = 0; j < num_letters; j++) {								//数轴排列
		for (map<string, int>::iterator it = letters.begin(); it != letters.end(); it++) {
			if (it->second == j) {
				cout << it->first << "\t";
				break;
			}
		}
		for (int k = 0; k < num_letters; k++) {
			cout << matirc[j][k] << "\t";
		}
		cout << endl;
		cout << endl;
	}
}

void fprint_matric(string file_path) {
	fstream f(file_path);;
	string letter;
	for (int i = 0; i < num_letters; i++) {														//先排列横轴
		for (map<string, int>::iterator it = letters.begin(); it != letters.end(); it++) {
			if (it->second == i) {
				letter += it->first;
			}
		}
	}
	f << letter << endl;
	for (int j = 0; j < num_letters; j++) {								//数轴排列
		for (int k = 0; k < num_letters; k++) {
			//cout << matirc[j][k] << "\t";
			f << matirc[j][k] << "\t";
		}
		f << endl;
	}

}

void R_equals() {						//此函数首先寻找平关系，在矩阵中记为0
	for (int i = 0; i < vi; i++) {
		string before, later;
		for (string::iterator iter = V[i][1].begin(); iter != V[i][1].end(); iter++) {		//每相邻两位取等于
			if (iter == V[i][1].begin()) {
				before = *iter;
				continue;
			}
			later = *iter;
			matirc[letters[before]][letters[later]] = 0;           //标记为0
			before = later;
		}
	}
}

void R_less() {
	for (int i = 0; i < vi; i++) {
		string before, later;
		for (string::iterator iter = V[i][1].begin(); iter != V[i][1].end(); iter++) {		//取相邻两位
			if (iter == V[i][1].begin()) {
				before = *iter;
				continue;
			}
			later = *iter;
			//cout << "before=" << before << "\t" << "later=" << later << endl;
			if (c_letters.find(before) == c_letters.end() && c_letters.find(later) != c_letters.end()) {  //形如A->(B, 前者是终结符，后者为非终结符
				//cout<<"能找到小于关系"<<endl;
				for (int i = 0; i < t; i++) {				//定位非终结符的坐标
					if (later == FIRSTVT[i][0]) {			//定位成功
						for (string::iterator it = FIRSTVT[i][1].begin(); it != FIRSTVT[i][1].end(); it++) {				//添加终结符与所有非终结符的FIRST集的所有小于关系
							string tem;
							tem.push_back(*it);
							matirc[letters[before]][letters[tem]] = 1;
						}
					}
				}

			}
	
			//matirc[letters[before]][letters[later]] = 1;       
			before = later;
		}
	}
	cout << endl;
}

void R_more() {
	for (int i = 0; i < vi; i++) {
		string before, later;
		for (string::iterator iter = V[i][1].begin(); iter != V[i][1].end(); iter++) {		//取相邻两位
			if (iter == V[i][1].begin()) {
				before = *iter;
				continue;
			}
			later = *iter;
			//cout << "before=" << before << "\t" << "later=" << later << endl;
			if (c_letters.find(before) != c_letters.end() && c_letters.find(later) == c_letters.end()) {  //形如A->Aa, 前者是非终结符，后者为非终结符
				//cout << "能找到大于关系" << endl;
				for (int i = 0; i < t; i++) {				//定位非终结符的坐标
					if (before == LASTVT[i][0]) {			//定位成功
						for (string::iterator it = LASTVT[i][1].begin(); it != LASTVT[i][1].end(); it++) {				//添加终结符与所有非终结符的FIRST集的所有小于关系
							string tem;
							tem.push_back(*it);
							matirc[letters[tem]][letters[later]] = 2;
						}
					}
				}

			}

			//matirc[letters[before]][letters[later]] = 1;           //标记为-1
			before = later;
		}
	}
}

void R_esle() {
	string s;
	s.push_back('S');
	string s2;
	s2.push_back('#');
	/*#与相邻关系处理*/
	for (int i = 0; i < num_letters; i++) {
		/*if (matirc[letters[s2]][i] != -1) {				//横向处理
			matirc[letters[s2]][i] = -1;
		}*/
		matirc[letters[s2]][i] = 1;						//#比所有符号小
		matirc[i][letters[s2]] = 2;						//所有符号比#大
		/*if(matirc[i][letters[s2]]!=2){				//纵向处理
			matirc[i][letters[s2]] = 1;
		}*/
	}
	/*对S与#的关系进行初始*/;
	matirc[letters[s]][letters[s2]] = 0;
	matirc[letters[s2]][letters[s]] = 0;
	/*对#与#进行初始*/
	matirc[letters[s2]][letters[s2]] = 0;
	
}

void split(string a) // 拆分文法，使其不含有｜
{
	for (int i = 3; i < a.length(); ++i)
	{
		V[vi][0] = a[0];
		while (a[i] != '|' && i < a.length())
		{
			V[vi][1] += a[i];
			i++;
		}
		vi++;
	}
}

void read_file(string file_path) //按行读取文件
{
	fstream f(file_path);
	vector<string> words;
	string line;
	while (getline(f, line))
	{
		words.push_back(line);
	}
	cout << "输入文法:" << endl;
	for (int i = 0; i < words.size(); i++)
	{
		cout << words[i] << endl;
		split(words[i]);
	}
}

int find_index(char a) //寻找字符a在firstvt或者lastvt中的位置
{
	for (int i = 0; i < t; ++i)
	{
		if (FIRSTVT[i][0][0] == a)
		{
			return i;
		}
	}
	return -1;
}

void get_start() //获取非终结符
{
	for (int i = 0; i < vi; ++i)
	{
		bool flag = true;
		for (int j = 0; j < t; ++j)
		{
			if (FIRSTVT[j][0] == V[i][0])
			{
				flag = false;
			}
		}
		if (flag)
		{
			FIRSTVT[t][0] = V[i][0];
			LASTVT[t][0] = V[i][0];
			t++;
		}
	}
}

void add_firstvt(string b, int a) //判断字符串b是否在序号为a的firstvt中，没有则加入
{
	for (int s = 0; s < b.length(); ++s)
	{
		bool flag = true;
		char c = b[s];
		if (c <= 'Z' && c >= 'A')
		{
			//FIRSTVT[a][1] += c;
			continue;
		}
		for (int i = 0; i < FIRSTVT[a][1].length(); ++i)
		{
			if (c == FIRSTVT[a][1][i])
			{
				flag = false;
			}
		}
		if (flag)
		{
			FIRSTVT[a][1] += c;
		}
	}
}

void add_firstvt(char c, int a) //判断字符c是否在序号为a的firstvt中，没有则加入
{
	bool flag = true;
	for (int i = 0; i < FIRSTVT[a][1].length(); ++i)
	{
		if (c <= 'Z' && c >= 'A')
		{
			//FIRSTVT[a][1] += c;
			continue;
		}
		if (c == FIRSTVT[a][1][i])
		{
			flag = false;
		}
	}
	if (flag)
	{
		FIRSTVT[a][1] += c;
	}
}

void add_lastvt(string b, int a) //判断字符串b是否在序号为a的lastvt中，没有则加入
{
	for (int s = 0; s < b.length(); ++s)
	{
		bool flag = true;
		char c = b[s];
		if (c <= 'Z' && c >= 'A')
		{
			//LASTVT[a][1] += c;
			continue;
		}
		for (int i = 0; i < LASTVT[a][1].length(); ++i)
		{
			if (c == LASTVT[a][1][i])
			{
				flag = false;
			}
		}
		if (flag)
		{
			LASTVT[a][1] += c;
		}
	}
}

void add_lastvt(char c, int a) //判断字符串c是否在序号为a的lastvt中，没有则加入
{
	bool flag = true;
	for (int i = 0; i < LASTVT[a][1].length(); ++i)
	{
		if (c <= 'Z' && c >= 'A')
		{
			continue;
		}
		if (c == LASTVT[a][1][i])
		{
			flag = false;
		}
	}
	if (flag)
	{
		LASTVT[a][1] += c;
	}
}

string get_cur_firstvt(char c, int a) //获取当前字符的firstvt，并放入序号为a的firstvt中
{
	string temp;
	for (int i = 0; i < vi; ++i)
	{
		if (c == V[i][0][0])
		{
			if (!(V[i][1][0] <= 'Z' && V[i][1][0] >= 'A'))
			{
				add_firstvt(V[i][1][0], a);
			}
			else
			{
				add_firstvt(V[i][1][0], a);
				if (c != V[i][1][0])
				{
					temp = get_cur_firstvt(V[i][1][0], find_index(V[i][1][0]));
					add_firstvt(temp, a);
				}
				if (V[i][1].length() > 2)
				{
					if (!(V[i][1][1] <= 'Z' && V[i][1][1] >= 'A'))
					{
						add_firstvt(V[i][1][1], a);
					}
				}
			}
		}
	}
	return FIRSTVT[a][1];
}

string get_cur_lastvt(char c, int a) //获取当前字符的lastvt，并放入序号为a的lastvt中
{
	string temp;
	for (int i = 0; i < vi; ++i)
	{
		int s = V[i][1].length();
		if (c == V[i][0][0])
		{
			if (!(V[i][1][s - 1] <= 'Z' && V[i][1][s - 1] >= 'A'))
			{
				add_lastvt(V[i][1][s - 1], a);
			}
			else
			{
				add_lastvt(V[i][1][s - 1], a);
				if (c != V[i][1][s - 1])
				{
					temp = get_cur_lastvt(V[i][1][s - 1], find_index(V[i][1][0]));
					add_lastvt(temp, a);
				}
				if (V[i][1].length() > 2)
				{
					if (!(V[i][1][s - 2] <= 'Z' && V[i][1][s - 2] >= 'A'))
					{
						add_lastvt(V[i][1][s - 2], a);
					}
				}
			}
		}
	}
	return LASTVT[a][1];
}


void get_firstvt() //获取所有文法的firstvt
{
	for (int i = 0; i < t; i++)
	{
		get_cur_firstvt(FIRSTVT[i][0][0], i);
	}
}

void get_lastvt() //获取所有文法的lastvt
{
	for (int i = 0; i < t; i++)
	{
		get_cur_lastvt(LASTVT[i][0][0], i);
	}
}

void print_firstvt(string t, string a) //打印非终极符为t的firstvt
{
	cout << "FIRSTVT(" << t << ") = {";
	for (int i = 0; i < a.length(); ++i)
	{
		if (i == a.length() - 1)
		{
			cout << "\"" << a[i] << "\"";
		}
		else
		{
			cout << "\"" << a[i] << "\"" << ", ";
		}
	}
	cout << "}" << endl;
}

void print_lastvt(string t, string a) //打印非终结符为t的lastvt
{
	cout << "LASTVT(" << t << ") = {";
	for (int i = 0; i < a.length(); ++i)
	{
		if (i == a.length() - 1)
		{
			cout << "\"" << a[i] << "\"";
		}
		else
		{
			cout << "\"" << a[i] << "\"" << ", ";
		}
	}
	cout << "}" << endl;
}

