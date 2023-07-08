#include "trap.h"
#include"parameter.cpp"


Trap::Trap(qreal x, qreal y, qreal width, qreal height)
    :StaticObject(x,y,width,height)
{
    mGraph.load(GRASS);
    statictrap.load(GRASS);
}


Trap::~Trap(){}

void Trap::draw(QPainter *painter){
    painter->drawPixmap(mRect.x(),mRect.y(),statictrap);
}
