#ifndef BULLS_H
#define BULLS_H

#include<Qtime>

#include "moveobject.h"
#include "staticObject.h"

class Bulls:public MoveObject{
    Q_OBJECT
private:
    QPixmap bull[2];
    int indexbull;
    QPixmap redbull[2];
    QPixmap yellowbull[2];
    QPixmap blackbull[2];
    int color;


public:
    Bulls(qreal x,qreal y,qreal width, qreal height);
    ~Bulls();


    void draw(QPainter *painter);
    void updateRect();
    static int temp;

};

#endif // BULLS_H
