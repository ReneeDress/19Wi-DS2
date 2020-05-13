#ifndef MULADJNETWORKVEX_H_INCLUDED
#define MULADJNETWORKVEX_H_INCLUDED
#include"MulAdjNetworkArc.h"
//邻接多重表顶点结点类
template <class ElemType,class WeightType>
struct MulAdjNetworkVex
{
    ElemType data;//数据元素值
    MulAdjNetworkArc<WeightType> *firstarc;//指向边的指针

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
