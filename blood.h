#ifndef BLOOD_H
#define BLOOD_H

#include "moveobject.h"

#include <random>
#include <iostream>

class Blood:public MoveObject{
    Q_OBJECT

public:
    Blood(qreal x, qreal y, qreal width, qreal height, int index);
    ~Blood();

    void updateRect();
    void draw(QPainter *painter);
};

#endif // BLOOD_H
