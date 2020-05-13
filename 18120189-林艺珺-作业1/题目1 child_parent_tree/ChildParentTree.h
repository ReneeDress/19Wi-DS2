#ifndef __CHILD_PARENT_TREE_H__
#define __CHILD_PARENT_TREE_H__

#include "LinkQueue.h"				// 链队列
#include "ChildParentTreeNode.h"	// 孩子双亲表示树结点类

// 孩子双亲表示树类
template <class ElemType>
class ChildParentTree
{
public:
//protected:
//  树的数据成员:
	ChildParentTreeNode<ElemType> *nodes;			// 存储树结点
	int maxSize;									// 树结点最大个数 
	int root, num;									// 根的位置及结点数

//	辅助函数:
	void PreRootOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// 先根序遍历
	void PostRootOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// 后根序遍历
	int HeightHelp(int r) const;					// 返回以r为根的高
	int DegreeHelp(int r) const;					// 返回以r为根的树的度

//public:
//  树方法声明及重载编译系统默认方法声明:
	ChildParentTree();								// 无参构造函数
	virtual ~ChildParentTree();						// 析构函数
	int GetRoot() const;							// 返回树的根
	bool Empty() const;								// 判断树是否为空
	Status GetElem(int cur, ElemType &e) const;	// 用e返回结点元素值
	Status SetElem(int cur, const ElemType &e);	// 将结cur的值置为e
	void PreRootOrder(void (*Visit)(const ElemType &)) const;	// 树的先序遍历
	void PostRootOrder(void (*Visit)(const ElemType &)) const;	// 树的后序遍历
	void LevelOrder(void (*Visit)(const ElemType &)) const;		// 树的层次遍历
	int NodeCount() const;							// 返回树的结点个数
	int NodeDegree(int cur) const;					// 返回结点cur的度
	int Degree() const;								// 返回树的度
	int FirstChild(int cur) const;					// 返回结点cur的第一个孩子
	int RightSibling(int cur) const;				// 返回结点cur的右兄弟
	int Parent(int cur) const;						// 返回结点cur的双亲
	Status InsertChild(int cur, int i, const ElemType &e);	
		// 将数据元素插入为cur的第i个孩子
	int	Height() const;								// 返回树的高
	ChildParentTree(const ElemType &e, int size = DEFAULT_SIZE);
		// 建立以数据元素e为根的树
	ChildParentTree(ElemType items[], int parents[], int r, int n, int size = DEFAULT_SIZE);
		// 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树

	int CountLeaves();
	void BinaryLevelOrder(void (*Visit)(const ElemType &)) const;
};

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentTree<ElemType> &t, int r, int level);
	// 按凹入表示法显示树，level为层次数，设根结点的层次数为1
template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentTree<ElemType> &t);
	// 按凹入表示法显示树

// 孩子双亲表示树类的实现部分
template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree()
// 操作结果：构造一个空树
{
	maxSize = DEFAULT_SIZE;								// 树结点最大个数
	nodes = new ChildParentTreeNode<ElemType>[maxSize];	// 分配存储空间
	root = -1;											// 表示不存在根
	num = 0;											// 空树的结点个数为0
}

template <class ElemType>
ChildParentTree<ElemType>::~ChildParentTree()
// 操作结果：释放存储空间
{
    Node<int> *p;
    for (int n = 0; n < num; n++) {
       p = nodes[n].childLkList;
       while ( p!= NULL) {
          nodes[n].childLkList = p->next;
          delete p;
          p = nodes[n].childLkList;
       }
    }   
	delete []nodes;										// 释放存储空间
}



template <class ElemType>
int ChildParentTree<ElemType>::GetRoot() const
// 操作结果：返回树的根
{
	return root;
}

template <class ElemType>
bool ChildParentTree<ElemType>::Empty() const
// 操作结果：判断树是否为空
{
	return num == 0;
}

template <class ElemType>
Status ChildParentTree<ElemType>::GetElem(int cur, ElemType &e) const
// 操作结果：用e返回结点cur元素值,如果不存在结点cur,函数返回NOT_PRESENT,否则返回ENTRY_FOUND
{
	if (cur < 0 || cur >= num)		// 不存在结点cur
		return NOT_PRESENT;			// 返回NOT_PRESENT
	else {	                        // 存在结点cur
		e = nodes[cur].data;		// 用e返回元素值
		return ENTRY_FOUND;			// 返回ENTRY_FOUND
	}
}

template <class ElemType>
Status ChildParentTree<ElemType>::SetElem(int cur, const ElemType &e)
// 操作结果：如果不存在结点cur,则返回FAIL,否则返回SUCCESS,并将结点cur的值设置为e
{
	if (cur < 0 || cur >= num)		// 不存在结点cur
		return FAIL;				// 返回FAIL
	else	{	                    // 存在结点cur
		nodes[cur].data = e;		// 将结点cur的值设置为e
		return SUCCESS;	  		    // 返回SUCCESS
	}
}

template <class ElemType>
void ChildParentTree<ElemType>::PreRootOrderHelp(int r, void (*Visit)(const ElemType &)) const
// 操作结果：按先根序依次对以r为根的树的每个元素调用函数(*visit)
{
	if (r >=0 && r < num)	{	// r范围合法
		(*Visit)(nodes[r].data);			// 访问根结点
		for (int child = FirstChild(r); child != -1; child = RightSibling(child))
			PreRootOrderHelp(child, Visit);// 依次先根序遍历每棵子树
	}
}

template <class ElemType>
void ChildParentTree<ElemType>::PreRootOrder(void (*Visit)(const ElemType &)) const
// 操作结果：按先根序依次对树的每个元素调用函数(*visit)
{
	PreRootOrderHelp(GetRoot(), Visit);		// 调用辅助函数实现后先序遍历
}

template <class ElemType>
void ChildParentTree<ElemType>::PostRootOrderHelp(int r, void (*Visit)(const ElemType &)) const
// 操作结果：按后根序依次对以r为根的树的每个元素调用函数(*visit)
{
	if (r >=0 && r < num)	{	// r范围合法
		for (int child = FirstChild(r); child != -1; child = RightSibling(child))
			PostRootOrderHelp(child, Visit);// 依次后根序遍历每棵子树
		(*Visit)(nodes[r].data);			// 访问根结点
	}
}

template <class ElemType>
void ChildParentTree<ElemType>::PostRootOrder(void (*Visit)(const ElemType &)) const
// 操作结果：按后根序依次对树的每个元素调用函数(*visit)
{
	PostRootOrderHelp(GetRoot(), Visit);	// 调用辅助函数实现后根序遍历
}

template <class ElemType>
void ChildParentTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历树
{
	LinkQueue<int> q;	// 队列
	int cur = root;		// 从根结点开始进行层次遍历
	
	if (cur >= 0 || cur < num)
       q.EnQueue(cur);	// 如果根合法,则入队
	while (!q.IsEmpty())	{	// q非空,说明还有结点未访问
		q.DelQueue(cur);						// 出队
		(*Visit)(nodes[cur].data);				// 访问当前结点
		for (int child = FirstChild(cur); child != -1; child = RightSibling(child))
			q.EnQueue(child);					// 依次将cur的孩子入列
	}
}

template <class ElemType>
int ChildParentTree<ElemType>::HeightHelp(int r) const
// 操作结果：返回以r为根的树的高
{
    int child, h, maxSubTreeHeight = 0;
	if (r < 0 || r >= num)
		return 0;
	else	{
		for (child = FirstChild(r); child != -1; child = RightSibling(child)) {
			h = HeightHelp(child);			// 求各子树的高
			maxSubTreeHeight = (maxSubTreeHeight < h) ? h : maxSubTreeHeight;
				// 求各子树高的最大值
		}
		return maxSubTreeHeight + 1;			// 树高为各子树的最大值再加1
	}
}

template <class ElemType>
int ChildParentTree<ElemType>::Height() const
// 操作结果：返回树的高
{
	return HeightHelp(root);					// 调用辅助函数实现返回树的高
}

template <class ElemType>
int ChildParentTree<ElemType>::NodeCount() const
// 操作结果：返回树的结点个数
{
	return num;
}

template <class ElemType>
int ChildParentTree<ElemType>::NodeDegree(int cur) const
// 操作结果：返回结点cur的度
{
	int d = 0;						// 临时变量,用于对孩子个数进行计数
	for (int child = FirstChild(cur); child != -1; child = RightSibling(child))
		d++;						// 对孩子个数进行计数
	return d;
}

template <class ElemType>
int ChildParentTree<ElemType>::DegreeHelp(int r) const
// 操作结果：返回以r为根的树的度
{

	int d = 0;						// 用于统计结点r的孩子个数
	int maxSubTreeDegree = 0;		// 子树中度的最大值
	for (int child = FirstChild(r); child != -1; child = RightSibling(child)) { 
		d++;						// 对r的孩子个数进行计数
		int subTreeDegree = DegreeHelp(child);	// 子树的度
		maxSubTreeDegree = (maxSubTreeDegree < subTreeDegree) ? subTreeDegree : maxSubTreeDegree;
			// 求子树度最大值
	}
	return (d < maxSubTreeDegree) ? maxSubTreeDegree : d;
}

template <class ElemType>
int ChildParentTree<ElemType>::Degree() const
// 操作结果：返回树的度
{
	return DegreeHelp(root);
}

template <class ElemType>
int ChildParentTree<ElemType>::FirstChild(int cur) const
// 操作结果：如cur无孩子,则返回-1,否则返回树结点cur的第一个孩子,
{
    Node<int> *p;
	if (cur < 0 || cur >= num)	
		return -1;						// 结点cur不存在,返回-1表示无孩子
	
	if (nodes[cur].childLkList == NULL)	// 无孩子
		return -1;
	else
		return nodes[cur].childLkList->data;	// 取出第一个孩子
}

template <class ElemType>
int ChildParentTree<ElemType>::RightSibling(int cur) const
// 操作结果：如果结点cur无右兄弟,则返回-1,否则返回cur的右兄弟
{
	if (cur < 0 || cur >= num)						
		return -1;						// 结点cur不存在,返回-1表示无孩子

	int pt = nodes[cur].parent;			// cur的双亲
    Node<int> * p = nodes[pt].childLkList;
    while (p != NULL && p->data != cur)
       p = p->next;
    if ( p == NULL || p->next == NULL)
		return -1;				// 表示无右兄弟
	else
		return p->next->data;	// 反回右兄弟
}

template <class ElemType>
int ChildParentTree<ElemType>::Parent(int cur) const
// 操作结果：返回树结点cur的双亲
{
	if (cur < 0 || cur >= num)						
		return -1;						// 结点cur不存在,返回-1表示无双亲
	return nodes[cur].parent;
}

template <class ElemType>
Status ChildParentTree<ElemType>::InsertChild(int cur, int i, const ElemType &e)
// 操作结果：将数据元素插入为cur的第i个孩子,如果插入成功,则返回SUCCESS,否则返回FAIL
{
	if (cur < 0 || cur >= num)
       return FAIL;
	if (i < 1 || i > NodeDegree(cur) + 1)
       return FAIL;
    if (num == maxSize)
       return FAIL;
	nodes[num].data = e;			// 将结点child的的数据元素值赋为e
	nodes[num].parent = cur;		// 结点child的双亲为cur
	nodes[num].childLkList = NULL;  // 双亲的孩子链表
	Node<int> *p, *q, *newnode;
	if (i == 1) {
	   newnode = new Node<int>(num, nodes[cur].childLkList);
	   nodes[cur].childLkList = newnode;
    }
    else {
       p =  nodes[cur].childLkList;  
	   for (int n = 1; n < i-1; n++)
	      p = p->next;
	   newnode = new Node<int>(num, p->next);
	   p->next = newnode;
    }   
	num++;											// 插入成功,结点数自加1
	return SUCCESS;
}

template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree(const ElemType &e, int size)
// 操作结果：建立以数据元素e为根的树
{
	maxSize = size;							// 树结点最大个数
	nodes = new ChildParentTreeNode<ElemType>[maxSize];	// 分配存储空间
	root = 0;								// 根的位置
	nodes[root].data = e;					// 对数据域进行赋值
	nodes[root].parent = -1;				// 根的双亲为-1
	num = 1;								// 结点个数
}

template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree(ElemType items[], int parents[], int r, int n, int size)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树
{
	maxSize = size;													// 最大结点个数
	if (n > maxSize)	
	    throw Error("结点个数太多!");								// 抛出异常
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// 分配存储空间
	for (int pos = 0; pos < n; pos++)
	{	// 依次对结点数据元素及双亲位置进行赋值
		nodes[pos].data = items[pos];								// 数据元素值
		nodes[pos].parent = parents[pos];							// 双亲位置
		if (parents[pos] != -1)		{
           Node<int> *p, *newnode;
	       newnode = new Node<int>(pos, NULL);
	       if (nodes[parents[pos]].childLkList == NULL)
	          nodes[parents[pos]].childLkList = newnode;
           else {
              p =  nodes[parents[pos]].childLkList;  
	          while (p->next != NULL)
	             p = p->next;
	          p->next = newnode;
            }   
		}
	}
	root = r;														// 根
	num = n;														// 结点个数
}

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentTree<ElemType> &t, int r, int level)
// 操作结果：按凹入表示法显示树，level为层次数，可设根结点的层次数为1
{
	if (r >= 0 && r < t.NodeCount())
	{	// 存在结点r,才显示r的信息
		cout<<endl;													//显示新行	
		for(int i = 0; i< level - 1; i++)
			cout<<" ";												//确保在第level列显示结点
		ElemType e;
		t.GetElem(r, e);											// 取出结点r的元素值
		cout << e;													// 显示结点元素值
		for (int child = t.FirstChild(r); child != -1; child = t.RightSibling(child))
		{	// 依次显示各棵子树
			DisplayTWithConcaveShapeHelp(t, child, level + 1);
		}
	}
}

template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentTree<ElemType> &t)
// 操作结果：按凹入表示法显示树
{
	DisplayTWithConcaveShapeHelp(t, t.GetRoot(), 1);				// 调用辅助函数实现按凹入表示法显示树
	cout << endl;													// 换行
}

template <class ElemType>
int ChildParentTree<ElemType>::CountLeaves()
{
    if (num > maxSize) {return 0;}
    int leafNum = 0;
    cout << "树的叶子结点: ";
    for (int i = 0; i < num; i++)
    {
        Node<int> *p = nodes[i].childLkList;
        if (p == NULL)
        {
            leafNum++;
            cout << nodes[i].data << " ";
        }
    }
    cout << endl;
    cout << "树的叶子数: ";
    return leafNum;
}

/*
template <class ElemType>
void ChildParentTree<ElemType>::BinLevelOrder()
{
    int flag[1000] = {0};
    
    for (int i = 0; i < num; i++)
    {
        if (nodes[i].parent == nodes[i - 1].parent - flag[i - 1])
        {
            flag[i] = i - 1 - nodes[i].parent;
            nodes[i].parent = i - 1;
        }
    }
    ElemType data[num];
    int par[num];
    for (int i = 0; i < num; i++)
    {
        data[i] = nodes[i].data;
        par[i] = nodes[i].parent;
    }
    TYPE temp;
    int ttemp;
	ElemType ndata[num];
    int npar[num];
    for （int i = -1; i < num; i++）
    {
    	for (int j = 0; j < num; j++)
    	if (par[j] == i) 
    }
    
    ChildParentTree<ElemType> BCPT(data, par, 0, num);
    int h[num];
    for (int i = 0; i < num; i++)
    {
    	cout << BCPT.nodes[i].data << " ";
    	cout << BCPT.nodes[i].parent << endl;
    	//cout << h[i] << endl;
    	//cout << BCPT.nodes[i].childLkList->data << endl;
    }
    DisplayTWithConcaveShape(BCPT);
    cout << "BinLevelOrder: ";
    for (int i = -1; i < num; i++)
    {
    	for (int j = num; j >= 0; j--)
    	{
    		if (h[j] == i) cout << BCPT.nodes[j].data << " ";
    	}
    }
    //BCPT.LevelOrder(Write);

}
*/

template <class ElemType>
void ChildParentTree<ElemType>::BinaryLevelOrder(void (*Visit)(const ElemType &)) const
// 操作结果：层次遍历转换的二叉树
{
	LinkQueue<int> q;	// 队列
	int cur = root;		// 从根结点开始进行层次遍历
	
	if (cur >= 0 || cur < num)
       q.EnQueue(cur);						// 如果根合法,则入队
	while (!q.IsEmpty())	{				// q非空,说明还有结点未访问
		q.DelQueue(cur);					// 出队
		(*Visit)(nodes[cur].data);			// 访问当前结点
		int fc = FirstChild(cur);
		if (fc != -1)	//队头元素第一个孩子非空
			q.EnQueue(fc);		//第一个孩子入队
		int rs = RightSibling(cur);
		if (rs != -1)	//队头元素右兄弟非空
			q.EnQueue(rs);	//右兄弟孩子入队
	}
}

#endif
