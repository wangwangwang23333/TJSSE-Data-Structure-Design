#include "sort.h"
#include<cstdio>
#include<algorithm>

#ifndef _CRT_SECURE_NO_WARNINGS
#    define _CRT_SECURE_NO_WARNINGS
#endif

int *array = nullptr, count = 0;

void showSort(const char *name, void(*sortfunc)(int *, int, sortData&))
{
	int *copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	sortData time;

	printf("%-15s", name);
	clock_t start = clock();
	sortfunc(copy, count, time);
	printf("\t%10gms", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("\t%15lld", time.compare);
	printf("\t%15lld\n", time.move);
	// if (!check(copy, count)) printf("Failed");
	delete[] copy;
}

void std_sort(const char *name)
{
	int *copy = new int[count];
	memcpy(copy, array, count * sizeof(int));
	printf("%-16s", name);
	clock_t start = clock();
	std::sort(copy, copy + count);
	printf("%10gms\n", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	delete[] copy;
}

int main()
{
	//展示界面
	printf("**                  排序算法比较                  **\n");
	printf("====================================================\n");
	printf("**                  1.冒泡排序                    **\n");
	printf("**                  2.选择排序                    **\n");
	printf("**                  3.直接插入排序                **\n");
	printf("**                  4.折半插入排序                **\n");
	printf("**                  5.希尔排序                    **\n");
	printf("**                  6.快速排序                    **\n");
	printf("**                  7.堆排序                      **\n");
	printf("**                  8.归并排序                    **\n");
	printf("**                  9.桶排序                      **\n");
	printf("**                  10.MSD基数排序                **\n");
	printf("**                  11.LSD基数排序                **\n");
	printf("====================================================\n");
	printf("\n设置随机数大小：");
	srand((unsigned int)time(NULL));
	scanf("%d", &count);
	//防止数字过大导致程序崩溃
	if (count <= 0 || count > 1e8) 
		return 0;
	printf("生成%d个随机数\n\n", count);
	array = new int[count];

	printf("===============================================================\n");
	//随机序列
	mySTL::randomArray(array, count);
	printf("**                         随机序列                         **\n");
	printf("===============================================================\n");
	printf("算法                    时间           比较次数        移动次数\n");
	if (count < 1e5) 
		showSort("冒泡排序", bubbleSort);
	if (count < 1e5) 
		showSort("选择排序", selectSort);
	if (count < 1e5) 
		showSort("直接插入排序", straightInsertSort);
	if (count < 1e5) 
		showSort("折半插入排序", binaryInsertSort);
	showSort("希尔排序", ShellSort);
	showSort("堆排序", HeapSort);
	showSort("快速排序", quickSort);
	showSort("归并排序", mergeSort);
	showSort("桶排序", bucketSort);
	showSort("MSD基数排序", MSDRadixSort);
	showSort("LSD基数排序", LSDRadixSort);
	std_sort("stl库排序");
	printf("===============================================================\n");

	//升序序列
	mySTL::ascendArray(array, count);
	printf("**                         升序序列                         **\n");
	printf("===============================================================\n");
	printf("算法                    时间           比较次数        移动次数\n");
	if (count < 1e5)
		showSort("冒泡排序", bubbleSort);
	if (count < 1e5)
		showSort("选择排序", selectSort);
	if (count < 1e5)
		showSort("直接插入排序", straightInsertSort);
	if (count < 1e5)
		showSort("折半插入排序", binaryInsertSort);
	showSort("希尔排序", ShellSort);
	showSort("堆排序", HeapSort);
	showSort("快速排序", quickSort);
	showSort("归并排序", mergeSort);
	showSort("桶排序", bucketSort);
	showSort("MSD基数排序", MSDRadixSort);
	showSort("LSD基数排序", LSDRadixSort);
	std_sort("stl库排序");
	printf("===============================================================\n");

	//降序序列
	mySTL::descendArray(array, count);
	printf("**                         降序序列                         **\n");
	printf("===============================================================\n");
	printf("算法                    时间           比较次数        移动次数\n");
	if (count < 1e5)
		showSort("冒泡排序", bubbleSort);
	if (count < 1e5)
		showSort("选择排序", selectSort);
	if (count < 1e5)
		showSort("直接插入排序", straightInsertSort);
	if (count < 1e5)
		showSort("折半插入排序", binaryInsertSort);
	showSort("希尔排序", ShellSort);
	showSort("堆排序", HeapSort);
	showSort("快速排序", quickSort);
	showSort("归并排序", mergeSort);
	showSort("桶排序", bucketSort);
	showSort("MSD基数排序", MSDRadixSort);
	showSort("LSD基数排序", LSDRadixSort);
	std_sort("stl库排序");
	printf("===============================================================\n");


	delete[] array;

	printf("\nEnter to Exit");
	getchar();
	getchar();

	return 0;
}