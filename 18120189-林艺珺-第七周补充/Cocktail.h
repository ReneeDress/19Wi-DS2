#ifndef __Cocktail_SORT_H__
#define __Cocktail_SORT_H__

template <class ElemType>
void CocktailSort(ElemType elem[], int n)
// 操作结果:对数组elem中的n个元素进行鸡尾酒排序
{
    bool finish = false;
    int i = 1;
    while (i < n && !finish)	{
        finish = true;  
		for (int j = 0; j < n - i; j++)
			if (elem[j] > elem[j + 1]) {
				Swap(elem[j], elem[j + 1]);
				finish = false;
            }
        cout << "第" << i << "趟冒泡排序的结果：（大至右但并无小至左）"; 
        Display(elem, n);       // 显示中间结果 
        for (int j = n - 1; j > 0; j--)
            if (elem[j] < elem[j - 1]) {
                Swap(elem[j], elem[j - 1]);
                finish = false;
            }
	    cout << "第" << i << "趟双向冒泡排序的结果：（大至右且小至左）"; 
        Display(elem, n);		// 显示中间结果 
        i++;
	}
}

#endif
