#include<iostream>
#include "PriorityQueue.h"
using namespace std;

int main()
{
	int N, temp;
	cin >> N;
	//优先级队列，也即最小堆
	PriorityQueue<int,Greater<int>> woodLength;
	for (int i = 0; i < N; ++i)
	{
		cin >> temp;
		woodLength.push(temp);
	}
	int sumCost = woodLength.size() == 1 ? woodLength.top() : 0;
	while (woodLength.size() > 1)
	{
		int length1 = woodLength.top();
		woodLength.pop();
		int length2 = woodLength.top();
		woodLength.pop();
		sumCost += length1 + length2;
		woodLength.push(length1 + length2);
	}
	cout << sumCost;

	cin.clear();
	cin.ignore(1024, '\n');
	cout << endl << "Enter to Exit";
	cin.get();
	return 0;
}