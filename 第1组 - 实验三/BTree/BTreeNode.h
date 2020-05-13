#ifndef BTREENODE_H
#define BTREENODE_H
#define ORDER 3

#include <iostream>
#include "Assistance.h"
using namespace std;

template<class ElemType>
struct BTreeNode
{
	int num;
	ElemType key[ORDER+1];
	BTreeNode<ElemType> *pointer[ORDER+1];
	
	BTreeNode();
};

template<class ElemType>
BTreeNode<ElemType>::BTreeNode()
{
	num = 0;
	for(int i = 0; i<=ORDER; i++)
		pointer[i] =NULL;
}




#endif