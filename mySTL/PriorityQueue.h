#pragma once
#include "Heap.h"

template <typename T, class Compare = Less<T>, class Sequence = Vector<T>>
class PriorityQueue
{
public:

public:
	Sequence _container;
	Compare _comparer;

public:
	PriorityQueue() : _container() {}
	PriorityQueue(const Compare &comp) : _container(), _comparer(comp) {}
	template <class iterator>
	PriorityQueue(iterator first, iterator last) : _container(first, last)
	{
		makeHeap(first, last, _comparer);
	}
	template <class iterator>
	PriorityQueue(iterator first, iterator last, const Compare &comp)
		: _container(first, last), _comparer(comp)
	{
		makeHeap(first, last, _comparer);
	}
	~PriorityQueue() {}

	bool empty() const { return _container.empty(); }
	int size() const { return _container.size(); }
	const T top() const { return _container.front(); }

	void push(const T x)
	{
		_container.push_back(x);
		pushHeap(_container.begin(), _container.end(), _comparer);
	}

	void pop()
	{
		popHeap(_container.begin(), _container.end(), _comparer);
		_container.pop_back();
	}
};