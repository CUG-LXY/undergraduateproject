#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include<iostream>
#include <stdio.h>
#include<queue>
using namespace std;

#define num 10
int count=10;

sem_t empty;
sem_t mutex;
sem_t stu;
sem_t exam;
sem_t enter;
sem_t leave;
queue<unsigned int> chair;
unsigned int quizer;//wait and test



void* students(void* args)//students
{
	sem_wait(&empty);
	sem_wait(&mutex);
	unsigned int a = (unsigned int)pthread_self()%100;
	chair.push(a);
	cout << a << " is on the chair." << endl;
	sem_post(&mutex);
	sem_post(&stu);
	sem_wait(&leave);
}

void* assistant(void* args)//assistant
{
	while(count){
	sem_wait(&exam);
	sem_wait(&stu);
	sem_wait(&mutex);
	quizer = chair.front();
	chair.pop();//the student enters the room
	//sem_wait(&mutex);
	cout << quizer << " enters the room and waits for the test." << endl;
	sem_post(&mutex);
 	sem_post(&empty);
	sem_post(&enter);
	}
}

void* teacher(void* args)//teacher
{
	//sleep(300);
	
	while(count){
	sem_wait(&enter);
	sem_wait(&mutex);
	cout << quizer << " starts his test." << endl;
	sem_post(&mutex);
	sem_wait(&mutex);
	sleep(10);
	cout << quizer << " finishs his test.He leaves the room." << endl;
	sem_post(&mutex);
	sem_post(&leave);
	sem_post(&exam);
	count--;
	}
	
}

int main()
{
	sem_init(&empty, 0, 5);
	sem_init(&mutex, 0, 1);
	sem_init(&stu, 0, 0);//the student who waits
	sem_init(&exam, 0, 1);//wether the room is free
	sem_init(&enter, 0, 0);//4
	sem_init(&leave, 0, 0);//5
	pthread_t student[num];
	for (int i = 0; i < num; i++)
		pthread_create(&student[i], NULL, students, NULL);
	pthread_t assit;
	pthread_create(&assit, NULL, assistant, NULL);
	pthread_t teach;
	pthread_create(&teach, NULL, teacher, NULL);
	
	void *retval;
	
	pthread_join(assit, &retval);
	pthread_join(teach,&retval);
	for (int i = 0; i < num; i++)
		pthread_join(student[i], &retval);
	return 0;
	


}
