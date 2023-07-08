#include "signboard.h"
#include "parameter.cpp"

#include <QDebug>
#include <QPixmap>

SignBoard::SignBoard(qreal x,
                     qreal y,
                     qreal width,
                     qreal height):
    StaticObject(x , y, width, height),
    touched(false){
    mGraph.load(BOARD);
}

SignBoard::~SignBoard(){

}

//判断碰撞
bool SignBoard::detect(MoveObject* obj){
    if(obj->rect().x() + obj->rect().width() + boardSpace>= rect().x()
        && obj->rect().x() - obj->rect().width() - boardSpace <= rect().x()){
        touched = true;
        return true;
    }
    touched = false;
    return false;
}

bool SignBoard::is_touched(){
    return touched;
}













