#ifndef TRIHEAPSORT_H
#define TRIHEAPSORT_H
#include "TriHeap.h"

template<class ElemType>
void TriHeapSort(ElemType *elem, int n)
{
    int i, j;
    TriHeap<ElemType> tri(elem, n, n);
    for (i = n - 1; i > 0; --i)
    {
        tri.TriSwap(0, i);
        j = (i-1)/3;
        while(j >= 0)
    	{
            tri.FilterDown(0, i-1);
            j--;
	    }
        if (n <=50)
        {
            cout << "第" << n - i << "趟堆排序结果："; 
            tri.Traverse(Write<ElemType>);
            cout << endl;
        }
    }
    cout << "排序后序列为：";
    tri.Traverse(Write<ElemType>);
    cout << endl;
}

#endif