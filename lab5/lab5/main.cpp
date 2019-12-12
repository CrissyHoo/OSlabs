#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
//�������״̬
typedef enum {
	READY,//׼��
	RUNNING,//����
	BLOCKED,//����
	FINISH//���
}proState;

//����ָ��ID
#define P 0//ִ��
#define V 1//�ͷ�
#define PUT  2//���뻺�����
#define  GET  3
#define PRODUCE 4
#define CONSUME 5
#define GOTO 6
#define  NOP 7

//�ź�����ʾ
typedef enum {S1,S2}blockReason;

//PCB�ṹ�嶨��
typedef struct {
	char name[10];
	proState state;
	blockReason reason;
	int breakpoint;
}PCB;

typedef int semaphore;
typedef int product;
#define BUFLEN 10//��������С

//����������
product buffer[BUFLEN + 1];
int front, rear;

//����ָ������
int productArray[] = { PRODUCE,P,PUT,V,GOTO };//
int consumerArray[] = { P,GET,V,CONSUME,GOTO };

//ָ�������
int PC;


PCB producer,consumer;
PCB *now;//current process
product in, out;//��ǰ����Ĳ�Ʒ
semaphore s1, s2;//s1�������Ϊ��������ʣ���С��s2�������Ϊ��Ʒ����
int max;//���������

void (*func[8])();//�˸�������ÿ��������Ӧһ��ָ�


void p() {
	if (now == &producer) {
		cout << "produer P"<<endl;
		if (--s1 < 0) {
			//��Ҫ�ȴ�
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
		if (--s2 < 0) {//û����Դ��
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
			//�����߽��̱��������һ�����ʣ����Դ��С��0
			consumer.state = READY;
		}
	}
	else {
		cout << "consumer V" << endl;
		if (++s1 <= 0 && producer.state == BLOCKED)
			//������Ҫ�ȴ�����producer���ڵ�״̬������
			producer.state = READY;
	}
	cout << "s1=" << s1 << ",s2=" << s2 << endl;

}

void put() {
	//������
	buffer[rear] = in;
	cout << "Producer put " << in << " at " << rear<<endl;
	rear = (rear + 1) % (BUFLEN + 1);
}

void get() {
	//������
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
	s1 = BUFLEN;//�������ǿյ�
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
		//�����ֳ�
		if (now->state != BLOCKED && now->state != FINISH) {
			now->state = READY;
		}
		//����Ӿ��������г�һ��
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
			cout << "�޿����н���" << endl;
			
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
	cout << "����������������ٸ���Ʒ��" << endl;
	cin >> max;
	init();
	dispatch();
	cin.get();
	cin.get();
}