#ifndef TRAP_H
#define TRAP_H


#include"staticObject.h"


class Trap:public StaticObject
{
    Q_OBJECT
public:
    QPixmap statictrap;
public:
    Trap(qreal x,qreal y,qreal width, qreal height);
    ~Trap();
    void draw(QPainter *painter);
};

#endif // TRAP_H
