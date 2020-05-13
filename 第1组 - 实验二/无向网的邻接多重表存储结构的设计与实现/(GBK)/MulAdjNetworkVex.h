#ifndef MULADJNETWORKVEX_H_INCLUDED
#define MULADJNETWORKVEX_H_INCLUDED
#include"MulAdjNetworkArc.h"
//�ڽӶ��ر�������
template <class ElemType,class WeightType>
struct MulAdjNetworkVex
{
    ElemType data;//����Ԫ��ֵ
    MulAdjNetworkArc<WeightType> *firstarc;//ָ��ߵ�ָ��

    MulAdjNetworkVex();
    MulAdjNetworkVex(ElemType val,MulAdjNetworkArc<WeightType>*adj=NULL);
};

template <class ElemType,class WeightType>
MulAdjNetworkVex< ElemType, WeightType>::MulAdjNetworkVex()
{
    firstarc=NULL;
}

template <class ElemType,class WeightType>
MulAdjNetworkVex< ElemType, WeightType>::MulAdjNetworkVex(ElemType val,MulAdjNetworkArc<WeightType>*adj)
{
    data=val;
    firstarc=adj;
}




#endif // MULADJNETWORKVEX_H_INCLUDED
