#include "Assistance.h"					// 实用程序软件包
#include "ChildSiblingTree.h"			// 孩子兄弟表示树类
#include <string>

void menu()
{
	cout << "=======		1	先根序遍历树		=======" << endl;
	cout << "=======		2	后根序遍历树		=======" << endl;
	cout << "=======		3	层次遍历树		=======" << endl;
	cout << "=======		4	树的高			=======" << endl;
	cout << "=======		5	树的度			=======" << endl;
	cout << "=======		6	转换二叉树的高		=======" << endl;
	cout << "=======		7	度数1结点数量		=======" << endl;
	return;
}

int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		//char items[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
		string items[] = {"李", "李三", "李一", "李某", "李家", "李六", "李五", "李啊"};
		int parents[] = {-1, 0, 0, 0, 1, 1, 3, 3};
		int r = 0, n = 8, cur;
		ChildSiblingTree<string> t(items, parents, n);
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
				cout << "转换二叉树的高: ";
				cout << t.BinDepth(t.root);
				cout << endl;
				break;
				case '7' :
				cout << "度数为1的结点的数量: ";
				cout << t.DegreeOne();
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

