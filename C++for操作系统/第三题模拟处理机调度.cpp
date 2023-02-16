#include<iostream>
#include<stdio.h>
#include<queue>
#include <iomanip>
#include<string>
using namespace std;

struct PCB
{
	int ID;//���̺�
	double arr_time;//����ʱ��
	double resp_time;//������Ӧʱ��
	double rest_time;//ʣ��ʱ��
};

int scheduling(queue<PCB> proces, double timeslice)//���Ⱥ���
{
	queue<PCB> ready;//�������У�������Ӵ˶����е��Ƚ���
	ready.push(proces.front());
	proces.pop();//���̶���ͷ�����������
	double slice_start;
	double slice_end=0;
	cout << "\n\n����״̬�����£�\n" << endl;
	cout << setw(20) << "����ID" << setw(20) << "����ʱ��" << setw(20) << "������Ӧʱ��" << setw(20) << "ʱ��Ƭ��ʼʱ��" << setw(20) << "ʱ��Ƭ����ʱ��" << endl;
	while (!proces.empty()||!ready.empty())//�����������н���
	{
		slice_start = slice_end;//��һ��ʱ��Ƭ�Ŀ�ʼʱ������һ��ʱ��Ƭ�Ľ���ʱ��
		slice_end += timeslice;//��һ��ʱ��Ƭ�Ľ���ʱ������һ��ʱ��Ƭ�Ľ���ʱ�����һ������ʱ��Ƭ��ʱ��
		while (!proces.empty())//�������̶��н���ʱ��Ƭ�����е���Ľ��̼������������
		{
			if (proces.front().arr_time > slice_end)break;
			
			ready.push(proces.front());
			proces.pop();//���̶���ͷ�����������
		}
		//��������Ϊ�գ�����ѭ������ʣ�µĽ������������
		if (ready.empty())continue;
		ready.front().rest_time -= timeslice;//���̵�ʣ��ʱ��ɼ���һ��ʱ��Ƭ
		//Ŀǰ���̵�ʣ��ʱ�䣬������Ҫ���е�ʱ��Ϊ0��������ý��̿ɽ���
		if (ready.front().rest_time <= 0)
		{
			ready.front().rest_time = 0;//��ʣ��ʱ�����㣬����ý��̽���
			cout << setw(20) << ready.front().ID  << setw(20) << ready.front().arr_time  << setw(20) << ready.front().resp_time  << setw(20) << slice_start  << setw(20) << slice_end  << endl;
			ready.pop();//�ͷŸý���
		}
		else//ʣ��ʱ���Դ���0��������ʱ��Ƭ���ý����������
		{
			cout << setw(20) << ready.front().ID  << setw(20) << ready.front().arr_time  << setw(20) << ready.front().resp_time  << setw(20) << slice_start  << setw(20) << slice_end  << endl;
			//�ý���ʵ����һ�ε��ȣ����ڶ�β,ʵ��ѭ����ת
			PCB tmp = ready.front();
			ready.pop();
			ready.push(tmp);
		}

	}
	return 0;
}


int addproces(queue<PCB>proces, double allresp_time, double timeslice)
{
	cout << "\n\n�����Ƿ�����½��̣���0������ӣ�1����ӣ�";
	int num;
	cin >> num;

	while (num == 1)
	{
		PCB p;
		cout << "���������ID��";
		cin >> p.ID;
		cout << "��������̵���ʱ�䣺";
		cin >> p.arr_time;
		cout << "�����������Ӧʱ�䣺";
		cin >> p.resp_time;
		cout << "���������ʣ��ʱ�䣺";
		cin >> p.rest_time;
		proces.push(p);
		allresp_time += p.resp_time;
		//cout << proces.size()*proces.size() << endl;
		timeslice = allresp_time / (proces.size()*proces.size());
		cout << "ʱ��ƬΪ��" << timeslice << endl;
		scheduling(proces, timeslice);
		cout << "�����Ƿ�����½��̣���0������ӣ�1����ӣ�";
		cin >> num;
	}
	return 0;
}
int test()//���Ժ���
{
	queue<PCB>proces;
	//����Ӧʱ��
	double allresp_time = 0;
	//ʱ��Ƭ
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
	cout << "ʱ��ƬΪ��" << timeslice << endl;
	scheduling(proces, timeslice);
	addproces(proces, allresp_time, timeslice);
	return 0;
}

int main()
{
	test();
	return 0;
}