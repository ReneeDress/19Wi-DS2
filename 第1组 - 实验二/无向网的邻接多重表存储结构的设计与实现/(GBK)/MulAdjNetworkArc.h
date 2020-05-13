#ifndef MULADJNETWORKARC_H_INCLUDED
#define MULADJNETWORKARC_H_INCLUDED
//邻接多重表边数据类
template<class WeightType>
struct MulAdjNetworkArc
{//数据成员：
    mutable Status tag;//标记域
    WeightType weight;//边的信息域
    int adjVex1,adjVex2;//顶点域
    MulAdjNetworkArc<WeightType> *nextarc1;
    MulAdjNetworkArc<WeightType> *nextarc2;//链接指针
//构造函数:
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
