#include<iostream>
#include<math.h>
#include<algorithm>
#include<string>
using namespace std;
#define N 1000
int n1;//���з����ĸ���
int n2;//��ҵ�����ĸ���

struct freeblock {
	int start;//��ʼ��ַ
	int end;//��ֹ��ַ
	int length;//����
}mFree[N];
struct task {
	int start;
	int end;
	int length;
}mWork[N];

void init() {
	n1 = 1;
	n2 = 0;
	mFree[0].start = 0;
	mFree[0].end = 128;
	mFree[0].length = 128;

}

bool cmp1(const freeblock &x, const freeblock &y) {
	return x.start < y.start;
}
bool cmp2(const task &x, const task &y) {
	return x.start < y.start;
}


void displayF() {
	cout << "���з���" << endl;
	for (int i = 0; i < n1; i++) {
		cout << "�����ţ�" << i<<endl;
		cout << "��ʼ��ַ��" << mFree[i].start << endl;
		cout << "���ȣ�" << mFree[i].length << endl;
		cout << "��ֹ��ַ" << mFree[i].end << endl;
	}
	cout << endl;
}
void displayT() {
	cout << "��ҵ����" << endl;
	for (int i = 0; i < n2;i++) {
		cout << "�����ţ�" << i << endl;
		cout << "��ʼ��ַ��" << mWork[i].start << endl;
		cout << "���ȣ�" << mWork[i].length << endl;
		cout << "��ֹ��ַ" << mWork[i].end << endl;
	}
	cout << endl;
}


int main() {
	int  t, len=0, flag, id,i,j;
	int front, mid, behind;
	int t1, t2;
	init();
	displayF();
	while (true) {
	cout << "����1װ������ҵ������2������ҵ���������������������" << endl;
	cin >> t;
	
		if (t == 1) {
			cout << "��������ҵռ�ó��ȣ�"  << endl;
			cin >> len;
			flag = 0;
			for (i = 0; i < n1; i++) {
				if (mFree[i].length >= len) {
					flag = 1;
					break;
				}
			}
			if (!flag) {
				cout << "�����ڴ�ʧ�ܣ�" << endl;
			}
			else {//����ɹ�������ҵ������ҵ����
				mWork[n2].start = mFree[i].start;
				mWork[n2].end = mWork[n2].start + len;
				mWork[n2].length = len;
				n2++;
				if (mFree[i].length == len) {
					//��ҵ���Ⱥͷ���Ŀ��з���������ȫ���
					for (j = i; j < n1 - 1; j++) {
						mFree[j].start = mFree[j + 1].start;
						mFree[j].end = mFree[j + 1].end;
						mFree[j].length = mFree[j + 1].length;
					}
					n1--;


				}
				else {//��ʣ��
					mFree[i].start += len;
					mFree[i].length -= len;
				}
			}

		}
		else if (t == 2) {//����
			cout << "����Ҫ���յ���ҵ�ţ�" << endl;
			cin >> id;
			front = mid = behind = 0;
			//����id�����
			for (i = 0; i < n1; i++) {
				if (mFree[i].start > mWork[id].end) {
					break;
				}
				if (mFree[i].end == mWork[id].start) {
					//�����շ������������˿�����
					front = 1;
					t1 = i;
				}
				if (mWork[id].end == mFree[i].start) {
					//�����п�����
					behind = 1;
					t2 = i;
				}
			}
			//����
			//������ķ���
			if (!front && !behind) {

				mFree[n1].start = mWork[id].start;
				mFree[n1].end = mWork[id].end;
				mFree[n1].length = mWork[id].end;
				n1++;
				sort(mFree, mFree + n1, cmp1);//������ʼ��ַ��������
				//����ҵ������ɾ��
				for (i = id; i < n2 - 1; i++) {
					mWork[i].start = mWork[i + 1].start;
					mWork[i].end = mWork[i + 1].end;
					mWork[i].length = mWork[i + 1].length;

				}
				n2--;


			}
			if (front &&behind) {
				//���¾��п��з���
				mid = 1;
			}

			if (mid) {
				//�ϲ����¿��������м����ҵ��
				mFree[t1].end = mFree[t2].end;
				mFree[t1].length = mFree[t1].end - mFree[t1].start;
				//ɾ�����з���t2
				for (i = t2; i < n1 - 1; i++) {
					mFree[i].start = mFree[i + 1].start;
					mFree[i].end = mFree[i + 1].end;
					mFree[i].length = mFree[i + 1].length;
				}
				n1--;
				//ɾ����ҵ��
				for (i = id; i < n2 - 1; i++) {
					mWork[i].start = mWork[i + 1].start;
					mWork[i].end = mWork[i + 1].end;
					mWork[i].length = mWork[i + 1].length;

				}
				n2--;

			}
			if (front && !mid) {
				//�����е�����û��
				//�ϲ��Լ�������
				mFree[t1].end = mWork[id].end;
				mFree[t1].length += mWork[id].length;
				//ɾ����ҵ��
				for (i = id; i < n2 - 1; i++) {
					mWork[i].start = mWork[i + 1].start;
					mWork[i].end = mWork[i + 1].end;
					mWork[i].length = mWork[i + 1].length;

				}
				n2--;


			}
			if (behind && !mid) {
				mFree[t2].start = mWork[id].start;
				mFree[t2].length += mWork[id].length;
				//ɾ����ҵ��
				for (i = id; i < n2 - 1; i++) {
					mWork[i].start = mWork[i + 1].start;
					mWork[i].end = mWork[i + 1].end;
					mWork[i].length = mWork[i + 1].length;

				}
				n2--;
			}
		}
		else {
			cout << "����" << endl;
			break;
		}
		displayF();
		displayT();
	}


}