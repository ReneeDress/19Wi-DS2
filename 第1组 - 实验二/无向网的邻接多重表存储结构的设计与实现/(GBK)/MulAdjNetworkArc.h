#ifndef MULADJNETWORKARC_H_INCLUDED
#define MULADJNETWORKARC_H_INCLUDED
//�ڽӶ��ر��������
template<class WeightType>
struct MulAdjNetworkArc
{//���ݳ�Ա��
    mutable Status tag;//�����
    WeightType weight;//�ߵ���Ϣ��
    int adjVex1,adjVex2;//������
    MulAdjNetworkArc<WeightType> *nextarc1;
    MulAdjNetworkArc<WeightType> *nextarc2;//����ָ��
//���캯��:
    MulAdjNetworkArc();
    MulAdjNetworkArc(WeightType w,int v1,int v2,MulAdjNetworkArc<WeightType> *next1=NULL,MulAdjNetworkArc<WeightType> *next2=NULL);
};

template<class WeightType>
MulAdjNetworkArc<WeightType>::MulAdjNetworkArc()
{
    adjVex1=-1;
    adjVex2=-1;
}

template<class WeightType>
MulAdjNetworkArc<WeightType>::MulAdjNetworkArc(WeightType w,int v1,int v2,MulAdjNetworkArc<WeightType> *next1,MulAdjNetworkArc<WeightType> *next2)
{
    tag=UNVISITED;
    weight=w;
    adjVex1=v1;
    adjVex2=v2;
    nextarc1=next1;
    nextarc2=next2;
}

#endif // MULADJNETWORKARC_H_INCLUDED
