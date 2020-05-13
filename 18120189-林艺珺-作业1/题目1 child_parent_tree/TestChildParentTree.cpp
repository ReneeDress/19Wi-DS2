#include "Assistance.h"					// 辅助软件包
#include "ChildParentTree.h"			// 孩子双亲表示树类

int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		char items[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
		int parents[] = {-1, 0, 0, 0, 1, 1, 3, 3};
		int r = 0, n = 8, cur;
		ChildParentTree<char> t(items, parents, r, n);
		cout << "树:" << endl;
		DisplayTWithConcaveShape(t);
		cout << endl;
		//system("PAUSE");				// 调用库函数system()

		cout << "先根序遍历树:";
		t.PreRootOrder(Write);
		cout << endl;
		cout << "后根序遍历树:";
		t.PostRootOrder(Write);
		cout << endl;
		cout << "层次遍历树:";
		t.LevelOrder(Write);
		cout << endl;
		cout << "树高:";
		cout << t.Height();
		cout << endl;
		cout << "树的度:";
		cout << t.Degree();
		cout << endl;
		int LeafNum = t.CountLeaves();
	    if (t.num <= t.maxSize)
	    {
	        cout << "LeafNum: " << LeafNum << endl;
	    }
		char e;
		t.GetElem(t.GetRoot(), e);
		cout << "结点" << e << "的度:" << t.NodeDegree(t.GetRoot()); 
		cout << endl;
		//system("PAUSE");				// 调用库函数system()

		cur = t.GetRoot();
		e = 'X';
		t.InsertChild(cur, 2, e);

		cur = t.FirstChild(cur);
		e = 'Y';
		t.InsertChild(cur, 1, e);

		cout << "树:" << endl;
		DisplayTWithConcaveShape(t);
		cout << endl;
		//system("PAUSE");				// 调用库函数system()
		
		int p, c;
		p = t.GetRoot();
		c = t.FirstChild(p);
		p = t.Parent(c);
		char pElem, cElem;
		t.GetElem(p, pElem);
		t.GetElem(c, cElem);
		cout << cElem << "双亲是:" << pElem;
		cout << endl;
		LeafNum = t.CountLeaves();
	    if (t.num <= t.maxSize)
	    {
	        cout << "LeafNum: " << LeafNum << endl;
	    }
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	//system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

