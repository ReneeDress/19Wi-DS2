#ifndef BTREE_H
#define BTREE_H
#include "BTreeNode.h"
#include "LinkQueue.h"
#include <math.h>

template<class ElemType>
class BTree
{
public:
	BTree(ElemType es[], int n);	//构造函数, 数组k有n个数
	~BTree();
	void DestructHelp(BTreeNode<ElemType> *p);	//析构p为根结点的树
	Status Find(ElemType k, int &kn, BTreeNode<ElemType> *&cur);	//在B树中找元素k，cur返回元素的所在结点，kn结点cur中位置
	bool IfOver(BTreeNode<ElemType> *cur);	//判断结点关键字是否超过最大范围
	bool IfUnder(BTreeNode<ElemType> *cur);	//判断结点关键字是否小于最小范围
	void Insert(ElemType k);		//插入元素k
	void NonSplitInsert(ElemType k, int kn, BTreeNode<ElemType> *cur);	//不分裂结点在cur结点 kn指针位置插入元素k
	void Split(BTreeNode<ElemType> *&cur);	//分裂cur结点
	BTreeNode<ElemType> *Parent(BTreeNode<ElemType> *cur);	//已知结点的双亲结点
	bool ParentHelp(BTreeNode<ElemType> *cur, BTreeNode<ElemType> *p, BTreeNode<ElemType> *&q);		//p为根结点的树是否存在cur的双亲结点
	int FindKeyNumInParent(BTreeNode<ElemType> *p);		//已知结点在双亲结点中的位置
	int Height(const BTreeNode<ElemType> *p);
	void Delete(ElemType k);
	bool IfInLeaf(BTreeNode<ElemType> *cur);	//判断结点cur是否是叶子结点
	BTreeNode<ElemType> *LargestReplace(int kn, BTreeNode<ElemType> *cur);
	void DeleteKey(BTreeNode<ElemType> *&cur, int kn);	//删除叶子结点cur中序号为kn元素
	void TakeKey(BTreeNode<ElemType> *&cur);	//非叶子结点向兄弟儿子

	void ShowBTNode(const BTreeNode<ElemType> *cur);
	void Traverse(BTreeNode<ElemType> *&p, void (*Visit)(const BTreeNode<ElemType> *&)) const;	//层序遍历以p为根的B树
	int DisplayTree();

protected:
	BTreeNode<ElemType> *root;
};

template<class ElemType>
BTree<ElemType>::BTree(ElemType es[], int n)
{
	root = new BTreeNode<ElemType>;
	for(int i=0; i<n; i++)
		Insert(es[i]);
}

template<class ElemType>
BTree<ElemType>::~BTree()
{
	DestructHelp(root);
}

template<class ElemType>
void BTree<ElemType>::DestructHelp(BTreeNode<ElemType> *p)
{
	if(p->pointer[0] == NULL)
	{
		delete p;
		return;
	}
	for(int i = 0; i<=p->num; i++)
		DestructHelp(p->pointer[i]);
	delete p;
	return;
}

template<class ElemType>
Status BTree<ElemType>::Find(ElemType k, int &kn, BTreeNode<ElemType> *&cur)
{
	cur = root;
	BTreeNode<ElemType> *p = cur;
	int i;
	if (root == NULL) 	//如果根结点为空
		kn = 0;
	while(cur != NULL)		//不是失败结点
	{
		for(i = 0; i < cur->num; i++)		//结点内查找是否有关键字或确定下一层指针
		{
			if(k == cur->key[i+1])
			{
				kn = i+1;
				return SUCCESS;
			}
			else if(k < cur->key[i+1])
				
				break;
		}	
		p = cur;
		cur = cur->pointer[i];
	}
	cur = p;		//失败时当前指针指向失败结点的上一层
	kn = i;		//失败时序号为指向失败结点的指针序号
	return FAIL;
}	

template<class ElemType>
bool BTree<ElemType>::IfOver(BTreeNode<ElemType> *cur)
{
	if(cur->num <= ORDER-1)
		return false;
	else 
		return true;
}

template<class ElemType>
bool BTree<ElemType>::IfUnder(BTreeNode<ElemType> *cur)
{
	if(cur == NULL)
		return false;
	if(cur->num < (ORDER+1)/2-1)
		return true;
	else
		return false;
}

template<class ElemType>
void BTree<ElemType>::Insert(ElemType k)
{
	int kn;
	BTreeNode<ElemType> *cur = NULL;
	if(Find(k, kn, cur)==FAIL)
	{
		NonSplitInsert(k, kn, cur);
		while(IfOver(cur))		//从插入结点向上分裂，直到符合<ORDER-1
			Split(cur);
	}
	else
		cout << "元素已存在！" << endl;
}

template<class ElemType>
void BTree<ElemType>::NonSplitInsert(ElemType k, int kn, BTreeNode<ElemType> *cur)
{
	for(int i = cur->num; i > kn; i--)
	{
		cur->key[i+1] = cur->key[i];
		cur->pointer[i+1] = cur->pointer[i];
	}
	cur->key[kn+1] = k;
	cur->pointer[kn+1] = NULL;
	cur->num++;
}

template<class ElemType>
void BTree<ElemType>::Split(BTreeNode<ElemType> *&cur)
{
	BTreeNode<ElemType> *p = cur;
	int i = 3, m = 2, j;		//m是要放到双亲结点的序号，i是要放到隔壁结点的开始序号
	cur = Parent(cur);
	int kn = FindKeyNumInParent(p);
	if(cur == NULL)		//如果分裂结点为根结点
	{
		cur = new BTreeNode<ElemType>;
		cur->pointer[0] = p;
		root = cur;
		kn = 0;
	}
	NonSplitInsert(p->key[m], kn, cur);		//将分裂结点中间那个插到双亲结点中
	BTreeNode<ElemType> *q = cur->pointer[kn+1] = new BTreeNode<ElemType>; 
	
	for(j = 1; i <= p->num; i++, j++)		//分裂结点后半部分放到q结点中
	{
		q->key[j] = p->key[i];
		q->pointer[j-1] = p->pointer[i-1];
		p->pointer[i-1] = NULL;
	}
	q->pointer[j-1] = p->pointer[i-1];
	p->pointer[i-1] = NULL;
	
	q->num = p->num-m;
	p->num = m-1;
}

template<class ElemType>
BTreeNode<ElemType> *BTree<ElemType>::Parent(BTreeNode<ElemType> *cur)
{
	BTreeNode<ElemType> *p = root, *q = NULL;
	int i;
	if(cur->num != 0)
	{
		while(p != NULL && cur != NULL)		//不是失败结点或根结点为空
		{
			for(i = 0; i < p->num; i++)		//结点内查找是否有关键字或确定下一层指针
			{
				if(cur == p)
				{
					return q;
				}
				else if(cur->key[1] <= p->key[i+1])
					break;
			}	
			q = p;
			p = p->pointer[i];
		}
	}
	else
	{
		q = p;
		if(ParentHelp(cur, p, q))
			return q;
	}
	return NULL;
}

template<class ElemType>
bool BTree<ElemType>::ParentHelp(BTreeNode<ElemType> *cur, BTreeNode<ElemType> *p, BTreeNode<ElemType> *&q)
{
	for(int i = 0; i<=p->num; i++)
	{
		if(p->pointer[i] == cur)
		{
			q = p;
			return true;
		}
	}
	for(int i = 0; i<=p->num; i++)
		if(p->pointer[i]!=NULL && ParentHelp(cur, p->pointer[i], q))
			return true;
	return false;
}

template<class ElemType>
int BTree<ElemType>::FindKeyNumInParent(BTreeNode<ElemType> *p)
{
	BTreeNode<ElemType> *cur = Parent(p);
	int i;
	if(cur!=NULL)
	{
		for(i = 0; i < cur->num; i++) 
		{
			if(p->key[1] <= cur->key[i+1])
				break;
		}
		return i;
	}
	return -1;
}

template<class ElemType>
int BTree<ElemType>::DisplayTree()
{
	LinkQueue<ElemType> queue;
	BTreeNode<ElemType> *cur = root;
	if(root == NULL)
	{
		cout << "树为空！" << endl;
		return 0;
	}
	queue.EnQueue(*cur);
	int h = Height(root);
	int s[h+1];		//输出换行符用
	for(int i=0; i<h+1; i++)
		s[i] = 0;
	s[0] = 1;
	s[1] = cur->num+1;
	
	while(!queue.IsEmpty())
	{
		
		queue.DelQueue(cur);		//出队
		for(int i = 0; i < Height(cur)*Height(cur)*2; i++)
			cout << " ";
		cout << cur->num << "_" ;
		for(int i = 1; i<=cur->num; i++)
			cout << cur->key[i] << ",";
		
		s[Height(root) - Height(cur)]--;
		if(s[Height(root) - Height(cur)] == 0)
			cout << endl;
		
		for(int i = 0; i<=cur->num && cur->pointer[i] != NULL; i++)	//入队
		{
			queue.EnQueue(*(cur->pointer[i]));
			s[Height(root) - Height(cur)+2] += cur->pointer[i]->num + 1;
		}
	}
	return 0;
}

template<class ElemType>
void BTree<ElemType>::ShowBTNode(const BTreeNode<ElemType> *cur)
{
	cout << cur->num << "_";
	for(int i=1; i<=cur->num; i++)
		cout << cur->key[i] << ",";
}

template<class ElemType>
void BTree<ElemType>::Traverse(BTreeNode<ElemType> *&p, void (*Visit)(const BTreeNode<ElemType> *&)) const
{
	LinkQueue<ElemType> queue;
	queue.EnQueue(*p);
	while(!queue.IsEmpty())
	{
		queue.DelQueue(p);		//出队
		(*Visit)(p);
		for(int i = 0; i<=p->num && p->pointer[i] != NULL; i++)	//入队
			queue.EnQueue(*(p->pointer[i]));
	}
}

template<class ElemType>
int BTree<ElemType>::Height(const BTreeNode<ElemType> *p)
{
	int h = 0;
	while(p!=NULL)
	{
		h++;
		p = p->pointer[0];
	}
	return h;
}

template<class ElemType>
void BTree<ElemType>::Delete(ElemType k)
{
	int kn;
	BTreeNode<ElemType> *cur = NULL;
	if(Find(k, kn, cur)==SUCCESS)
	{
		if(!IfInLeaf(cur))
		{
			cur = LargestReplace(kn, cur);
			kn = cur->num;
		}
		DeleteKey(cur, kn);
		while(IfUnder(cur))
			TakeKey(cur);
	}
	else
		cout << "元素不存在！" << endl;
}

template<class ElemType>
bool BTree<ElemType>::IfInLeaf(BTreeNode<ElemType> *cur)
{
	if(cur->pointer[0] == NULL)
		return true;
	else
		return false;
}

template<class ElemType>
BTreeNode<ElemType> *BTree<ElemType>::LargestReplace(int kn, BTreeNode<ElemType> *cur)
{
	BTreeNode<ElemType> *p = cur;
	if(p->pointer[kn-1]!=NULL)
		p = p->pointer[kn-1];
	while(p->pointer[p->num] != NULL)
		p = p->pointer[p->num];
	cur->key[kn] = p->key[p->num];
	return p;
}

template<class ElemType>
void BTree<ElemType>::DeleteKey(BTreeNode<ElemType> *&cur, int kn)
{
	if(cur->num>=2 && cur == root)
	{
		for(int i = kn; i<cur->num; i++)
			cur->key[i] = cur->key[i+1];
		cur->num--;
	}
	else if(cur->num >=(ORDER+1)/2)
	{
		for(int i = kn; i<cur->num; i++)
			cur->key[i] = cur->key[i+1];
		cur->num--;
	}
	else if(cur->num ==(ORDER+1)/2-1)
	{
		if(cur != root)
		{
			BTreeNode<ElemType> *p = Parent(cur);
			int m = FindKeyNumInParent(cur);
	
			if(m>0 && p->pointer[m-1]->num >=(ORDER+1)/2)	//cur有上一个兄弟结点且关键词树>[m/2]
			{
				for(int i=cur->num+1; i>1; i--)
					cur->key[i] = cur->key[i-1];
				cur->key[1] = p->key[m];
				p->key[m] = p->pointer[m-1]->key[p->pointer[m-1]->num];
				p->pointer[m-1]->num--;
				for(int i = kn+1; i<=cur->num; i++)
					cur->key[i] = cur->key[i+1];
			}
			else if(p->num > m && p->pointer[m+1]->num >=(ORDER+1)/2)	//cur有下一个兄弟结点且关键词树>[m/2]
			{
				cur->key[cur->num+1] = p->key[m+1];
				p->key[m+1] = p->pointer[m+1]->key[1];
				for(int i = 1; i<p->pointer[m+1]->num; i++)
					p->pointer[m+1]->key[i] = p->pointer[m+1]->key[i+1];
				p->pointer[m+1]->num--;
				for(int i = kn; i<cur->num; i++)
					cur->key[i] = cur->key[i+1];
			}
			else	//兄弟结点都借不到关键字，向双亲结点借，并合并兄弟结点
			{
				if(p->num > m)	//合并右兄弟结点
				{
					cur->key[cur->num+1] = p->key[m+1]; //从双亲结点移下关键字
					for(int i = kn; i<=cur->num; i++)	//删除关键字
						cur->key[i] = cur->key[i+1];
					for(int i=1; i <= p->pointer[m+1]->num; i++)	//合并（兄弟结点的所有key移过来）
						cur->key[cur->num+i] = p->pointer[m+1]->key[i];
					cur->num = cur->num + p->pointer[m+1]->num;
					
					delete p->pointer[m+1];
					p->pointer[m+1] = NULL;
					
					for(int i=m+1; i<p->num; i++)	//双亲结点中填上空位
					{
						p->key[i] = p->key[i+1];
						p->pointer[i] = p->pointer[i+1];
					}
					p->pointer[p->num] = NULL;
					p->num--;			
				}
				else if(m!=0)	//合并左兄弟结点
				{
					for(int i=kn; i>1; i++)	//删除关键字
						cur->key[i] = cur->key[i-1]; 
					p->pointer[m-1]->key[p->pointer[m-1]->num+1] = p->key[m]; //从双亲结点移下关键字
					for(int i=1; i<cur->num; i++)	//合并（兄弟结点的所有key移过来）
						p->pointer[m-1]->key[p->pointer[m-1]->num + i+1] = cur->key[i];
					p->pointer[m-1]->num += cur->num;
					
					delete cur;
					cur = p->pointer[m-1];
	
					for(int i=m; i<p->num; i++)	//双亲结点中填上空位
					{
						p->key[i] = p->key[i+1];
						p->pointer[i] = p->pointer[i+1];
					}
					p->pointer[p->num] = NULL;
					p->num--;
				}
				
				if(p == root && p->num==0)
				{
					root = cur;
					delete p;
				}
				cur = Parent(cur);
			}
		}
		else	//根结点为叶子结点
		{
			for(int i = kn; i<cur->num; i++)
				cur->key[i] = cur->key[i+1];
			cur->num--;
			if(cur->num == 0)
			{
				delete cur;
				root = NULL;
			}
		}
			
	}
}

template<class ElemType>
void BTree<ElemType>::TakeKey(BTreeNode<ElemType> *&cur)
{
	BTreeNode<ElemType> *p = Parent(cur);
	int m = FindKeyNumInParent(cur);
	if(m>0 && p->pointer[m-1]->num >=(ORDER+1)/2)	//cur有上一个兄弟结点且关键词树>[m/2]
	{
		cur->num++;
		for(int i=cur->num; i>1; i--)	//cur中所有key和pointer向后移一位
		{
			cur->key[i] = cur->key[i-1];
			cur->pointer[i] = cur->pointer[i-1];
		}
		cur->pointer[1] = cur->pointer[0];
		
		cur->key[1] = p->key[m];	//从双亲结点移一个关键字
		p->key[m] = p->pointer[m-1]->key[p->pointer[m-1]->num];	//cur的兄弟结点移给双亲结点一个最大关键字
		cur->pointer[0] = p->pointer[m-1]->pointer[p->pointer[m-1]->num]; //指针也顺带要过来
		p->pointer[m-1]->num--;
	}
	else if(p->num > m && p->pointer[m+1]->num >=(ORDER+1)/2)	//cur有下一个兄弟结点且关键词树>[m/2]
	{
		cur->num++;
		cur->key[cur->num] = p->key[m+1];	//从双亲结点移一个关键字
		p->key[m+1] = p->pointer[m+1]->key[1];	//cur的兄弟结点移给双亲结点一个最小关键字
		cur->pointer[cur->num] = p->pointer[m+1]->pointer[0];	//指针也顺带要过来
		
		p->pointer[m+1]->pointer[0] = p->pointer[m+1]->pointer[1];	//兄弟结点所有key和pointer向前移一位
		for(int i = 1; i<p->pointer[m+1]->num; i++)
		{
			p->pointer[m+1]->pointer[i] = p->pointer[m+1]->pointer[i+1];
			p->pointer[m+1]->key[i] = p->pointer[m+1]->key[i+1];
		}
		
		p->pointer[m+1]->num--;
	}	
	else	//兄弟结点都借不到关键字，向双亲结点借，并合并兄弟结点
	{	
		if(m!=0)	//合并左兄弟结点
		{
			p->pointer[m-1]->num++;
			p->pointer[m-1]->key[p->pointer[m-1]->num] = p->key[m]; //从双亲结点移下关键字
			
			p->pointer[m-1]->pointer[p->pointer[m-1]->num] = cur->pointer[0];	//合并（兄弟结点的所有key和pointer移过来）
			for(int i=1; i<cur->num; i++)
			{
				p->pointer[m-1]->key[p->pointer[m-1]->num + i] = cur->key[i];
				p->pointer[m-1]->pointer[p->pointer[m-1]->num + i] = cur->pointer[i];
			}
			p->pointer[m-1]->num += cur->num;
			
			delete cur;
			cur = p->pointer[m-1];
			
			for(int i=m; i<p->num; i++)	//双亲结点中填上空位
			{
				p->key[i] = p->key[i+1];
				p->pointer[i] = p->pointer[i+1];
			}
			p->pointer[p->num] = NULL;
			p->num--;
		}
		else if(p->num > m)	//合并右兄弟结点
		{
			cur->num ++;
			cur->key[cur->num] = p->key[m+1];//从双亲结点移下关键字
			
			cur->pointer[cur->num] = p->pointer[m+1]->pointer[0];//合并（兄弟结点的所有key和pointer移过来）
			for(int i=1; i<=p->pointer[m+1]->num; i++)
			{
				cur->key[cur->num+i] = p->pointer[m+1]->key[i];	
				cur->pointer[cur->num+i] = p->pointer[m+1]->pointer[i];
			}
			cur->num = cur->num + p->pointer[m+1]->num;
			
			delete p->pointer[m+1];
			p->pointer[m+1] = NULL;
			
			for(int i=m+1; i<p->num; i++)	//双亲结点中填上空位
			{
				p->key[i] = p->key[i+1];
				p->pointer[i] = p->pointer[i+1];
			}
			p->pointer[p->num] = NULL;
			p->num--;			
		}
		
		if(p == root && p->num==0)
		{
			root = cur;
			delete p;
		}
		cur = Parent(cur);
	}
}



#endif