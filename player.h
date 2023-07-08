#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QVector>

#include "moveobject.h"
#include "blood.h"

class Player:public MoveObject{
    Q_OBJECT

private:
    MoveObject *liftObj;
    //0为静止，1为移动
    QPixmap right[2];
    QPixmap left[2];
    QPixmap liftRight[2];
    QPixmap liftLeft[2];
    QPixmap death;
    int indexRight;
    int indexLeft;
    int indexLiftRight;
    int indexLiftLeft;
    bool indexDirection;
    int deathTimer;
    void setIndex();

public:
    Player(qreal x, qreal y, qreal width, qreal height);
    ~Player();

    void updateRect();
    void draw(QPainter *painter);

    void updateState();

    void jump();
    void pickUp(MoveObject* obj);
    void throwing();

    void moveRight();
    void moveLeft();
    void moveNo();

    void setDeath();

    QVector<Blood*> bloodList;
    enum State{
        Static,
        Jump,
        MoveLeft,
        MoveRight,
        Lift,
        LiftMoveLeft,
        LiftMoveRight,
        Death
    }playerState;

};

#endif // PLAYER_H
