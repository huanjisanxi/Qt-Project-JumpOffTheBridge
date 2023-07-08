#ifndef BOMB_H
#define BOMB_H

#include "moveobject.h"

class Bomb:public MoveObject{
    Q_OBJECT

public:
    Bomb(qreal x, qreal y, qreal width, qreal height);
    ~Bomb();

    void updateState();
    void updateRect();
};

#endif // BOMB_H
