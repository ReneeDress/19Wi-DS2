#include "BTree.h"
string absorb;

void Menu(BTree<int> &);

int main()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl 
		 << "       	 	  欢迎测试 B树" << endl 
		 << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		 
	cout << "---------------------------------------------------------" << endl
		 << "请选择测试树类型：" << endl
		 << " a.普通型" << endl
		 << " b.树中每个结点的关键字个数都是1个（三阶的关键字个数下限）" << endl
		 << " c.树中每个结点的关键字个数都是2个（三阶的关键字个数上限）" << endl
		 << " d.树中只有一个结点" << endl
		 << " e.空B树" << endl
		 << " 0.退出" << endl;
		 
	char i;
	while(cin >> i)
	{
		getline(cin, absorb);
		switch(i)
		{
			case 'a':	{int k[] = {41,26,74,82,17,35,53,60,78,87,94};
						BTree<int> d(k,11);
						cout << "树:";
						d.DisplayTree();
						Menu(d);
						break;}
			case 'b':	{int n[] = {69,43,38,47,78,63,56};
						BTree<int> b(n,7);
						cout << "树:";
						b.DisplayTree();
						Menu(b);
						break;}
			case 'c':	{int r[] = {56,34,77,45,27,60,84,32,39,93,102,65,90,108,37,38,43,113,121,100,110,73,63,75,112,130};
						BTree<int> c(r,26);
						cout << "树:";
						c.DisplayTree();
						Menu(c);
						break;}
			case 'd':	{int m[] = {6};
						BTree<int> a(m,1);
						cout << "树:";
						a.DisplayTree();
						Menu(a);
						break;}
			case 'e':	{int l[] ={};
						BTree<int> e(l, 0);
						cout << "树:";
						e.DisplayTree();
						Menu(e);
						break;}
			case '0':	return 0;
		}
		cout << "---------------------------------------------------------" << endl
		 << "请选择测试树类型：" << endl
		 << " a.普通型" << endl
		 << " b.树中每个结点的关键字个数都是1个（三阶的关键字个数下限）" << endl
		 << " c.树中每个结点的关键字个数都是2个（三阶的关键字个数上限）" << endl
		 << " d.树中只有一个结点" << endl
		 << " e.空B树" << endl
		 << " 0.退出" << endl;
	}
}


void Menu(BTree<int> &bt)
{
	cout << "---------------------------------------------------------" << endl
		<< "	请选择测试功能(输入字母或符号)：" << endl 
		<< " 	 a.查找" << endl 
		<< " 	 b.插入" << endl 
		<< " 	 c.删除" << endl
		<< " 	 d.重新选择测试树类型" << endl;
		
	int k;
	char o;
	BTreeNode<int> *cur;
	int kn;
	while(cin >> o)
	{
		getline(cin, absorb);
		switch(o)
		{
			case 'a': 	{cout << "输入要查找的树中元素k：";
						cin >> k;
						getline(cin, absorb);
						if(bt.Find(k,kn,cur)==SUCCESS)
						{
							cout << "元素" << k << "在结点 ";
							bt.ShowBTNode(cur); 
							cout << " 中的第" << kn << "个元素位置" << endl;
						}
						else
							cout << "树中没有要查找的元素" << endl;
						cout << endl;
						break;}
			case 'b':	{cout << "输入要插入的元素：";
						cin >> k;
						getline(cin, absorb);
						bt.Insert(k);
						bt.DisplayTree();
						cout << endl;
						break;}
			case 'c':	{cout << "输入要删除的元素";
						cin >> k;
						getline(cin, absorb);
						bt.Delete(k);
						bt.DisplayTree();
						cout << endl;
						break;}
			case 'd':	return;		
		}
		cout << "---------------------------------------------------------" << endl
		<< "	请选择测试功能(输入字母或符号)：" << endl 
		<< " 	 a.查找" << endl 
		<< " 	 b.插入" << endl 
		<< " 	 c.删除" << endl
		<< " 	 d.重新选择测试树类型" << endl;
	}
}