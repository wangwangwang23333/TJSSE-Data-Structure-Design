#pragma once
#include "Algorithm.h"
#include<cstring>

//结构体，记录排序比较次数和交换次数
struct sortData
{
	long long move = 0;
	long long compare = 0;
};

//选择排序
void selectSort(int *p, int n, sortData& sort)
{
	for (int i = 0; i < n; ++i) 
	{
		int min = i;
		for (int j = i + 1; j < n; ++j) 
		{
			if (p[j] < p[min]) 
				min = j;
			++sort.compare;
		}
		if (min != i) 
		{
			mySTL::swap(p[i], p[min]);
			sort.move += 3;
		}
	}
}

static void fixHeap(int *heap, int end, int i, sortData &sort)
{  //堆调整(最大堆)
	int child = 2 * i + 1;
	while (child < end)
	{
		if (child + 1 < end)
		{
			++sort.compare;
			if (heap[child] < heap[child + 1]) child++;  // 找较大的子节点
		}
		++sort.compare;
		if (heap[i] > heap[child])
			break;
		mySTL::swap(heap[i], heap[child]);
		sort.move += 3;
		i = child;
		child = 2 * i + 1;
	}
}

//堆排序
void HeapSort(int *p, int n, sortData &sort)
{
	for (int i = (n - 2) / 2; i >= 0; i--)  //堆化,从倒数第二层(向上)开始修复
		fixHeap(p, n, i, sort);

	for (int i = n - 1; i >= 1; i--) 
	{
		mySTL::swap(p[i], p[0]);        //将最大的元素放在最后
		sort.move += 3;          //
		fixHeap(p, i, 0, sort);  //调整剩下的堆
	}
}




//冒泡排序
void bubbleSort(int *p, int n, sortData& sort)
{
	bool disordered = true;
	for (int i = n - 1; i >= 0 && disordered; --i) {
		disordered = false;
		for (int j = 0; j < i; ++j) {
			if (p[j] > p[j + 1]) {
				mySTL::swap(p[j], p[j + 1]);
				sort.move += 3;
				disordered = true;
			}
			++sort.compare;
		}
	}
}

// 快排递归函数
static void _quickSort(int *a, int begin, int end, sortData &data)
{
	if (end - begin < 2)
		return;
	int i = begin, j = end - 1;
	//三路取中优化
	int mid = (i + j) / 2, k = i;
	if (a[mid] < a[k])
		k = mid;
	if (a[j] < a[k])
		k = j;
	if (k != j)
		mySTL::swap(a[k], a[j]);//三者最小值放到最右端
	if (a[mid] < a[i])
		mySTL::swap(a[mid], a[i]);//次小值放最左端

	//哨兵
	int pivot = a[i];
	while (i != j)
	{
		while (i < j && (++data.compare, a[j] >= pivot)) j--;
		a[i] = a[j];
		++data.move;
		while (i < j && (++data.compare, a[i] <= pivot)) i++;
		a[j] = a[i];
		++data.move;
	}
	a[i] = pivot;
	++data.move;
	_quickSort(a, begin, i, data);
	_quickSort(a, i + 1, end, data);
}

//快速排序
void quickSort(int *a, int n, sortData &data) 
{ 
	_quickSort(a, 0, n, data); 
}



//直接插入排序
void straightInsertSort(int *p, int n, sortData& sort)
{
	for (int i = 1; i < n; i++) 
	{
		int temp = p[i];
		++sort.move;  
		int j = i;
		while (j > 0 && (++sort.compare, temp < p[j - 1])) {  //
			p[j] = p[j - 1];
			++sort.move;  
			j--;
		}
		p[j] = temp;
		++sort.move;  
	}
}

//折半插入排序
void binaryInsertSort(int *p, int n, sortData &sort)
{
	for (int i = 1; i < n; ++i) 
	{
		int begin = 0, end = i;
		int temp = p[i];
		++sort.move;  
		while (begin < end) 
		{
			int mid = (begin + end - 1) / 2;
			if (temp < p[mid])  // a[mid]较大，在左侧找 
				end = mid;
			else  // a[mid]小于或等于temp，在右侧找（等于的时候也在右侧找）
				begin = mid + 1;
			++sort.compare;
		}
		// 至此，a[begin]是大于a[i]的首个值
		for (int k = i - 1; k >= begin; k--)
		{
			p[k + 1] = p[k];
			++sort.move;
		}
		p[begin] = temp;
		++sort.move;  
	}
}

//希尔排序
void ShellSort(int *p, int n, sortData &sort)
{
	int gap = 1;
	while (gap < n / 3) 
		gap = 3 * gap + 1;  // h依次取1,4,13,40,121
	while (gap) 
	{
		for (int i = gap; i < n; i++) 
		{
			int temp = p[i];
			++sort.move;  
			int j = i;
			while (j >= gap && (++sort.compare, temp < p[j - gap])) 
			{  
				p[j] = p[j - gap];
				++sort.move;  
				j -= gap;
			}
			p[j] = temp;
			++sort.move;  
		}
		gap /= 3;
	}
}


static void _merge(int *a, int begin, int mid, int end, int *arr, sortData &data)
{
	for (int k = begin; k < end; k++)
	{
		arr[k] = a[k];
		++data.move;
	}
	int i = begin, j = mid;
	for (int k = begin; k < end; k++)
	{
		if (i >= mid)
			a[k] = arr[j++];
		else if (j >= end)
			a[k] = arr[i++];
		else
		{
			++data.compare;
			if (arr[j] < arr[i])
				a[k] = arr[j++];
			else
				a[k] = arr[i++];
		}
		++data.move;
	}
}

static void _mergeSort(int *a, int begin, int end, int *arr, sortData &data)
{
	if (end - begin <= 1)
		return;
	int mid = (begin + end) / 2;
	_mergeSort(a, begin, mid, arr, data);
	_mergeSort(a, mid, end, arr, data);
	_merge(a, begin, mid, end, arr, data);
}


//归并排序
void mergeSort(int *p, int n, sortData& data)
{
	int *arr = new int[n];
	_mergeSort(p, 0, n, arr, data);
	delete[] arr;
}





static void _MSDRadixSort(int *, int, int, int, sortData &);
static int getDigitBase10(int, int);
static int getDigitBase16(int, int);

const int radix = 16;

void MSDRadixSort(int *a, int n, sortData &time)
{
	int max = -1000000000, maxd = -1;
	for (int i = 0; i < n; i++)
		if (a[i] > max) max = a[i];
	while (max) {
		max >>= 4;
		maxd++;
	}
	_MSDRadixSort(a, 0, n, maxd, time);
}

static void _MSDRadixSort(int *a, int begin, int end, int d, sortData &time)
{
	const int n = end - begin;
	if (n <= 1 || d < 0) return;
	int *aux = new int[n];
	int *count = new int[radix];
	memset(count, 0, radix * sizeof(int));
	for (int i = begin; i < end; i++) count[getDigitBase16(a[i], d)]++;
	for (int i = 1; i < radix; i++) count[i] += count[i - 1];  //前缀和
	for (int i = begin; i < end; i++)
		aux[--count[getDigitBase16(a[i], d)]] = a[i];
	memcpy(a + begin, aux, n * sizeof(int));
	time.move += 2 * n;  //
	for (int i = 0; i < radix; i++) {
		_MSDRadixSort(a, begin + count[i],
			begin + (i == radix - 1 ? n : count[i + 1]), d - 1,
			time);  //递归
	}
	delete[] count;
	delete[] aux;
}

void LSDRadixSort(int *a, int n, sortData &time)
{
	int max = -1000000000, maxd = -1;
	for (int i = 0; i < n; i++)
		if (a[i] > max) max = a[i];
	while (max) {
		max >>= 4;
		maxd++;
	}
	int *aux = new int[n];
	int *count = new int[radix];
	for (int d = 0; d <= maxd; d++) {
		memset(count, 0, radix * sizeof(int));
		for (int i = 0; i < n; i++) count[getDigitBase16(a[i], d)]++;
		for (int i = 1; i < radix; i++) count[i] += count[i - 1];  //前缀和
		for (int i = n - 1; i >= 0; i--)
			aux[--count[getDigitBase16(a[i], d)]] = a[i];
		memcpy(a, aux, n * sizeof(int));
		time.move += 2 * n;  //
	}
	delete[] count;
	delete[] aux;
}

static int getDigitBase10(int x, int d)  // unused
{
	while (d--) x /= 10;
	return x % 10;
}

static int getDigitBase16(int x, int d) { return x >> (d << 2) & 0xF; }

//桶排序
void bucketSort(int arr[], int n, sortData& data)
{
	int i, j;
	int *buckets = new int[n + 1];

	for (i = 0; i < n + 1; i++) // 清零
		buckets[i] = 0;
	// 1.计数,将数组arr中的元素放到桶中
	for (i = 0; i < n; i++)
		buckets[arr[i]]++; // 将arr[i]的值对应buckets数组的下标，每有一个就加1
	// 2.排序
	for (i = 0, j = 0; i < n + 1; i++) {
		while (buckets[i] > 0) { // 说明存有元素,相同的整数，要重复输出
			arr[j] = i;
			buckets[i]--;
			j++;
		}
	}
	delete[] buckets;
}