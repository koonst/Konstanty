#pragma once

#include <algorithm>

template<typename T>
void mergeWrap(T* tab, T* tmp, int left, int right, int maxdepth);

template<typename T>
void merge(T* tab, T* tmp, int left, int midd, int right)
{
	for (int i = left; i <= right; i++) tmp[i] = tab[i];

	int i = left;
	int j = midd + 1;
	int q = left;

	while (i <= midd && j <= right)
	{
		if (tmp[i] < tmp[j]) tab[q++] = tmp[i++];
		else tab[q++] = tmp[j++];
	}
	while (i <= midd) tab[q++] = tmp[i++];
}


template<typename T>
void mergesort(T* tab, T* tmp, int left, int right)
{
	if (left < right)
	{
		int midd = (left + right) / 2;
		mergesort(tab, tmp, left, midd);
		mergesort(tab, tmp, midd + 1, right);
		merge(tab, tmp, left, midd, right);
	}
}


template<typename T>
void mergeWrap(T* tab, T* tmp, int left, int right, int maxdepth)
{
	mergesort(tab, tmp, left, right);
}

template void mergeWrap<int>(int*, int*, int, int, int);