#include "sort_algorithms.h"


/**************
*             *
* MERGE SORT  *
*             *
**************/
template<typename T>
void merge(T *tab, T *tmp, int left, int midd, int right)
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
void mergesort(T *tab, T *tmp, int left, int right)
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
void mergeWrap(T *tab, T *tmp, int left, int right, int maxdepth)
{
    mergesort(tab, tmp, left, right);
}


/**************
*             *
* QUICK SORT  *
*             *
**************/
template<typename T>
int partition(T *tab, int left, int right)
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
void quicksort(T *tab, int left, int right)
{
    if (left < right)
    {
        int q = partition(tab, left, right);
        quicksort(tab, left, q);
        quicksort(tab, q + 1, right);
    }
}


template<typename T>
void quickWrap(T *tab, T *tmp, int left, int right, int maxdepth)
{
    quicksort(tab, left, right);
}


/*****************
*                *
* INSERTION SORT *
*                *
******************/
template<typename T>
void insertionsort(T *tab, int left, int right)
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


/************
*           *
* HEAP SORT *
*           *
************/
template<typename T>
void heapsort(T *left, T *right)
{
	std::make_heap(left, right);
	std::sort_heap(left, right);
}


/**************
*             *
* INTRO SORT  *
*             *
**************/
template<typename T>
void introsort(T *tab, T *left, T *right, int maxdepth)
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
void introWrap(T *tab, T *tmp, int left, int right, int maxdepth)
{
    introsort(tab, tab, tab + right , maxdepth);
}


template void introWrap<int>(int*, int*, int, int, int);
template void mergeWrap<int>(int*, int*, int, int, int);
template void quickWrap<int>(int*, int*, int, int, int);

template void introWrap<double>(double*, double*, int, int, int);
template void mergeWrap<double>(double*, double*, int, int, int);
template void quickWrap<double>(double*, double*, int, int, int);
