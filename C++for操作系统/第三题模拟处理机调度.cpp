#include<iostream>
#include<stdio.h>
#include<queue>
#include <iomanip>
#include<string>
using namespace std;

struct PCB
{
	int ID;//进程号
	double arr_time;//到达时间
	double resp_time;//进程响应时间
	double rest_time;//剩余时间
};

int scheduling(queue<PCB> proces, double timeslice)//调度函数
{
	queue<PCB> ready;//就绪队列，处理机从此队列中调度进程
	ready.push(proces.front());
	proces.pop();//进程队列头部入就绪队列
	double slice_start;
	double slice_end=0;
	cout << "\n\n进程状态表如下：\n" << endl;
	cout << setw(20) << "进程ID" << setw(20) << "到达时间" << setw(20) << "进程响应时间" << setw(20) << "时间片开始时间" << setw(20) << "时间片结束时间" << endl;
	while (!proces.empty()||!ready.empty())//遍历调度所有进程
	{
		slice_start = slice_end;//这一个时间片的开始时间是上一个时间片的结束时间
		slice_end += timeslice;//这一个时间片的结束时间是上一个时间片的结束时间加上一个完整时间片的时间
		while (!proces.empty())//遍历进程队列将该时间片内所有到达的进程加入就绪队列中
		{
			if (proces.front().arr_time > slice_end)break;
			
			ready.push(proces.front());
			proces.pop();//进程队列头部入就绪队列
		}
		//就绪队列为空，继续循环，将剩下的进程入就绪队列
		if (ready.empty())continue;
		ready.front().rest_time -= timeslice;//进程的剩余时间可减少一个时间片
		//目前进程的剩余时间，即还需要运行的时间为0或复数，则该进程可结束
		if (ready.front().rest_time <= 0)
		{
			ready.front().rest_time = 0;//将剩余时间置零，代表该进程结束
			cout << setw(20) << ready.front().ID  << setw(20) << ready.front().arr_time  << setw(20) << ready.front().resp_time  << setw(20) << slice_start  << setw(20) << slice_end  << endl;
			ready.pop();//释放该进程
		}
		else//剩余时间仍大于0，即大于时间片，该进程仍需调度
		{
			cout << setw(20) << ready.front().ID  << setw(20) << ready.front().arr_time  << setw(20) << ready.front().resp_time  << setw(20) << slice_start  << setw(20) << slice_end  << endl;
			//该进程实现了一次调度，置于队尾,实现循环轮转
			PCB tmp = ready.front();
			ready.pop();
			ready.push(tmp);
		}

	}
	return 0;
}


int addproces(queue<PCB>proces, double allresp_time, double timeslice)
{
	cout << "\n\n请问是否添加新进程？（0：不添加；1：添加）";
	int num;
	cin >> num;

	while (num == 1)
	{
		PCB p;
		cout << "请输入进程ID：";
		cin >> p.ID;
		cout << "请输入进程到达时间：";
		cin >> p.arr_time;
		cout << "请输入进程响应时间：";
		cin >> p.resp_time;
		cout << "请输入进程剩余时间：";
		cin >> p.rest_time;
		proces.push(p);
		allresp_time += p.resp_time;
		//cout << proces.size()*proces.size() << endl;
		timeslice = allresp_time / (proces.size()*proces.size());
		cout << "时间片为：" << timeslice << endl;
		scheduling(proces, timeslice);
		cout << "请问是否添加新进程？（0：不添加；1：添加）";
		cin >> num;
	}
	return 0;
}
int test()//测试函数
{
	queue<PCB>proces;
	//总响应时间
	double allresp_time = 0;
	//时间片
	double timeslice = 0;
	PCB p1, p2, p3, p4, p5;

	p1 = { 1,0,3,3 };
	p2 = { 2,1,5,5 };
	p3 = { 3,5,5,5 };
	p4 = { 4,10,4,4 };
	p5 = { 5,12,6,4 };
	allresp_time += p1.resp_time + p2.resp_time + p3.resp_time + p4.resp_time + p5.resp_time;
	timeslice = allresp_time / 25;
	proces.push(p1);
	proces.push(p2);
	proces.push(p3);
	proces.push(p4);
	proces.push(p5);
	cout << "时间片为：" << timeslice << endl;
	scheduling(proces, timeslice);
	addproces(proces, allresp_time, timeslice);
	return 0;
}

int main()
{
	test();
	return 0;
}