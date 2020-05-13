#ifndef __Count_SORTT_H__
#define __Count_SORTT_H__

template <class ElemType>
void CountSort(ElemType elem[], int n)
{
	int max = 1000;
	int C[1000000] = {0};
	ElemType temp[1000000];
	for (int m = 0; m < n; m++)
		temp[m] = elem[m];
	for (int i = 0; i < n; ++i)
        ++C[temp[i]];
    for (int i = 1; i <= max; ++i)
        C[i] += C[i-1];
    for (int i = n-1; i >= 0; --i)
        elem[--C[temp[i]]] = temp[i];
}

#endif