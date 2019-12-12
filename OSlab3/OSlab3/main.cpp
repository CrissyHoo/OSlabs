#include<iostream>
using namespace std;

#define SIZE 8
int bit[SIZE][SIZE] = {0};//用来存贮位示图
void allocate() {
	int i, j, need, num=0;
	cout << "请输入需要分配的磁盘大小，单位为块，且小于等于64" << endl;
	cin >> need;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (bit[i][j] == 0) {
				num++;
			}
		}
	}
	if (need <=num) {
		cout << "分配成功！" << endl;
		cout << "分配的物理地址为：" << endl;
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (need <= 0) {
					break;
				}
				if (bit[i][j] == 0) {
					bit[i][j] = 1;
					cout << "第" << i << "柱面，" << "第" << j / 4 << "磁道，" << "第" << j % 4 << "块物理记录" << endl;
					need--;
				}
			}
		}
	}
	else {
		cout << "分配失败" << endl;
	}

}
void recycle() {
	//这个函数是回收用的
	int cylinder, track, log;
	cout << "请输入待回收的物理地址：" << endl;
	cout << "柱面号：";
	cin >> cylinder;
	cout << "磁道号：";
	cin >> track;
	cout << "物理记录号";
	cin >> log;
	int i = cylinder;
	int j = track * 4 + log;
	bit[i][j] = 0;
	cout << "已回收" << endl;
	cout << "回收的是第" << i << "字节 " << "第" << j << "位" << endl;
}
void display() {
	//展示位示图
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << bit[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
}
int main() {
	//初始化
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			bit[i][j] = 0;
		}
	}

	while (true) {
		cout << "输入1分配外存，输入2回收外存，输入3查看位示图，输入其他键退出。" << endl;
		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			allocate();
			break;
		case 2:
			recycle();
			break;
		case 3:
			display();
			break;
		default:
			exit(0);
			
		}
	}
}


