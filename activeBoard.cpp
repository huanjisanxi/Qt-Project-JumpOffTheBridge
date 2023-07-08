#include "activeBoard.h"
#include "parameter.cpp"

#include <QDebug>

ActiveBoard::ActiveBoard(qreal x,
               qreal y,
               qreal width,
               qreal height):
    MoveObject(x,y,width,height){
    mxSpeed=0;
    mySpeed=0;
    boardState = Rest;
    boardIndex = 0;
    activated = 0;

    rest.load(ACTIVEBOARD0);
    active_0.load(ACTIVEBOARD1);
    active_1.load(ACTIVEBOARD2);
    gun_0.load(ACTIVEBOARD3);
    gun_1.load(ACTIVEBOARD4);
    gun_2.load(ACTIVEBOARD3);
    run_0.load(ACTIVEBOARD5);
    run_1.load(ACTIVEBOARD6);
    run_2.load(ACTIVEBOARD7);
}

ActiveBoard::~ActiveBoard(){
    //-------TODO-------
}

void ActiveBoard::updateState(MoveObject* obj){
    if(boardState == Rest){
        if(obj->rect().x() + activeBoardSpace > rect().x() && obj->rect().y() + obj->rect().height() >= floorY){
            boardState = Active_0;
        }
    }
    else{
        boardIndex++;
        if(boardState == Active_0){
            if(boardIndex > active1Start){
                boardState = Active_1;
            }
        }
        else if(boardState == Active_1){
            if(boardIndex > gun0Start){
                boardState = Gun_0;
            }
        }
        else if(boardState == Gun_0){
            if(boardIndex > gun1Start){
                boardState = Gun_1;
            }
        }
        else if(boardState == Gun_1){
            activated = 1;
            if(boardIndex >gun2Start){
                boardState = Gun_2;
            }
        }
        else if(boardState == Gun_2){
            if(boardIndex > run0Start){
                boardState = Run_0;
                boardIndex = 0;
            }
        }
        else{
            boardIndex %= 15;
            setxSpeed(5);
            if(boardIndex < 5){
                boardState = Run_0;
            }
            else if(boardIndex < 10){
                boardState = Run_1;
            }
            else{
                boardState = Run_2;
            }
        }
    }
}

void ActiveBoard::updateRect(MoveObject* obj){
    updateState(obj);
    MoveObject::updateRect();
}

void ActiveBoard::draw(QPainter *painter){
    switch (boardState) {
    case Rest:
        painter->drawPixmap(mRect.x(), mRect.y(), rest.width(), rest.height(), rest);
        break;
    case Active_0:
        painter->drawPixmap(mRect.x(), mRect.y(), active_0.width(), active_0.height(), active_0);
        break;
    case Active_1:
        painter->drawPixmap(mRect.x(),mRect.y(),active_1.width(),active_1.height(), active_1);
        break;
    case Gun_0:
        painter->drawPixmap(mRect.x() - 2, mRect.y(), gun_0.width(), gun_0.height(), gun_0);
        break;
    case Gun_1:
        painter->drawPixmap(mRect.x(), mRect.y() - 2, gun_1.width(), gun_1.height(), gun_1);
        break;
    case Gun_2:
        painter->drawPixmap(mRect.x() - 2, mRect.y(), gun_2.width(), gun_2.height(), gun_2);
        break;
    case Run_0:
        painter->drawPixmap(mRect.x(), mRect.y() - 2, run_0.width(), run_0.height(), run_0);
        break;
    case Run_1:
        painter->drawPixmap(mRect.x(), mRect.y() - 4, run_1.width(), run_1.height(), run_1);
        break;
    case Run_2:
        painter->drawPixmap(mRect.x(), mRect.y() - 2, run_2.width(), run_2.height(), run_2);
        break;
    default:
        break;
    }
}

bool ActiveBoard::is_active(){
    return activated;
}
