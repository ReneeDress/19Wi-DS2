#include "Assistance.h"					// 辅助软件包
#include "ChildParentTree.h"			// 孩子双亲表示树类

void menu()
{
	cout << "=======		1	先根序遍历树		=======" << endl;
	cout << "=======		2	后根序遍历树		=======" << endl;
	cout << "=======		3	层次遍历树		=======" << endl;
	cout << "=======		4	树的高			=======" << endl;
	cout << "=======		5	树的度			=======" << endl;
	cout << "=======		6	树的叶子数		=======" << endl;
	cout << "=======		7	层次遍历二叉树		=======" << endl;
	return;
}

int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		char items[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
		int parents[] = {-1, 0, 0, 0, 1, 1, 3, 3};
		//char items[] = {'A', 'B', 'E', 'C', 'F', 'D', 'G', 'H'};
		//int parents[] = {-1, 0, 1, 1, 2, 3, 5, 6};
		int r = 0, n = 8, cur;
		ChildParentTree<char> t(items, parents, r, n);
		cout << "树:";
		DisplayTWithConcaveShape(t);
		cout << endl;
 
		menu();
		char input;
		while (cin >> input)
		{
			switch(input)
			{
				case '1' :
				cout << "先根序遍历树: ";
				t.PreRootOrder(Write);
				cout << endl;
				break;
				case '2' :
				cout << "后根序遍历树: ";
				t.PostRootOrder(Write);
				cout << endl;
				break;
				case '3' :
				cout << "层次遍历树: ";
				t.LevelOrder(Write);
				cout << endl;
				break;
				case '4' :
				cout << "树的高: ";
				cout << t.Height();
				cout << endl;
				break;
				case '5' :
				cout << "树的度: ";
				cout << t.Degree();
				cout << endl;
				break;
				case '6' :
				cout << t.CountLeaves();
				cout << endl;
				break;
				case '7' :
				cout << "层次遍历二叉树: ";
				t.BinaryLevelOrder(Write);
				cout << endl;
				break;
			}
			menu();
		}
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	//system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}



