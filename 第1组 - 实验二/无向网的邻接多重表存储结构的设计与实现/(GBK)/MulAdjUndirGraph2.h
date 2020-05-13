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
		
//����ͼ���ڽӶ��ر�
template<class ElemType, class WeightType>
class MulAdjUndirGraph
{
protected:
	int vexNum, vexMaxNum, arcNum;//������Ŀ����󶥵���������
	MulAdjNetworkVex<ElemType, WeightType>* vexTable;//�����
	mutable Status* tag;
public:
	MulAdjUndirGraph(ElemType es[], int vertexNum, int vertexmaxNum = DEFAULT_SIZE);
	// ~NetWork();
	void Show();
	int FirstAdjVex(int v) const;		// ����v�ĵ�һ���ڽӵ����	
	int NextAdjVex(int v1, int v2) const;		 // ����v1�������v2����һ���ڽӵ�
	Status GetTag(int v) const;				     // �󶥵�v�ı�־		 
	void SetTag(int v, Status tag) const;	     // ���ö���v�ı�־Ϊtag	
	MulAdjNetworkArc<WeightType>* GetNextarc(const MulAdjNetworkArc<WeightType>& a1, int v) const;	//��a1����v����һ����
	WeightType GetWeight(int v1, int v2) const;	 // ����v1��v2�ıߵ�Ȩֵ
	int SimplePathNum(WeightType len) const;	//����ͼ����������֮�䳤��Ϊlen�ļ�·����Ŀ
	int HelpVexSPN(int v, WeightType len) const; //�������㳤��Ϊlen�ļ�·����Ŀ
	int GetOrder(ElemType &d) const;
	void InsertVex(const ElemType& d);			 // ����Ԫ��ֵΪd�Ķ���		 
	void InsertArc(int v1, int v2, WeightType w);// ���붥��Ϊv1,v2��ȨΪw�ı�
	void InsertArcP(int v1, int v2, WeightType w);// ���붥��Ϊv1,v2��ȨΪw�ı�
	int IfArc(int v1, int v2);			//�ж�v1-v2���Ƿ����
	void DeleteVex(int v1,int m[1][1]);
	void DeleteVex(ElemType e1, int m[1][1]);	
	void DeleteArc(int v1, int v2);
	void DeleteArc(ElemType e1, ElemType e2);

};

template <class ElemType, class WeightType>
MulAdjUndirGraph<ElemType, WeightType>::MulAdjUndirGraph(ElemType es[], int vertexNum, int vertexmaxNum)
{
	if (vertexmaxNum < 0)
		throw Error("����Ķ��������Ŀ����Ϊ��!");        // �׳��쳣

	if (vertexmaxNum < vertexNum)
		throw Error("������Ŀ���ܴ�������Ķ��������Ŀ!");// �׳��쳣

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
	cout << "����ͼ����" << vexNum << "�����㣬" << arcNum << "����" << endl;
	for (int v = 0; v < vexNum; v++)
	{ // ��ʾ��v���ڽ�����
		if (vexTable[v].firstarc != NULL)
		{
			cout << v << ":\t" << vexTable[v].data << " ";
		}    // ��ʾ�����
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
		throw Error("v���Ϸ�!");// �׳��쳣

	if (vexTable[v].firstarc == NULL)
		return -1;              // �������ڽӵ�
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
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2)
		throw Error("v1���ܵ���v2!");// �׳��쳣

	p = vexTable[v1].firstarc;
	while (p != NULL && p->adjVex1 != v2 && p->adjVex2 != v2)
	{
		if (p->adjVex1 == v1)
			p = p->nextarc1;
		else
			p = p->nextarc2;
	}
	if (p == NULL)
		return -1;                   // ������V1-V2��

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
		throw Error("v���Ϸ�!");		// �׳��쳣

	return tag[v];
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::SetTag(int v, Status val) const
{
	if (v < 0 || v >= vexNum)
		throw Error("v���Ϸ�!");		// �׳��쳣

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
	throw Error("v1-v2�޴˱�");
}

template <class ElemType, class WeightType>
int MulAdjUndirGraph<ElemType, WeightType>::SimplePathNum(WeightType len) const
{
	if (len <= 0)
		throw Error("len���Ϸ���");
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
        return -1; // ����d������,����-1
    else
        return v; // ����d������,�����������
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::InsertVex(const ElemType& d)
{
	if (vexNum == vexMaxNum)
		throw Error("ͼ�Ķ��������ܳ�������������!");	// �׳��쳣

	vexTable[vexNum].data = d;
	vexTable[vexNum].firstarc = NULL;
	tag[vexNum] = UNVISITED;
	vexNum++;
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w)
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2)
		throw Error("v1���ܵ���v2!");// �׳��쳣
	if (IfArc(v1, v2))
		return;	// �׳��쳣
	MulAdjNetworkArc<WeightType>* p = NULL, * q = NULL, * g = NULL;

	for (p = vexTable[v1].firstarc; p != NULL; q = p, p = GetNextarc(*p, v1)) {}	//�ҵ�v1�����һ����q ��p��q�ĺ�һ���ߣ���q�ĺ�һ����Ϊ��ʱ��q�������һ�����ˣ�
	g = new MulAdjNetworkArc<WeightType>(w, v1, v2);	//g���½���Ҫ����ı�
	if (q == NULL)		//�������v1��һ���߶�û�еĻ�
		vexTable[v1].firstarc = g;
	else	//����v1�б�
	{
		if (q->adjVex1 == v1)		//�ж��±�g����v1���һ���ߵ��ĸ�ָ���
			q->nextarc1 = g;
		else
			q->nextarc2 = g;
	}

	p = q = NULL;
	for (p = vexTable[v2].firstarc; p != NULL; q = p, p = GetNextarc(*p, v2)) {}	//�ҵ�v2�����һ����q ��p��q�ĺ�һ���ߣ���q�ĺ�һ����Ϊ��ʱ��q�������һ�����ˣ�
	if (q == NULL)	//�������v1��һ���߶�û�еĻ�
		vexTable[v2].firstarc = g;
	else
	{
		if (q->adjVex1 == v2)		//�ж��±�g����v2���һ���ߵ��ĸ�ָ���
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
		throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2)
		throw Error("v1���ܵ���v2!");// �׳��쳣
	if (m[v1][v2] != 0)
		{cout << "�˱��Ѵ��ڡ�" << endl; return;}	// �׳��쳣
	if (IfArc(v1, v2))
		return;	// �׳��쳣
	MulAdjNetworkArc<WeightType>* p = NULL, * q = NULL, * g = NULL;

	for (p = vexTable[v1].firstarc; p != NULL; q = p, p = GetNextarc(*p, v1)) {}	//�ҵ�v1�����һ����q ��p��q�ĺ�һ���ߣ���q�ĺ�һ����Ϊ��ʱ��q�������һ�����ˣ�
	g = new MulAdjNetworkArc<WeightType>(w, v1, v2);	//g���½���Ҫ����ı�
	if (q == NULL)		//�������v1��һ���߶�û�еĻ�
		vexTable[v1].firstarc = g;
	else	//����v1�б�
	{
		if (q->adjVex1 == v1)		//�ж��±�g����v1���һ���ߵ��ĸ�ָ���
			q->nextarc1 = g;
		else
			q->nextarc2 = g;
	}

	p = q = NULL;
	for (p = vexTable[v2].firstarc; p != NULL; q = p, p = GetNextarc(*p, v2)) {}	//�ҵ�v2�����һ����q ��p��q�ĺ�һ���ߣ���q�ĺ�һ����Ϊ��ʱ��q�������һ�����ˣ�
	if (q == NULL)	//�������v1��һ���߶�û�еĻ�
		vexTable[v2].firstarc = g;
	else
	{
		if (q->adjVex1 == v2)		//�ж��±�g����v2���һ���ߵ��ĸ�ָ���
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
		{cout << "ͼ�в�����Ҫɾ���Ķ���!" << endl; return;}// �쳣
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
	cout << "ɾ���ɹ���" << endl;
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::DeleteVex(ElemType e, int m[1][1])
{
	v = GetOrder(e);
	if (v >= vexNum)
		{cout << "ͼ�в�����Ҫɾ���Ķ���!" << endl; return;}// �쳣
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
	cout << "ɾ���ɹ���" << endl;
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::DeleteArc(int v1, int v2)
{
	if (m[v1][v2] == 0) {cout << "ͼ�в�����Ҫɾ���ı�!" << endl; return;}// �쳣
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
	cout << "ɾ���ɹ���" << endl;
}

template <class ElemType, class WeightType>
void MulAdjUndirGraph<ElemType, WeightType>::DeleteArc(ElemType e1, ElemType e2)
{
	v1 = GetOrder(e1);
	v2 = GetOrder(e2);
	if (m[v1][v2] == 0) {cout << "ͼ�в�����Ҫɾ���ı�!" << endl; return;}// �쳣

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
	cout << "ɾ���ɹ���" << endl;
}

#endif // MULADJUNDIRGRAPH_H_INCLUDED