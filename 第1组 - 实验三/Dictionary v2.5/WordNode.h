#ifndef __WORD_NODE_H__
#define __WORD_NODE_H__

#include <string>
using namespace std;

struct WordNode
{
	string key;				//根据单词及词性构造的关键字
	string word;			//英文单词
	string type;			//该词条英文单词词性
	string pron;			//国际音标
	string chn;				//中文释义
	WordNode *leftChild;	// 左孩子指针域
	WordNode *rightChild;	// 右孩子指针域

	WordNode()				//构造函数
	{ leftChild = rightChild = NULL;}
	WordNode(const string &w, const string &t, const string &p, const string &c, WordNode *lChild = NULL, WordNode *rChild = NULL)
	{	
		word = w;
		type = t;
		if (t.length() < 5)
		{
			for (int i = 5; i > t.length(); i--)
			{
				string b = " ";
				type = b + type;
			}
		}
		key = w + t;		//通过填补词性至5位加上单词本身构造新的关键字
		pron = p;
		chn = c;
		leftChild = lChild;
		rightChild = rChild;
	}
};

#endif

