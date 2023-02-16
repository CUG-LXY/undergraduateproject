#include <windows.h>
//#include"PixImage.h"
#include"RunLengthEncoding.h"
#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>



//��ȷ�Բ���
//�޸�����
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

//ģ��
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
//��Ե���
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

//��ɫͼ��ת�γ̱���
void correct_change()
{
	for (int i = 0; i < 200; i++)
	{
		RunLengthEncoding run();
	}
}

//ͼ��ת�γ̱���
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
//�γ̱���תͼ��
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


//�����γ̱���ʱ��������,ע�����ڴ����н�����ֵ��Ϊ����
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

//�����γ̱���
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


//��Ч�Բ���

//�����̺߳�����������Ľṹ��
typedef struct __THREAD_DATA
{
	int num;//numΪͼƬ·���е����������ļ����еĵڼ���ͼƬ
}THREAD_DATA;



//�̺߳���
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
	QueryPerformanceCounter(&startCount);// ͳ��������ʱ��


	//��ʼ���߳�����
	THREAD_DATA threadData1, threadData2, threadData3, threadData4;
	threadData1.num = 60;//���ݲ��Դ������и���
	threadData2.num = 120;
	threadData3.num = 180;
	threadData4.num = 240;
	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc, &threadData1, 0, NULL);//���߳�
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc, &threadData2, 0, NULL);
	HANDLE hThread3 = CreateThread(NULL, 0, ThreadProc, &threadData3, 0, NULL);
	HANDLE hThread4 = CreateThread(NULL, 0, ThreadProc, &threadData4, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	CloseHandle(hThread3);
	CloseHandle(hThread4);//һ�����̼߳��ĸ����̣߳�������߳�



	//���߳�
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
		//img.Modifypx(3, 4, 56, 78, 90);//���ʲô���ܾͰѱ�Ĺ���ע�͵�
		//img.Fuzzy(2);
		//img.PrintPic();
		//img.EdgeDetection(tmp);
		//tmp = Edge + b + c;
		//img.CreatTiff(tmp);
		//img.PrintPic();
		b = "";
		tmp = "";


	}
	// ֹͣ��ʱ��
	QueryPerformanceCounter(&endCount);

	// ���ؼ�ʱ������ʱ��(��λ�����룩
	elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	elapsed *= 1000;
	cout << elapsed;
}
