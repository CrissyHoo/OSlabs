#include<iostream>
using namespace std;

#define SIZE 8
int bit[SIZE][SIZE] = {0};//��������λʾͼ
void allocate() {
	int i, j, need, num=0;
	cout << "��������Ҫ����Ĵ��̴�С����λΪ�飬��С�ڵ���64" << endl;
	cin >> need;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (bit[i][j] == 0) {
				num++;
			}
		}
	}
	if (need <=num) {
		cout << "����ɹ���" << endl;
		cout << "����������ַΪ��" << endl;
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (need <= 0) {
					break;
				}
				if (bit[i][j] == 0) {
					bit[i][j] = 1;
					cout << "��" << i << "���棬" << "��" << j / 4 << "�ŵ���" << "��" << j % 4 << "�������¼" << endl;
					need--;
				}
			}
		}
	}
	else {
		cout << "����ʧ��" << endl;
	}

}
void recycle() {
	//��������ǻ����õ�
	int cylinder, track, log;
	cout << "����������յ������ַ��" << endl;
	cout << "����ţ�";
	cin >> cylinder;
	cout << "�ŵ��ţ�";
	cin >> track;
	cout << "�����¼��";
	cin >> log;
	int i = cylinder;
	int j = track * 4 + log;
	bit[i][j] = 0;
	cout << "�ѻ���" << endl;
	cout << "���յ��ǵ�" << i << "�ֽ� " << "��" << j << "λ" << endl;
}
void display() {
	//չʾλʾͼ
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
	//��ʼ��
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			bit[i][j] = 0;
		}
	}

	while (true) {
		cout << "����1������棬����2������棬����3�鿴λʾͼ�������������˳���" << endl;
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


