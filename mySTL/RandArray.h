#pragma once
#include<cstdlib>
#include<time.h>
namespace mySTL
{

	//在数组arrays中内产生number个[min,max]区间内的随机数
	void randomArray(int *arrays, int number, unsigned int seed = 0)
	{
		srand(!seed ? seed : (unsigned int)time(NULL));
		for (int i = 0; i < number; ++i)
			arrays[i] = rand() % number;
	}

	//在数组arrays内产生number个升序数
	void ascendArray(int *arrays, int number)
	{
		for (int i = 0; i < number; ++i)
			arrays[i] = i;
	}

	//在数组arrays内产生number个降序数
	void descendArray(int *arrays, int number)
	{
		for (int i = 0; i < number; ++i)
			arrays[i] = number - i;
	}

};