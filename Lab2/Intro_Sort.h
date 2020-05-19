#pragma once

#include <algorithm>
#include "Quick_Sort.h"

template<typename T>
void introWrap(T* tab, T* tmp, int left, int right, int maxdepth);


template<typename T>
void insertionsort(T* tab, int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int key = tab[i];
		int j = i;

		while (j > left && tab[j - 1] > key)
		{
			tab[j] = tab[j - 1];
			j--;
		}
		tab[j] = key;
	}
}

template<typename T>
void heapsort(T* left, T* right)
{
	std::make_heap(left, right);
	std::sort_heap(left, right);
}

template<typename T>
void introsort(T* tab, T* left, T* right, int maxdepth)
{
	if ((right - left) < 16) insertionsort(tab, left - tab, right - tab);
	else if (maxdepth == 0) heapsort(left, right + 1);
	else
	{
		int pivot = partition(tab, left - tab, right - tab);
		introsort(tab, left, tab + pivot, maxdepth - 1);
		introsort(tab, tab + pivot + 1, right, maxdepth - 1);
	}
}

template<typename T>
void introWrap(T* tab, T* tmp, int left, int right, int maxdepth)
{
	introsort(tab, tab, tab + right, maxdepth);
}


template void introWrap<int>(int*, int*, int, int, int);