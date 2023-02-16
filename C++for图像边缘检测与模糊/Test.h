#include <windows.h>
//#include"PixImage.h"
#include"RunLengthEncoding.h"
#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>



//正确性测试
//修改像素
void correct_modif()
{
	PixImage img;
	string a = "D:/30000/";
	string Modif = "D:/outModif/";
	int i = 1;
	string b = std::to_string(i);
	string c = ".tif";
	string tmp;
	for (int i = 0; i < 200; i++)
	{
		b = to_string(i + 1);
		tmp = a + b + c;
		img.Read(tmp);
		img.Modifypx(2, 3, 45, 67, 89);
		img.PrintPic();
		tmp = Modif + b + c;
		img.CreatTiff(tmp);
		b = "";
		tmp = "";
	}
}

//模糊
void correct_Fuzzy()
{
	PixImage img;
	string a = "D:/30000/";
	string Fuz = "D:/outFuzzy/";
	int i = 1;
	string b = std::to_string(i);
	string c = ".tif";
	string tmp;
	for (int i = 0; i < 200; i++)
	{
		b = to_string(i + 1);
		tmp = a + b + c;
		img.Read(tmp);
		img.Fuzzy(3);
		img.PrintPic();
		tmp = Fuz + b + c;
		img.CreatTiff(tmp);
		b = "";
		tmp = "";
	}
}
//边缘检测
void correct_Edge()
{
	PixImage img;
	string a = "D:/30000/";
	string Edge = "D:/outEdge/";
	int i = 1;
	string b = std::to_string(i);
	string c = ".tif";
	string tmp;
	for (int i = 0; i < 200; i++)
	{
		b = to_string(i + 1);
		tmp = a + b + c;
		img.Read(tmp);
		img.EdgeDetection(tmp);
		img.PrintPic();
		tmp = Edge + b + c;
		img.CreatTiff(tmp);
		b = "";
		tmp = "";
	}

}

//黑色图像转游程编码
void correct_change()
{
	for (int i = 0; i < 200; i++)
	{
		RunLengthEncoding run();
	}
}

//图像转游程编码
void correct_change1()
{
	PixImage img;
	string a = "D:/30000/";
	//string Edge = "D:/outEdge/";
	int i = 1;
	string b = std::to_string(i);
	string c = ".tif";
	string tmp;
	for (int i = 0; i < 200; i++)
	{
		b = to_string(i + 1);
		tmp = a + b + c;
		img.Read(tmp);
		RunLengthEncoding run(img);
		b = "";
		tmp = "";
	}
}
//游程编码转图像
void correct_toPixImage()
{
	PixImage img;
	string a = "D:/30000/";
	//string Edge = "D:/outEdge/";
	int i = 1;
	string b = std::to_string(i);
	string c = ".tif";
	string tmp;
	for (int i = 0; i < 200; i++)
	{
		b = to_string(i + 1);
		tmp = a + b + c;
		img.Read(tmp);
		RunLengthEncoding run(img);
		run.toPixImage();
		b = "";
		tmp = "";
	}
}


//运行游程编码时更改像素,注：请在代码中将输入值改为常量
void correct_ChangePixel()
{
	PixImage img;
	string a = "D:/30000/";
	//string Edge = "D:/outEdge/";
	int i = 1;
	string b = std::to_string(i);
	string c = ".tif";
	string tmp;
	for (int i = 0; i < 200; i++)
	{
		b = to_string(i + 1);
		tmp = a + b + c;
		img.Read(tmp);
		RunLengthEncoding run(img);
		run.ChangePixel();
		b = "";
		tmp = "";
	}
}

//遍历游程编码
void correct_visit()
{
	PixImage img;
	string a = "D:/30000/";
	//string Edge = "D:/outEdge/";
	int i = 1;
	string b = std::to_string(i);
	string c = ".tif";
	string tmp;
	for (int i = 0; i < 200; i++)
	{
		b = to_string(i + 1);
		tmp = a + b + c;
		img.Read(tmp);
		RunLengthEncoding run(img);
		run.visit();
		b = "";
		tmp = "";
	}
}


//高效性测试

//定义线程函数传入参数的结构体
typedef struct __THREAD_DATA
{
	int num;//num为图片路径中的整数，即文件家中的第几个图片
}THREAD_DATA;



//线程函数
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	THREAD_DATA* pThreadData = (THREAD_DATA*)lpParameter;
	/*PixImage img;
	string a = "D:/30000/";
	string Edge = "D:/outEdge/";
	string b = "1";
	string c = ".tif";
	int count = 0, num = pThreadData->num;
	while (count < 60)
	{
		b = to_string(num + count + 1);
		string tmp;
		tmp = a + b + c;
		img.Read(tmp);
		//img.Modifypx(3, 4, 56, 78, 90);
		img.Fuzzy(2);
		//img.PrintPic();
		//img.EdgeDetection(tmp);
		//tmp = Edge + b + c;
		//img.CreatTiff(tmp);
		//img.PrintPic();
		b = "";
		tmp = "";
		count++;
	}*/
	PixImage img;
	string a = "D:/300/";
	string Edge = "D:/outEdge/";
	string b = "1";
	string c = ".tif";
	int count = 0, num = pThreadData->num;
	while (count < 60)
	{
		b = to_string(num + count + 1);
		string tmp = a + b + c;
		img.Read(tmp);
		RunLengthEncoding run(img);
		img=run.toPixImage();
		tmp = Edge + b + c;
		img.CreatTiff(tmp);
		b = "";
		tmp = "";
	}
	return 0L;
}
void Quick_test()
{
	LARGE_INTEGER freq;
	LARGE_INTEGER startCount, endCount;
	double elapsed;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&startCount);// 统计运行总时间


	//初始化线程数据
	THREAD_DATA threadData1, threadData2, threadData3, threadData4;
	threadData1.num = 60;//根据测试次数进行更改
	threadData2.num = 120;
	threadData3.num = 180;
	threadData4.num = 240;
	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc, &threadData1, 0, NULL);//子线程
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc, &threadData2, 0, NULL);
	HANDLE hThread3 = CreateThread(NULL, 0, ThreadProc, &threadData3, 0, NULL);
	HANDLE hThread4 = CreateThread(NULL, 0, ThreadProc, &threadData4, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	CloseHandle(hThread3);
	CloseHandle(hThread4);//一个主线程加四个子线程，共五个线程



	//主线程
	for (int i = 0; i < 60; i++)
	{
		PixImage img;
		string a = "D:/30000/";
		string Edge = "D:/outEdge/";
		string b = "1";
		string c = ".tif";
		b = to_string(i + 1);
		string tmp;
		tmp = a + b + c;
		img.Read(tmp);
		RunLengthEncoding run(img);
		img = run.toPixImage();
		tmp = Edge + b + c;
		img.CreatTiff(tmp);
		//img.Modifypx(3, 4, 56, 78, 90);//想测什么功能就把别的功能注释掉
		//img.Fuzzy(2);
		//img.PrintPic();
		//img.EdgeDetection(tmp);
		//tmp = Edge + b + c;
		//img.CreatTiff(tmp);
		//img.PrintPic();
		b = "";
		tmp = "";


	}
	// 停止计时器
	QueryPerformanceCounter(&endCount);

	// 返回计时器经过时间(单位：毫秒）
	elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	elapsed *= 1000;
	cout << elapsed;
}
