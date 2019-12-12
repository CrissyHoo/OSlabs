#include<iostream>
#include<math.h>
#include<algorithm>
#include<string>
using namespace std;
#define N 1000
int n1;//空闲分区的个数
int n2;//作业分区的个数

struct freeblock {
	int start;//起始地址
	int end;//终止地址
	int length;//长度
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
	cout << "空闲分区" << endl;
	for (int i = 0; i < n1; i++) {
		cout << "分区号：" << i<<endl;
		cout << "起始地址：" << mFree[i].start << endl;
		cout << "长度：" << mFree[i].length << endl;
		cout << "终止地址" << mFree[i].end << endl;
	}
	cout << endl;
}
void displayT() {
	cout << "作业分区" << endl;
	for (int i = 0; i < n2;i++) {
		cout << "分区号：" << i << endl;
		cout << "起始地址：" << mWork[i].start << endl;
		cout << "长度：" << mWork[i].length << endl;
		cout << "终止地址" << mWork[i].end << endl;
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
	cout << "输入1装入新作业，输入2回收作业，输入其他任意键结束：" << endl;
	cin >> t;
	
		if (t == 1) {
			cout << "请输入作业占用长度："  << endl;
			cin >> len;
			flag = 0;
			for (i = 0; i < n1; i++) {
				if (mFree[i].length >= len) {
					flag = 1;
					break;
				}
			}
			if (!flag) {
				cout << "分配内存失败！" << endl;
			}
			else {//分配成功，将作业加入作业区中
				mWork[n2].start = mFree[i].start;
				mWork[n2].end = mWork[n2].start + len;
				mWork[n2].length = len;
				n2++;
				if (mFree[i].length == len) {
					//作业长度和分配的空闲分区长度完全相等
					for (j = i; j < n1 - 1; j++) {
						mFree[j].start = mFree[j + 1].start;
						mFree[j].end = mFree[j + 1].end;
						mFree[j].length = mFree[j + 1].length;
					}
					n1--;


				}
				else {//有剩余
					mFree[i].start += len;
					mFree[i].length -= len;
				}
			}

		}
		else if (t == 2) {//回收
			cout << "输入要回收的作业号：" << endl;
			cin >> id;
			front = mid = behind = 0;
			//分析id区情况
			for (i = 0; i < n1; i++) {
				if (mFree[i].start > mWork[id].end) {
					break;
				}
				if (mFree[i].end == mWork[id].start) {
					//待回收分区上面连接了空闲区
					front = 1;
					t1 = i;
				}
				if (mWork[id].end == mFree[i].start) {
					//下面有空闲区
					behind = 1;
					t2 = i;
				}
			}
			//处理
			//孤零零的分区
			if (!front && !behind) {

				mFree[n1].start = mWork[id].start;
				mFree[n1].end = mWork[id].end;
				mFree[n1].length = mWork[id].end;
				n1++;
				sort(mFree, mFree + n1, cmp1);//根据起始地址重新排序
				//在作业分区中删除
				for (i = id; i < n2 - 1; i++) {
					mWork[i].start = mWork[i + 1].start;
					mWork[i].end = mWork[i + 1].end;
					mWork[i].length = mWork[i + 1].length;

				}
				n2--;


			}
			if (front &&behind) {
				//上下均有空闲分区
				mid = 1;
			}

			if (mid) {
				//合并上下空闲区和中间的作业区
				mFree[t1].end = mFree[t2].end;
				mFree[t1].length = mFree[t1].end - mFree[t1].start;
				//删除空闲分区t2
				for (i = t2; i < n1 - 1; i++) {
					mFree[i].start = mFree[i + 1].start;
					mFree[i].end = mFree[i + 1].end;
					mFree[i].length = mFree[i + 1].length;
				}
				n1--;
				//删除作业区
				for (i = id; i < n2 - 1; i++) {
					mWork[i].start = mWork[i + 1].start;
					mWork[i].end = mWork[i + 1].end;
					mWork[i].length = mWork[i + 1].length;

				}
				n2--;

			}
			if (front && !mid) {
				//上面有但下面没有
				//合并自己和上面
				mFree[t1].end = mWork[id].end;
				mFree[t1].length += mWork[id].length;
				//删除作业区
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
				//删除作业区
				for (i = id; i < n2 - 1; i++) {
					mWork[i].start = mWork[i + 1].start;
					mWork[i].end = mWork[i + 1].end;
					mWork[i].length = mWork[i + 1].length;

				}
				n2--;
			}
		}
		else {
			cout << "结束" << endl;
			break;
		}
		displayF();
		displayT();
	}


}