#pragma once
#include<cstdlib>
namespace mySTL
{

	template <class Iter, typename T>
	Iter find(Iter begin, Iter end, const T &value)
	{
		while (begin != end) {
			if (*begin == value) return begin;
			++begin;
		}
		return end;
	}

	template<typename T>
	void swap(T& t1, T& t2) {
		T tmp = t1;
		t1 = t2;
		t2 = tmp;
	}

	template <typename Iter>
	void random_shuffle(Iter first, Iter last)
	{
		int rest = last - first;
		while (first != last) {
			swap(*first, *(first + rand() % rest));
			--rest;
			++first;
		}
	}
}