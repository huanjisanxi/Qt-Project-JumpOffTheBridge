#ifndef ACTIVEBOARD_H
#define ACTIVEBOARD_H

#include <QTimer>

#include "moveobject.h"

class ActiveBoard:public MoveObject{
    Q_OBJECT

private:
    enum State{
        Rest,
        Active_0,
        Active_1,
        Gun_0,
        Gun_1,
        Gun_2,
        Run_0,
        Run_1,
        Run_2
    }boardState;
    QPixmap rest;
    QPixmap active_0;
    QPixmap active_1;
    QPixmap gun_0;
    QPixmap gun_1;
    QPixmap gun_2;
    QPixmap run_0;
    QPixmap run_1;
    QPixmap run_2;
    int boardIndex;
    bool activated;

public:
    ActiveBoard(qreal x, qreal y, qreal width, qreal height);
    ~ActiveBoard();

    void updateState(MoveObject *);
    void updateRect(MoveObject *);
    void draw(QPainter *painter);
    bool is_active();

};

#endif // ACTIVEBOARD_H
