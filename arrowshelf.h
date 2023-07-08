#ifndef ARROWSHELF_H
#define ARROWSHELF_H

#include"staticObject.h"


class ArrowShelf:public StaticObject
{
    Q_OBJECT

public:
    ArrowShelf(qreal x,qreal y,qreal width, qreal height);
    ~ArrowShelf();
};

#endif // ARROWSHELF_H
