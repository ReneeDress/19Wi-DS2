#include "Assistance.h"
#include "TriHeapSort.h"
#include "HeapSort.h"
#include<ctime>

string absorb;

int main()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl 
		 << "       	 	  欢迎测试 三叉堆排序算法" << endl 
		 << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		 
	cout << "---------------------------------------------------------" << endl
		 << "请选择测试树类型：" << endl
		 << " a.普通型" << endl
		 << " b.满三叉树的最大堆 正序" << endl
		 << " c.满三叉树的最大堆 逆序" << endl
		 << " d.100个随机数三叉堆排序（与原有堆排序算法对比）" << endl
		 << " e.1000个随机数三叉堆排序（与原有堆排序算法对比）" << endl
		 << " 0.退出" << endl;
		 
	char i;
    clock_t starttime,endtime;
	while(cin >> i)
	{
		getline(cin, absorb);
		switch(i)
		{
			case 'a':	{int k[] = {55, 63, 21, 72, 63, 38, 16, 46, 92, 87, 100, 12};
                        int kk = 12;
                        TriHeapSort(k, kk);
                        break;}
			case 'b':	{int l[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
                        int ll = 13;
                        TriHeapSort(l, ll);
                        break;} 
			case 'c':	{int m[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
                        int mm = 13;
                        TriHeapSort(m, mm);
                        break;}
			case 'd':	{int nn = 100;
                        int n[nn];
                        for(int j=0;j<nn;++j)
                            n[j]=rand()%100;
                        starttime=clock();
                        TriHeapSort(n,nn); // 三叉堆排序
                        endtime=clock();
                        cout << nn << "个数组成的三叉堆排序需要" << (double)(endtime-starttime)/CLOCKS_PER_SEC << "s" << endl << endl;
						starttime=clock();
                        HeapSort(n,nn); // 堆排序
                        endtime=clock();
                        cout << nn << "个数组成的原有堆排序算法需要" << (double)(endtime-starttime)/CLOCKS_PER_SEC << "s" << endl << endl;
                        break;}
			case 'e':	{int rr = 1000;
                        int r[rr];
                        for (int j = 0; j < rr; ++j)
                            r[j] = rand() % 100;
                        starttime = clock();
                        TriHeapSort(r, rr); // 三叉堆排序
                        endtime = clock();
                        cout << rr << "个数组成的三叉堆排序需要" << (double)(endtime - starttime) / CLOCKS_PER_SEC << "s" << endl << endl;
						starttime=clock();
                        HeapSort(r,rr); // 堆排序
                        endtime=clock();
                        cout << rr << "个数组成的原有堆排序算法需要" << (double)(endtime-starttime)/CLOCKS_PER_SEC << "s" << endl << endl;
                        break;}
			case '0':	return 0;
		}
        cout << "---------------------------------------------------------" << endl
            << "请选择测试树类型：" << endl
            << " a.普通型" << endl
            << " b.满三叉树的最大堆 正序" << endl
            << " c.满三叉树的最大堆 逆序" << endl
            << " d.100个随机数三叉堆排序（与原有堆排序算法对比）" << endl
            << " e.1000个随机数三叉堆排序（与原有堆排序算法对比）" << endl
            << " 0.退出" << endl;
	}
}