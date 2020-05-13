#ifndef __Count_SORT_H__
#define __Count_SORT_H__

template <class ElemType>
void CountSort(ElemType elem[], int n)
{
	int C[1000000] = {0};
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (elem[j] < elem[i])
				C[i]++;
	ElemType temp[1000000];
	for (int m = 0; m < n; m++)
		temp[m] = elem[m];

	for (int k = 0; k < n; k++)
	{
		elem[C[k]] = temp[k];
	}
}

#endif