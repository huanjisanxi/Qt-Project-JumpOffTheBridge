#ifndef DOG_H
#define DOG_H

#include "moveobject.h"

class Dog:public MoveObject{
    Q_OBJECT
private:
    QPixmap actdog[3];
    int tmp;
public:
    Dog(qreal x, qreal y, qreal width, qreal height);
    ~Dog();

    void updateRect();
    void draw(QPainter *painter);
};

#endif // DOG_H
