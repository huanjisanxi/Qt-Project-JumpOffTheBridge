#ifndef BULLET_H
#define BULLET_H

#include "staticObject.h"
#include "moveobject.h"

class Bullet:public MoveObject{
    Q_OBJECT

public:
    Bullet(qreal x, qreal y, qreal width, qreal height);
    ~Bullet();
};

#endif // BULLET_H
