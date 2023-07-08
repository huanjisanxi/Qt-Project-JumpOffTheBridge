#ifndef DRAGON_H
#define DRAGON_H

#include "staticObject.h"
#include "moveobject.h"
#include "arrow.h"

#include <QVector>

class Dragon:public StaticObject{
    Q_OBJECT

private:
    enum State{
        Rest,
        Attack,
        Attacked,
        Dead
    }dragonState;
    QPixmap restG;
    QPixmap attackG;
    QPixmap attackedG;
    QPixmap redHeartG;
    QPixmap whiteHeartG;
    QPixmap blackHeartG;
    int attackTimer;
    int attackedTimer;
    int attackTime;
    int strength;
    int deathTimer;
    bool shootBomb;

public:
    Dragon(qreal x, qreal y, qreal width, qreal height);
    ~Dragon();

    bool isAlive();
    bool isShootBomb();
    void draw(QPainter *painter);
    void updateState(const QVector<Arrow*>& arrowList);

};

#endif // DRAGON_H
