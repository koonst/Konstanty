#pragma once

#include <algorithm>

template<typename T>
void quickWrap(T* tab, T* tmp, int left, int right, int maxdepth);

template<typename T>
int partition(T* tab, int left, int right)
{
	int pivot = tab[(left + right) / 2], i = left, j = right; //pivot selection is always middle

	while (true)
	{
		while (tab[j] > pivot) j--;

		while (tab[i] < pivot) i++;

		if (i < j)  std::swap(tab[i++], tab[j--]);
		else return j;
	}
}


template<typename T>
void quicksort(T* tab, int left, int right)
{
	if (left < right)
	{
		int q = partition(tab, left, right);
		quicksort(tab, left, q);
		quicksort(tab, q + 1, right);
	}
}


template<typename T>
void quickWrap(T* tab, T* tmp, int left, int right, int maxdepth)
{
	quicksort(tab, left, right);
}

template void quickWrap<int>(int*, int*, int, int, int);