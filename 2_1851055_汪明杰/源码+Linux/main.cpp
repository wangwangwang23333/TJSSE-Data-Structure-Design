#include "List.h"
#include<iostream>

using namespace std;

template<class Type>
List<Type> intersection(const List<Type> &l1, const List<Type> &l2)
{
	auto it1 = l1.begin();
	auto it2 = l2.begin();

	//保存交集结果的链表
	List<Type> result;

	while (it1 != l1.end() && it2 != l2.end())
	{
		if (*it1 < *it2)
			++it1;
		else if (*it1 > *it2)
			++it2;
		else
		{
			result.push_back(*it1);
			++it1;
			++it2;
		}
	}

	return result;
}

int main()
{
	List<int> l1, l2, l3;
	int i;

	//输入
	while (cin >> i && i != -1)
		l1.push_back(i);
	while (cin >> i && i != -1)
		l2.push_back(i);

	//求交集
	l3 = intersection(l1, l2);

	//输出结果
	if (!l3.empty())
	{
		for (auto it = l3.begin(); it != l3.end(); ++it)
			cout << *it << " ";
	}
	else
		cout << "NULL";

	cin.clear();
	cin.ignore(1024, '\n');
	
	cout << endl << "Enter to Exit";
	cin.get();

	return 0;
}