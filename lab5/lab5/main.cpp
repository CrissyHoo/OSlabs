#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
//定义进程状态
typedef enum {
	READY,//准备
	RUNNING,//运行
	BLOCKED,//阻塞
	FINISH//完成
}proState;

//各种指令ID
#define P 0//执行
#define V 1//释放
#define PUT  2//放入缓冲池中
#define  GET  3
#define PRODUCE 4
#define CONSUME 5
#define GOTO 6
#define  NOP 7

//信号量表示
typedef enum {S1,S2}blockReason;

//PCB结构体定义
typedef struct {
	char name[10];
	proState state;
	blockReason reason;
	int breakpoint;
}PCB;

typedef int semaphore;
typedef int product;
#define BUFLEN 10//缓冲区大小

//缓冲区队列
product buffer[BUFLEN + 1];
int front, rear;

//进程指令序列
int productArray[] = { PRODUCE,P,PUT,V,GOTO };//
int consumerArray[] = { P,GET,V,CONSUME,GOTO };

//指令计数器
int PC;


PCB producer,consumer;
PCB *now;//current process
product in, out;//当前处理的产品
semaphore s1, s2;//s1可以理解为缓冲区的剩余大小，s2可以理解为产品数量
int max;//最大生产数

void (*func[8])();//八个函数，每个函数对应一条指令，


void p() {
	if (now == &producer) {
		cout << "produer P"<<endl;
		if (--s1 < 0) {
			//需要等待
			cout << "produce waiting..." << endl;
			now->state = BLOCKED;
			now->reason = S1;
			now->breakpoint = P;
		}
		else {
			cout<<"Continue.";
		}
	}
	else {
		cout << "consumer P" << endl;
		if (--s2 < 0) {//没有资源了
			cout << "consumer waiting.." << endl;
			now->state = BLOCKED;
			now->breakpoint = P;
			now->reason = S2;
			
		}
		else {
			cout << "continue" << endl;
		}

	}
	cout << "s1=" << s1 << ",s2=" << s2 << endl;
	
}

void v() {
	if (now == &producer) {
		cout << "producer V" << endl;
		if (++s2 <= 0 && consumer.state == BLOCKED) {
			//消费者进程被阻塞并且缓冲区剩余资源数小于0
			consumer.state = READY;
		}
	}
	else {
		cout << "consumer V" << endl;
		if (++s1 <= 0 && producer.state == BLOCKED)
			//进程需要等待并且producer现在的状态是阻塞
			producer.state = READY;
	}
	cout << "s1=" << s1 << ",s2=" << s2 << endl;

}

void put() {
	//进队列
	buffer[rear] = in;
	cout << "Producer put " << in << " at " << rear<<endl;
	rear = (rear + 1) % (BUFLEN + 1);
}

void get() {
	//出队列
	out = buffer[front];
	cout << "consumer get " << out << " at " << front << endl;
	front = (front + 1) % (BUFLEN + 1);
}

void produce() {
	in++;
	cout << "product " << in << " produced." << endl;
}

void consume() {
	cout << "product " << out << " consumed." << endl;
}

void goto0() {
	if (now == &producer) {
		cout << "Producer goto." << endl;
		if (in >= max) {
			cout << "it's max now, produce stops." << endl;
			now->state = FINISH;
		}
	}
	else {
		cout << "consumer goto" << endl;

	}
	PC = 0;
}

void init() {
	s1 = BUFLEN;//缓冲区是空的
	s2 = 0;
	strcpy_s(producer.name, "producer");
	strcpy_s(consumer.name, "consumer");
	producer.state = consumer.state = READY;
	producer.breakpoint = consumer.breakpoint = 0;//P
	now = &producer;
	PC = 0;
	front = rear = 0;
	in = 0;
	func[0] = p;
	func[1] = v;
	func[2] = put;
	func[3] = get;
	func[4] = produce;
	func[5] = consume;
	func[6] = goto0;
	func[7] = NULL;
	
}

void execute() {
	int i = PC++;
	int j = (now == &producer) ? productArray[i] : consumerArray[i];
	func[j]();
}

void dispatch() {
	while (1) {
		now->breakpoint = PC;
		//保护现场
		if (now->state != BLOCKED && now->state != FINISH) {
			now->state = READY;
		}
		//随机从就绪队列中抽一个
		int choice = rand() % 2;
		if (producer.state == READY && consumer.state == READY) {
			now = (choice == 0) ? &producer : &consumer;
		}
		else if (producer.state == READY) {
			now = &producer;
		}
		else if (consumer.state == READY) {
			now = &consumer;
		}
		else {
			cout << "无可运行进程" << endl;
			
			cin.get();
			cin.get();
			exit(0);
		}
		now->state = RUNNING;
		PC = now->breakpoint;
		execute();
		cout << endl;

	}
}
int main() {
	cout << "生产者最多生产多少个产品？" << endl;
	cin >> max;
	init();
	dispatch();
	cin.get();
	cin.get();
}