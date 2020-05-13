#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include "LinkQueue.h"
#include "WordNode.h"
#include <string>
#include <sstream>
using namespace std;

class Dictionary
{
protected:
	WordNode *root;
	WordNode *CopyTree(WordNode *r);	// 复制以r为根的二叉排序树
	void Destroy(WordNode * &r);					// 销毁以r为根的二叉排序树
	void InOrder(WordNode *r, void (*Visit)(const int &)) const;	// 中序遍历以r为根的二叉排序树
	void Print(WordNode *r) const;
	int NodeCount(const WordNode *r) const;// 求以r为根的二叉排序树的结点数
	WordNode *Parent(WordNode *r, const WordNode *p) const;			// 在以r为根的二叉排序树中求p的双亲
	WordNode *Find(const string &word, WordNode *&f) const;	
	WordNode *FindInit(const string &key, WordNode *&f) const;	
	void Delete(WordNode *&p);				// 删除p指向的结点

public:
	Dictionary();									// 无参数的构造函数
	virtual ~Dictionary();							// 析构函数
	WordNode *GetRoot() const;				// 求二叉排序树的根
	bool IsEmpty() const;								// 判断二叉排序树是否为空
	Status SetType(WordNode *p, string &e);
	Status SetPron(WordNode *p, const string &e);
	Status SetChn(WordNode *p, const string &e);
	void InOrder(void (*Visit)(const int &)) const;	// 二叉排序树的中序遍历	
	void Print() const;
	int NodeCount() const;									// 求二叉排序树的结点个数
	WordNode *Find(const string &word) const;  
	WordNode *FindInit(const string &key) const;	// 查找关键字为key的数据元素
	WordNode *Parent(const WordNode *p) const;
	bool Insert(const string &w, string &t, const string &p, const string &c);
	bool Delete(const string &key);						// 删除关键字为key的数据元素
	Dictionary(const Dictionary &copy);	// 复制构造函数
	Dictionary(WordNode *r);				// 建立以r为根的二叉排序树
	Dictionary &operator=(const Dictionary& copy);	// 赋值语句重载
	bool SaveHelp(ofstream &SaveFile, WordNode *r);
	bool Save(char *filename);
};

bool Dictionary::SaveHelp(ofstream &SaveFile, WordNode *r)
{
	if (r != NULL) 	{
		SaveHelp(SaveFile, r->leftChild);	// 中序遍历r的左子树
		SaveFile << r->word << " " << r->type << " " << r->pron << " " << r->chn << endl;
		SaveHelp(SaveFile, r->rightChild);	// 中序遍历r的右子树
	}
	return 1;
}

bool Dictionary::Save(char *filename)
{
	ofstream SaveFile;
	SaveFile.open(filename);
	if(SaveFile.fail())//文件打开失败:返回0
	{
	   return 0;
	}
	SaveHelp(SaveFile, root);
	SaveFile.close();
	return 1;
}

Dictionary::Dictionary()
// 操作结果：构造一个空二叉排序树
{
	root = NULL;
}


Dictionary::~Dictionary()
// 操作结果：销毁二叉排序树--析造函数
{
	Destroy(root);
}


WordNode *Dictionary::GetRoot() const
// 操作结果：返回二叉排序树的根
{
	return root;
}


bool Dictionary::IsEmpty() const
// 操作结果：判断二叉排序树是否为空
{
	return root == NULL;
}

Status Dictionary::SetType(WordNode *p, string &e)
// 操作结果：如果不存在结点p,则返回FAIL,否则返回SUCCESS,并将结点p的值设置为e
{
	if (p == NULL)
		return FAIL;		// 不存在结点p，返回FAIL
	else	{
		p->type = e;
		cout << p->type << endl;
		if (e.length() < 5)
		{
			for (int i = 5; i > e.length(); i--)
			{
				string b = " ";
				e = b + e;
			}
		}
		p->key = p->word + e;
		return SUCCESS;				// 返回SUCCESS
	}
}
Status Dictionary::SetPron(WordNode *p, const string &e)
{
	if (p == NULL)
		return FAIL;		// 不存在结点p，返回FAIL
	else	{
		p->pron = e;				// 存在结点p将结点p的值设置为e
		return SUCCESS;				// 返回SUCCESS
	}
}
Status Dictionary::SetChn(WordNode *p, const string &e)
{
	if (p == NULL)
		return FAIL;		// 不存在结点p，返回FAIL
	else	{
		p->chn = e;				// 存在结点p将结点p的值设置为e
		return SUCCESS;				// 返回SUCCESS
	}
}

void Dictionary::InOrder(WordNode *r, void (*Visit)(const int &)) const
// 操作结果：中序遍历以r为根的二叉排序树
{
	if (r != NULL) 	{
		InOrder(r->leftChild, Visit);	// 中序遍历r的左子树
		cout << r->word << " ";
		//(*Visit)(r->data);				// 访问根结点
		InOrder(r->rightChild, Visit);	// 中序遍历r的右子树
	}
}

void Dictionary::InOrder(void (*Visit)(const int &)) const
// 操作结果：中序遍历二叉排序树
{
	InOrder(root, Visit);	
}	

void Dictionary::Print(WordNode *r) const
{
	if (r != NULL) 	{
		Print(r->leftChild);	// 中序遍历r的左子树
		cout << setfill(' ') << setw(20) << left << r->word;	
		cout << setfill(' ') << setw(5) << left << r->type << "  ";	
		cout << setfill(' ') << setw(30) << left << r->pron;
		cout << setfill(' ') << setw(50) << left << r->chn << endl;				//显示结点
		cout << endl;
		Print(r->rightChild);	// 中序遍历r的右子树
	}
}

void Dictionary::Print() const
{
	cout << endl;
	Print(root);	
}	

int Dictionary::NodeCount(const WordNode *r) const
// 操作结果：求以r为根的二叉排序树的结点个数
{
	if (r ==NULL) 
        return 0;			// 空二叉排序树结点个数为0
	else 
        return 1 + NodeCount(r->leftChild) + NodeCount(r->rightChild);
		// 非空二叉排序树结点个为左右子树的结点个数之和再加1
}


int Dictionary::NodeCount() const
// 操作结果：求二叉排序树的结点个数
{
	return NodeCount(root);
}

WordNode *Dictionary::FindInit(const string &key, WordNode *&f) const
{
	WordNode *p = GetRoot();	// 指向当前结点
	f = NULL;								// 指向p的双亲

	while (p != NULL && key != p->key)	{	// 查找关键字为key的结点
		if (key < p->key)	{	// key更小,在左子树上进行查找
			f = p;
			p = p->leftChild;
		}
		else		{	// key更大,在右子树上进行查找
			f = p;
			p = p->rightChild;
		}
	}
	return p;
}

WordNode *Dictionary::Find(const string &word, WordNode *&f) const
{
	WordNode *p = GetRoot();
	f = NULL;

	while (p != NULL)	{	// 查找关键字为key的结点
		if (word < p->word)	{	// key更小,在左子树上进行查找
			f = p;
			p = p->leftChild;
		}
		else if (word == p->word)
		{
			cout << "请输入需要查找的词性：";
			string t;
			cin >> t;
			if (t.length() < 5)
			{
				for (int i = 5; i > t.length(); i--)
				{
					string b = " ";
					t = b + t;
				}
			}
			string k = word + t;
			return FindInit(k, f);
		}
		else		{	// key更大,在右子树上进行查找
			f = p;
			p = p->rightChild;
		}
	}
	return p;
}

WordNode *Dictionary::Find(const string &word)	const 
{
	WordNode *f;			// 指向被查找结点的双亲
	return Find(word, f);
}

WordNode *Dictionary::FindInit(const string &key)	const 
{
	WordNode *f;			// 指向被查找结点的双亲
	return FindInit(key, f);
}

bool Dictionary::Insert(const string &w,
	string &t, const string &pr, const string &c)
// 操作结果: 插入数据元素e
{
	WordNode *f;		// 指向被查找结点的双亲
	if (t.length() < 5)
		{
			for (int i = 5; i > t.length(); i--)
			{
				string b = " ";
				t = b + t;
			}
		}
	string k = w + t;
	if (FindInit(k, f) == NULL)	{	    // 查找失败, 插入成功
		WordNode *p;	// 插入的新结点
		p = new WordNode(w, t, pr, c);
		if (IsEmpty())	            // 空二叉树,新结点为根结点
			root = p;
		else if (k < f->key)	    // e小于其双亲,插入结点为f的左孩子
			f->leftChild = p;
		else 	                    // e大于其双亲,插入结点为f的右íı孩子
			f->rightChild = p;
		return true;		
	}
	else	// 查找成功, 插入失败
		cout << endl << "单词已存在." << endl; 
		return false;
}


void Dictionary::Delete(WordNode *&p)
// 操作结果: 删除p指向的结点
{
	WordNode *tmpPtr, *tmpF;  
	if (p->leftChild == NULL && p->rightChild == NULL)	{	// p为叶结点
		delete p;
		p = NULL;
	}
	else if (p->leftChild == NULL)	{	// p只有左子树为空
		tmpPtr = p;
		p = p->rightChild;
		delete tmpPtr;
	}
	else if (p->rightChild == NULL)	{	// p只有右子树非空
		tmpPtr = p;
		p = p->leftChild;
		delete tmpPtr;
	}
	else	{	// p左右子非空
		tmpF = p;
		tmpPtr = p->leftChild;
		while (tmpPtr->rightChild != NULL)	{	// 查找p在中序序列中直接前驱tmpPtr及其双亲tmpF,直到tmpPtr右子树为空
			tmpF = tmpPtr;
			tmpPtr = tmpPtr->rightChild;
		}
		p->key = tmpPtr->key;
			// 将tmpPtr指向结点的数据元素值赋值给tmpF指向结点的数据元素值

		// 删除tmpPtr指向的结点
		if (tmpF->rightChild == tmpPtr)	// 删除tmpF的右孩子
			Delete(tmpF->rightChild);
		else    // 删除tmpF的左孩子
			Delete(tmpF->leftChild);
	}
}

bool Dictionary::Delete(const string &word)
// 操作结果: 删除关键字为key的数据元素
{
	WordNode *p, *f;
	p = Find(word, f);
	if ( p == NULL)	// 查找失败, 删除失败
	{
		cout << endl << "单词不存在." << endl; 
		return false;
	}
	else	// 查找成功, 插入失败
	{
		if (f == NULL)	// 被删除结点为根结点
			Delete(p);
		else if (word < f->word)	// elem.key更小,删除f的左孩子
			Delete(f->leftChild);
		else	// elem.key更大, 删除f的右孩子
			Delete(f->rightChild);
		cout << endl << "删除成功." << endl; 
		return true;	
	}
			
}

void Dictionary::Destroy(WordNode *&r)
// 操作结果：销毁以r的二叉排序树
{
	if(r != NULL)	{	// r非空,实施销毁
		Destroy(r->leftChild);		// 销毁左子树
		Destroy(r->rightChild);		// 销毁右子树
		delete r;						// 销毁根结点
		r = NULL;
	}
}

WordNode *Dictionary::CopyTree(WordNode *copy)
// 操作结果：将以copy为根的二叉排序树复制成新的二叉排序树,返回新二叉排序树的根
{
	if (copy == NULL)	// 复制空二叉排序树
		return NULL;					// 空二叉排序树根为空	
	else	{	// 复制非空二叉排序树
		WordNode *lChild = CopyTree(copy->leftChild);	// 复制左子树
		WordNode *rChild = CopyTree(copy->rightChild);	// 复制右子树
		WordNode *r = new WordNode("word","n.","word!","单词", lChild, rChild);
			// 复制根结点
		return r;
	}
}

Dictionary::Dictionary(const Dictionary &copy)
// 操作结果：由已知二叉排序树构造新二叉排序树——复制构造函数
{
	root = CopyTree(copy.root);	// 复制二叉排序树
}


Dictionary::Dictionary(WordNode *r)
// 操作结果：建立以r为根的二叉排序树
{	
	root = r;	// 复制二叉排序树
}


Dictionary &Dictionary::operator=(const Dictionary &copy)
// 操作结果：由已知二叉排序树copy复制到当前二叉排序树--赋值语句重载
{
	if (&copy != this)	{
		Destroy(root);				// 释放原二叉排序树所占用空间
		root = CopyTree(copy.root);	// 复制二叉排序树
	}
	return *this;
}

#endif
