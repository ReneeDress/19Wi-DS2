#ifndef TRIHEAP_H
#define TRIHEAP_H

template<class ElemType>
class TriHeap
{
private:
	ElemType *TriheapArr;
	int CurrentSize;
	int MaxSize;

public :
	TriHeap(int maxSize);
	TriHeap(ElemType a[],int maxsize,int n);
	~TriHeap(){delete []TriheapArr;}
    void Traverse(void (*Visit)(const ElemType &)) const;
	void FilterDown(int Start, int End);
	void FilterUp(int End);
	void TriSwap(int m, int n) { Swap(TriheapArr[m], TriheapArr[n]); }
};

template<class ElemType>
TriHeap<ElemType>::TriHeap(int maxSize)
{
    if (maxSize <= 0)		{
	    cerr << "堆的大小不能小于1" << endl;
        exit(1);
    }
	MaxSize = maxSize;
	TriheapArr = new ElemType[MaxSize];
	CurrentSize = 0;
}

template<class ElemType>
TriHeap<ElemType>::TriHeap(ElemType *a,int maxSize,int n)
{
	if(n <= 0)	{
	    cerr << "堆的大小不能小于1" << endl;
        exit(1);
    }
	MaxSize = maxSize;
	TriheapArr = new ElemType [MaxSize];
	for (int i = 0; i < n; i++)
        TriheapArr[i] = a[i];
	CurrentSize = n;
	int i = (CurrentSize - 1) / 3;
	while(i >= 0)	{
        FilterDown(i,CurrentSize - 1);
		i--;
	}
	cout << "初始堆：";
	Traverse(Write<ElemType>);
	cout << endl;
}

template <class ElemType>
void TriHeap<ElemType>::FilterDown(int Start, int End)
{
    int i = Start, j;
    ElemType temp = TriheapArr[i];
    j = 3 * i + 1;
    while(j <= End)		{
        if(j < End && TriheapArr[j] < TriheapArr[j+1])
        {
		    j++;
        	if(j < End && TriheapArr[j] < TriheapArr[j+1])
        		j++;
        }
        if(j < End-1 && TriheapArr[j] >= TriheapArr[j+1] && TriheapArr[j] < TriheapArr[j+2])
            j+=2;
        if(temp >= TriheapArr[j]) break;
        else {
            TriheapArr[i] = TriheapArr[j];
            i = j;
            j = 3*j+1;
        }
    }
    TriheapArr[i] = temp;
}

template<class ElemType>
void TriHeap<ElemType>::FilterUp(int End)
{
	int j = End,i;
	ElemType temp = TriheapArr[j];
	i = (j - 1) / 3;
	while(j > 0)	{
		if (TriheapArr[i] >= temp) break;
		else {
			TriheapArr[j] = TriheapArr[i];
			j = i;
			i = (j - 1) / 3;
		}
		TriheapArr[j] = temp;
	}
}

template<class ElemType>
void TriHeap<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
{
	for(int i = 0; i < CurrentSize; i++)
		(*Visit)(TriheapArr[i]);
}
#endif
