#include<iostream>
#include<queue>
#include<string>
using namespace std;

#define Time_Pice 1
struct _PCBNode
{
	char name[20];       //进程名称
	int arrive_time;     //到达时间
	int need_time;      //服务时间
	int cputime;         //CPU已经执行的时间
	int accomplish_Time; //完成时间
	int turn_over_time;  //周转时间
	bool tag;            //是否完成
};

class _PCB
{
public:
	void Push(struct _PCBNode& node)
	{
		_PNode.push(node);
	}
	void init_time()
	{
		TIME = 0;
	}
	bool empty()
	{
		return _PNode.empty();
	}
	void Pop()
	{
		struct _PCBNode node;
		unsigned int n = _PNode.size();
		unsigned int  i = 0;
		for (; i < n; ++i)
		{
			node = _PNode.front(); _PNode.pop();
			if (node.arrive_time <= TIME)
			{
				break;
			}
			_PNode.push(node);
		}
		TIME = TIME + Time_Pice;
		if (i == n)
		{
			Display_PCB();
			return;
		}
		node.cputime += Time_Pice;

		if (node.cputime >= node.need_time)
		{
			node.accomplish_Time = TIME;
			node.tag = true;
			node.turn_over_time = node.accomplish_Time - node.arrive_time;
			_CNode.push(node);
			cout << node.name << "   run over" << endl;
		}
		else
		{
			_PNode.push(node);
		}
		Display_PCB();
	}
	void Display_PCB()
	{
		cout << "  TIME   " << TIME << endl;
		int n = _PNode.size();
		if (n != 0)
		{
			cout << "ready......." << endl;
			cout << "name   arrive_time  need_time    cputime    tag" << endl;
			for (int i = 0; i < n; ++i)
			{
				struct _PCBNode node = _PNode.front(); _PNode.pop();
				if (node.arrive_time <= TIME)
				{
					cout << node.name << "             " << node.arrive_time << "           "
						<< node.need_time << "          " << node.cputime << "        " << node.tag << endl;
				}

				_PNode.push(node);
			}
			cout << endl;
		}

		n = _CNode.size();
		if (n != 0)
		{
			cout << "run over" << endl;
			cout << "name   arrive_time  need_time   accomplish_Time     turn_over_time     tag" << endl;
			for (int i = 0; i < n; ++i)
			{
				struct _PCBNode node = _CNode.front(); _CNode.pop();
				cout << node.name << "             " << node.arrive_time << "           "
					<< node.need_time << "     " << node.accomplish_Time << "                     " << node.turn_over_time << "                 " << node.tag << endl;
				_CNode.push(node);
			}
			cout << endl;
		}
		cout << "**************************************************" << endl;
	}
private:
	queue<struct _PCBNode> _PNode;
	queue<struct _PCBNode> _CNode;
	int TIME;
};

void main()
{
	_PCB pcb;
	pcb.init_time();
	int PCB_Numble;

	char PCBname[20];
	int arrive_time;
	int need_time;

	cout << "input PCB_Numble :   ";
	cin >> PCB_Numble;

	cout << "input PCBname arrive_time and need_time. For example A 0 5\n";
	for (int i = 0; i < PCB_Numble; ++i)
	{
		cin >> PCBname >> arrive_time >> need_time;
		struct _PCBNode node;
		strcpy_s(node.name, PCBname);
		node.arrive_time = arrive_time;
		node.need_time = need_time;
		node.accomplish_Time = 0;
		node.cputime = 0;
		node.tag = 0;
		pcb.Push(node);
	}

	pcb.Display_PCB();
	while (!pcb.empty())
	{
		pcb.Pop();
	}
	cin.get();
	cin.get();
}

