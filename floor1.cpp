#include "floor1.h"

#include <QDebug>

Floor1::Floor1(qreal x, qreal y, qreal width, qreal height):
    StaticObject(x,y,width,height){

}

Floor1::~Floor1(){

}

//判断碰撞
bool Floor1::touch(MoveObject* obj){
    if((obj->rect().x() < 560 && obj->rect().x() >= 1200-mRect.width())||
        (obj->rect().x() > 1200+640 && obj->rect().x() <= 1200+mRect.width()))
        return obj->rect().y() + obj->rect().height() >= mRect.y() && obj->rect().y() <= 444;
    return obj->rect().y() + obj->rect().height() >= mRect.y()
           && (obj->rect().x() <= 1200+mRect.width() && obj->rect().x()>=1200-mRect.width());
}

//处理玩家小人触地
bool Floor1::detect(MoveObject* obj){
    bool ret = touch(obj);
    obj->setOnFloor(ret);
    if(ret){
        upForce(obj);
        obj->setPos(obj->rect().x(),mRect.y()-obj->rect().height());
    }
    return ret;
}

void Floor1::upForce(MoveObject* obj){
    obj->setySpeed(0);
}
