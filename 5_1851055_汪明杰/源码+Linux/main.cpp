#include "Queue.h"
#include<iostream>

using namespace std;

int main()
{
	int N;//顾客总数
	//直至输入正确
	while (true)
	{
		cin >> N;
		if (N <= 0)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Please input a positve." << endl;
		}
		else
			break;
	}
	Queue<int> queueA, queueB;
	//顾客入队
	for (int i = 1; i <= N; ++i)
	{
		int temp;
		cin >> temp;
		if (temp % 2 == 0)
			queueB.push(temp);
		else
			queueA.push(temp);
	}
	cout << "Output:";
	//出队
	while (!queueA.empty() || !queueB.empty())
	{
		//A业务处理完毕
		for (int i = 0; i < 2; ++i)
			if (!queueA.empty())
			{
				cout << queueA.front() << " ";
				queueA.pop();
			}
		//B业务处理完毕
		if (!queueB.empty())
		{
			cout << queueB.front() << " ";
			queueB.pop();
		}
	}

	cin.clear();
	cin.ignore(1024, '\n');
	cout << endl << "Enter to Exit";
	cin.get();

	return 0;
}