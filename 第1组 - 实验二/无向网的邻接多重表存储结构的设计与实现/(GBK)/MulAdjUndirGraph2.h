#ifndef MULADJUNDIRGRAPH_H_INCLUDED
#define MULADJUNDIRGRAPH_H_INCLUDED

#include "MulAdjNetworkVex.h"
#include "MulAdjNetworkArc.h"


char vexs[] = {'A'};
		int m[1][1] = {
			{0}
		};
		char c = '0', e, e1, e2;
		int n = 1, v, v1, v2, v3, len, w;
		
//无向图的邻接多重表
template<class ElemType, class WeightType>
class MulAdjUndirGraph
{
protected:
	int vexNum, vexMaxNum, arcNum;//顶点数目，最大顶点数。边数
	MulAdjNetworkVex<ElemType, WeightType>* vexTable;//顶点表
	mutable Status* tag;
public:
	MulAdjUndirGraph(ElemType es[], int vertexNum, int vertexmaxNum = DEFAULT_SIZE);
	// ~NetWork();
	void Show();
	int FirstAdjVex(int v) const;		// 顶点v的第一个邻接点序号	
	int NextAdjVex(int v1, int v2) const;		 // 顶点v1的相对于v2的下一个邻接点
	Status GetTag(int v) const;				     // 求顶点v的标志		 
	void SetTag(int v, Status tag) const;	     // 设置顶点v的标志为tag	
	MulAdjNetworkArc<WeightType>* GetNextarc(const MulAdjNetworkArc<WeightType>& a1, int v) const;	//边a1关于v的下一条边
	WeightType GetWeight(int v1, int v2) const;	 // 顶点v1到v2的边的权值
	int SimplePathNum(WeightType len) const;	//无向图中任意两点之间长度为len的简单路径数目
	int HelpVexSPN(int v, WeightType len) const; //辅助计算长度为len的简单路径数目
	int GetOrder(ElemType &d) const;
	void InsertVex(const ElemType& d);			 // 插入元素值为d的顶点		 
	void InsertArc(int v1, int v2, WeightType w);// 插入顶点为v1,v2、权为w的边
	void InsertArcP(int v1, int v2, WeightType w);// 插入顶点为v1,v2、权为w的边
	int IfArc(int v1, int v2);			//判断v1-v2边是否存在
	void DeleteVex(int v1,int m[1][1]);
	void DeleteVex(ElemType e1, int m[1][1]);	
	void DeleteArc(int v1, int v2);
	void DeleteArc(ElemType e1, ElemType e2);

};

template <class ElemType, class WeightType>
MulAdjUndirGraph<ElemType, WeightType>::MulAdjUndirGraph(ElemType es[], int vertexNum, int vertexmaxNum)
{
	if (vertexmaxNum < 0)
		throw Error("允许的顶点最大数目不能为负!");        // 抛出异常

	if (vertexmaxNum < vertexNum)
		throw Error("顶点数目不能大于允许的顶点最大数目!");// 抛出异常

	vexNum = vertexNum;
	vexMaxNum = vertexmaxNum;
	arcNum = 0;
	//infinity = infinit;

	tag = new Status[vexMaxNum];
	vexTable = new MulAdjNetworkVex<ElemType, WeightType>[vexMaxNum];

	for (int v = 0; v < vexNum; v++) {
		tag[v] = UNVISITED;
		vexTable[v].data = es[v];
		vexTable[v].firstarc = NULL;
	}
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::Show()
{
	MulAdjNetworkArc<WeightType>* p, * f;
	cout << "无向图共有" << vexNum << "个顶点，" << arcNum << "条边" << endl;
	for (int v = 0; v < vexNum; v++)
	{ // 显示第v个邻接链表
		if (vexTable[v].firstarc != NULL)
		{
			cout << v << ":\t" << vexTable[v].data << " ";
		}    // 显示顶点号
		p = vexTable[v].firstarc;
		while (p != NULL) {
			cout << vexTable[p->adjVex1].data << "--" << p->weight << "--" << vexTable[p->adjVex2].data << ",";
			if (p->adjVex1 == v)
				p = p->nextarc1;
			else
				p = p->nextarc2;

		}
		if (vexTable[v].firstarc != NULL) cout << endl;
	}
}

template <class ElemType, class WeightType>
int MulAdjUndirGraph<ElemType, WeightType>::FirstAdjVex(int v) const
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!");// 抛出异常

	if (vexTable[v].firstarc == NULL)
		return -1;              // 不存在邻接点
	if (vexTable[v].firstarc->adjVex1 != v)
		return vexTable[v].firstarc->adjVex1;
	else
		return vexTable[v].firstarc->adjVex2;
}

template <class ElemType, class WeightType>
int MulAdjUndirGraph<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
{
	MulAdjNetworkArc<WeightType>* p, * q;
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
		throw Error("v1不能等于v2!");// 抛出异常

	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex1 != v2 && p->adjVex2 != v2)
	{
		if (p->adjVex1 == v1)
			p = p->nextarc1;
		else
			p = p->nextarc2;
	}
	if (p == NULL)
		return -1;                   // 不存在V1-V2边

	q = GetNextarc(*p, v1);
	if (q == NULL)
		return -1;
	else
	{
		if (q->adjVex1 == v1)
			return q->adjVex2;
		else
			return q->adjVex1;
	}
}

template <class ElemType, class WeightType>
Status MulAdjUndirGraph<ElemType, WeightType>::GetTag(int v) const
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!");		// 抛出异常

	return tag[v];
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::SetTag(int v, Status val) const
{
	if (v < 0 || v >= vexNum)
		throw Error("v不合法!");		// 抛出异常

	tag[v] = val;
}

template <class ElemType, class WeightType>
MulAdjNetworkArc<WeightType>* MulAdjUndirGraph<ElemType, WeightType>::GetNextarc(const MulAdjNetworkArc<WeightType>& a1, int v) const
{
	if (a1.adjVex1 == v)
		return a1.nextarc1;
	else
		return a1.nextarc2;
}

template <class ElemType, class WeightType>
WeightType MulAdjUndirGraph<ElemType, WeightType>::GetWeight(int v1, int v2) const
{
	MulAdjNetworkArc<WeightType>* p;
	for (p = vexTable[v1].firstarc; p != NULL; p = GetNextarc(*p, v1))
	{
		if (p->adjVex2 == v2 || p->adjVex1 == v2)
			return p->weight;
	}
	throw Error("v1-v2无此边");
}

template <class ElemType, class WeightType>
int MulAdjUndirGraph<ElemType, WeightType>::SimplePathNum(WeightType len) const
{
	if (len <= 0)
		throw Error("len不合法！");
	int n = 0;
	for (int i = 0; i < vexNum; i++)
		SetTag(i, UNVISITED);
	for (int i = 0; i < vexNum; i++)
		n += HelpVexSPN(i, len);
	return n;
}

template <class ElemType, class WeightType>
int MulAdjUndirGraph<ElemType, WeightType>::HelpVexSPN(int v, WeightType len) const
{
	int n = 0;
	SetTag(v, VISITED);
	for (int p = FirstAdjVex(v); p != -1; p = NextAdjVex(v, p))
	{
		if (tag[p] == VISITED)
			continue;
		if (len - GetWeight(v, p) > 0)
			n += HelpVexSPN(p, len - GetWeight(v, p));
		else if (len - GetWeight(v, p) == 0)
			n++;
	}
	SetTag(v, UNVISITED);
	return n;
}

template <class ElemType, class WeightType>
int MulAdjUndirGraph<ElemType, WeightType>::GetOrder(ElemType &d) const
{
    int v;
    for (v = 0; v < vexNum; v++)
        if (d == vexTable[v].data)
            break;

    if (v < 0 || v >= vexNum)
        return -1; // 顶点d不存在,返回-1
    else
        return v; // 顶点d不存在,返回它的序号
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::InsertVex(const ElemType& d)
{
	if (vexNum == vexMaxNum)
		throw Error("图的顶点数不能超过允许的最大数!");	// 抛出异常

	vexTable[vexNum].data = d;
	vexTable[vexNum].firstarc = NULL;
	tag[vexNum] = UNVISITED;
	vexNum++;
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w)
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
		throw Error("v1不能等于v2!");// 抛出异常
	if (IfArc(v1, v2))
		return;	// 抛出异常
	MulAdjNetworkArc<WeightType>* p = NULL, * q = NULL, * g = NULL;

	for (p = vexTable[v1].firstarc; p != NULL; q = p, p = GetNextarc(*p, v1)) {}	//找到v1中最后一条边q （p是q的后一条边，当q的后一条边为空时，q就是最后一条边了）
	g = new MulAdjNetworkArc<WeightType>(w, v1, v2);	//g是新建的要插入的边
	if (q == NULL)		//如果顶点v1连一条边都没有的话
		vexTable[v1].firstarc = g;
	else	//顶点v1有边
	{
		if (q->adjVex1 == v1)		//判断新边g接在v1最后一条边的哪个指针后
			q->nextarc1 = g;
		else
			q->nextarc2 = g;
	}

	p = q = NULL;
	for (p = vexTable[v2].firstarc; p != NULL; q = p, p = GetNextarc(*p, v2)) {}	//找到v2中最后一条边q （p是q的后一条边，当q的后一条边为空时，q就是最后一条边了）
	if (q == NULL)	//如果顶点v1连一条边都没有的话
		vexTable[v2].firstarc = g;
	else
	{
		if (q->adjVex1 == v2)		//判断新边g接在v2最后一条边的哪个指针后
			q->nextarc1 = g;
		else
			q->nextarc2 = g;
	}
	g->nextarc1 = NULL;
	g->nextarc2 = NULL;
	g->tag = UNVISITED;
	arcNum++;
	m[v1][v2] = w;
}
template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::InsertArcP(int v1, int v2, WeightType w)
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
		throw Error("v1不能等于v2!");// 抛出异常
	if (m[v1][v2] != 0)
		{cout << "此边已存在。" << endl; return;}	// 抛出异常
	if (IfArc(v1, v2))
		return;	// 抛出异常
	MulAdjNetworkArc<WeightType>* p = NULL, * q = NULL, * g = NULL;

	for (p = vexTable[v1].firstarc; p != NULL; q = p, p = GetNextarc(*p, v1)) {}	//找到v1中最后一条边q （p是q的后一条边，当q的后一条边为空时，q就是最后一条边了）
	g = new MulAdjNetworkArc<WeightType>(w, v1, v2);	//g是新建的要插入的边
	if (q == NULL)		//如果顶点v1连一条边都没有的话
		vexTable[v1].firstarc = g;
	else	//顶点v1有边
	{
		if (q->adjVex1 == v1)		//判断新边g接在v1最后一条边的哪个指针后
			q->nextarc1 = g;
		else
			q->nextarc2 = g;
	}

	p = q = NULL;
	for (p = vexTable[v2].firstarc; p != NULL; q = p, p = GetNextarc(*p, v2)) {}	//找到v2中最后一条边q （p是q的后一条边，当q的后一条边为空时，q就是最后一条边了）
	if (q == NULL)	//如果顶点v1连一条边都没有的话
		vexTable[v2].firstarc = g;
	else
	{
		if (q->adjVex1 == v2)		//判断新边g接在v2最后一条边的哪个指针后
			q->nextarc1 = g;
		else
			q->nextarc2 = g;
	}
	g->nextarc1 = NULL;
	g->nextarc2 = NULL;
	g->tag = UNVISITED;
	arcNum++;
	m[v1][v2] = w;
}

template <class ElemType, class WeightType>
int MulAdjUndirGraph<ElemType, WeightType>::IfArc(int v1, int v2)
{
	MulAdjNetworkArc<WeightType>* p = NULL;
	for (p = vexTable[v1].firstarc; p != NULL; p = GetNextarc(*p, v1))
		if (p->adjVex1 == v2 || p->adjVex2 == v2)
			return 1;
	return 0;
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::DeleteVex(int v, int m[1][1])
{
	if (v >= vexNum)
		{cout << "图中不存在要删除的顶点!" << endl; return;}// 异常
	for (int i = 0; i < vexNum; i++)
	{
		if (i != v)
		{
			if (m[v][i] != 0)
			{
				if (v > i) DeleteArc(i, v);
				else DeleteArc(v, i);
			}
		}
	}
	cout << "删除成功！" << endl;
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::DeleteVex(ElemType e, int m[1][1])
{
	v = GetOrder(e);
	if (v >= vexNum)
		{cout << "图中不存在要删除的顶点!" << endl; return;}// 异常
	for (int i = 0; i < vexNum; i++)
	{
		if (i != v)
		{
			if (m[v][i] != 0)
			{
				if (v > i) DeleteArc(i, v);
				else DeleteArc(v, i);
			}
		}
	}
	cout << "删除成功！" << endl;
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::DeleteArc(int v1, int v2)
{
	if (m[v1][v2] == 0) {cout << "图中不存在要删除的边!" << endl; return;}// 异常
	MulAdjNetworkArc<WeightType>* temp = vexTable[v1].firstarc, * p1 = NULL, * p2 = NULL;
	while (temp != NULL && temp->adjVex1 != v2 && temp->adjVex2 != v2)
	{
		p1 = temp;
		temp = GetNextarc(*temp, v1);
	}

	temp = vexTable[v2].firstarc;
	while (temp != NULL && temp->adjVex1 != v1 && temp->adjVex2 != v1)
	{
		p2 = temp;
		temp = GetNextarc(*temp, v2);
	}
	if (vexTable[v1].firstarc == temp && temp != NULL)vexTable[v1].firstarc = GetNextarc(*temp, v1);
	else
	{
		if (p1 != NULL)
		{
			if (p1->adjVex1 == v1)p1->nextarc1 = temp->nextarc1;
			if (p1->adjVex2 == v1)p1->nextarc2 = temp->nextarc1;
		}
	}
	if (vexTable[v2].firstarc == temp && temp != NULL)vexTable[v2].firstarc = GetNextarc(*temp, v2);
	else
	{
		if (p2 != NULL)
		{
			if (p2->adjVex1 == v2)p2->nextarc1 = temp->nextarc2;
			if (p2->adjVex2 == v2)p2->nextarc2 = temp->nextarc2;
		}
	}

	arcNum--;
	m[v1][v2] = 0;
	cout << "删除成功！" << endl;
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::DeleteArc(ElemType e1, ElemType e2)
{
	v1 = GetOrder(e1);
	v2 = GetOrder(e2);
	if (m[v1][v2] == 0) {cout << "图中不存在要删除的边!" << endl; return;}// 异常

	MulAdjNetworkArc<WeightType>* temp = vexTable[v1].firstarc, * p1 = NULL, * p2 = NULL;
	while (temp != NULL && temp->adjVex1 != v2 && temp->adjVex2 != v2)
	{
		p1 = temp;
		temp = GetNextarc(*temp, v1);
	}

	temp = vexTable[v2].firstarc;
	while (temp != NULL && temp->adjVex1 != v1 && temp->adjVex2 != v1)
	{
		p2 = temp;
		temp = GetNextarc(*temp, v2);
	}
	if (vexTable[v1].firstarc == temp && temp != NULL)vexTable[v1].firstarc = GetNextarc(*temp, v1);
	else
	{
		if (p1 != NULL)
		{
			if (p1->adjVex1 == v1)p1->nextarc1 = temp->nextarc1;
			if (p1->adjVex2 == v1)p1->nextarc2 = temp->nextarc1;
		}
	}
	if (vexTable[v2].firstarc == temp && temp != NULL)vexTable[v2].firstarc = GetNextarc(*temp, v2);
	else
	{
		if (p2 != NULL)
		{
			if (p2->adjVex1 == v2)p2->nextarc1 = temp->nextarc2;
			if (p2->adjVex2 == v2)p2->nextarc2 = temp->nextarc2;
		}
	}

	arcNum--;
	m[v1][v2] = 0;
	cout << "删除成功！" << endl;
}

#endif // MULADJUNDIRGRAPH_H_INCLUDED