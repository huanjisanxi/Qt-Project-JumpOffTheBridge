#include "floor2.h"

#include <QDebug>

Floor2::Floor2(qreal x, qreal y, qreal width, qreal height):
    StaticObject(x,y,width,height){

}

Floor2::~Floor2(){

}

//判断碰撞
bool Floor2::touch(MoveObject* obj){
    if(obj->rect().x() < 560 && obj->rect().x() >= 1200-mRect.width())
        return obj->rect().y() + obj->rect().height() >= mRect.y() && obj->rect().y() <= 444;
    return obj->rect().y() + obj->rect().height() >= rect().y()
           && obj->rect().x() >= 1200 - rect().width();
}

//处理玩家小人触地
bool Floor2::detect(MoveObject* obj){
    bool ret = touch(obj);
    obj->setOnFloor(ret);
    if(ret){
        upForce(obj);
        obj->setPos(obj->rect().x(),mRect.y()-obj->rect().height());
    }
    return ret;
}

void Floor2::upForce(MoveObject* obj){
    obj->setySpeed(0);
}
