#include "arrowshelf.h"
#include"parameter.cpp"


ArrowShelf::ArrowShelf(qreal x, qreal y, qreal width, qreal height)
    :StaticObject(x,y,width,height)
{
    mGraph.load(WEAPONSHELF);
}


ArrowShelf::~ArrowShelf(){}
