#pragma once
#include "Functional.h"
#include "Vector.h"
#include "Algorithm.h"


//将*(end-1)调整到合适的位置, 使得[start,end)变成堆
template <class Iter>
void pushHeap(Iter start, Iter end)
{
	typedef typename Iter::value_type value_type;
	siftFix(start, 0, end - start - 1, *(end - 1), Less<value_type>());
}

template <class Iter, class Compare>
void pushHeap(Iter start, Iter end, Compare &comp)
{
	siftFix(start, 0, end - start - 1, *(end - 1), comp);
}

//功能：将*(start)交换到*(end-1)处(以便删去), [start,end-1)变成堆
template <class Iter>
void popHeap(Iter start, Iter end)
{
	typedef typename Iter::value_type value_type;
	value_type value = *(end - 1);  //将原来的末尾值保存起来
	*(end - 1) = *(start);  //将*(start)移动到*(end-1),*(start)处出现hole
	sinkFix(start, end - start - 1, 0, value, Less<value_type>());
}
template <class Iter, class Compare>
void popHeap(Iter start, Iter end, Compare &comp)
{
	typedef typename Iter::value_type value_type;
	value_type value = *(end - 1);  //将原来的末尾值保存起来
	*(end - 1) = *(start);  //将*(start)移动到*(end-1),*(start)处出现hole
	sinkFix(start, end - start - 1, 0, value, comp);
}


//功能：将[start,end)变成堆

template <class Iter>
void makeHeap(Iter start, Iter end)
{
	typedef typename Iter::value_type value_type;
	ptrdiff_t len = end - start;
	if (len < 2) return;
	ptrdiff_t hole = (len - 2) / 2;
	while (hole >= 0) {
		//调整 hole 节点
		sinkFix(start, len, hole, *(start + hole), Less<value_type>());
		--hole;
	}
}

template <class Iter, class Compare>
void makeHeap(Iter start, Iter end, Compare comp)
{
	ptrdiff_t len = end - start;
	if (len < 2) return;
	ptrdiff_t hole = (len - 2) / 2;
	while (hole > 0) {
		//调整 hole 节点
		sinkFix(start, len, hole, *(start + hole), comp);
		--hole;
	}
}



//功能：向上调整hole的位置, 找到合适的位置将value存入

template <class Iterator, typename T, class Compare>
void siftFix(Iterator first,
	ptrdiff_t top,
	ptrdiff_t hole,
	T value,
	Compare comp)
{
	ptrdiff_t parent = (hole - 1) / 2;
	while (parent >= top && comp(*(first + parent), value)) {
		*(first + hole) = *(first + parent);
		hole = parent;
		parent = (hole + 1) / 2 - 1;
	}
	*(first + hole) = value;
}

//功能：向下调整hole的位置, 找到合适的位置将value存入

template <class Iterator, typename T, class Compare>
void sinkFix(Iterator first,
	ptrdiff_t len,
	ptrdiff_t hole,
	T value,
	Compare comp)
{
	/* 1.将hole下移到叶子处 */
	ptrdiff_t bigChild = 2 * hole + 2;  //从右孩子开始考虑
	while (bigChild < len) {
		if (comp(*(first + bigChild), *(first + bigChild - 1)))
			bigChild--;  //左孩子大于右孩子
		*(first + hole) = *(first + bigChild);
		hole = bigChild;
		bigChild = 2 * hole + 2;
	}
	if (len % 2 == 0 &&
		bigChild == len) {  //特殊情况：最后一个节点为左节点, 没有兄弟节点
		*(first + hole) = *(first + bigChild - 1);
		hole = bigChild - 1;
	}
	/* 2.转化为向上调整问题 */
	siftFix(first, 0, hole, value, comp);
}