#include "floor.h"

#include <QDebug>

Floor::Floor(qreal x, qreal y, qreal width, qreal height):StaticObject(x,y,width,height){

}

Floor::~Floor(){

}

//判断碰撞
bool Floor::touch(MoveObject* obj){
    if(obj->rect().x() > 640 && obj->rect().x() <= mRect.width())
        return obj->rect().y() + obj->rect().height() >= mRect.y() && obj->rect().y() <= 444;
    return obj->rect().y() + obj->rect().height() >= mRect.y() && obj->rect().x() <= mRect.width();
}

bool Floor::detect(Player *player){
    for(int i = 0; i != player->bloodList.size(); i++){
        bool onFloor = touch(player->bloodList[i]);
        player->bloodList[i]->setOnFloor(onFloor);
        if(onFloor){
            upForce(player->bloodList[i]);
            player->bloodList[i]->setPos(player->bloodList[i]->rect().x(),mRect.y()-player->bloodList[i]->rect().height());
        }
    }

    bool ret = touch(player);
    player->setOnFloor(ret);
    if(ret){
        upForce(player);
        player->setPos(player->rect().x(),mRect.y()-player->rect().height());
    }
    return ret;
}

bool Floor::detect(MoveObject* obj){
    bool ret = touch(obj);
    obj->setOnFloor(ret);
    if(ret){
        upForce(obj);
        obj->setPos(obj->rect().x(),mRect.y()-obj->rect().height());
    }
    return ret;
}

void Floor::upForce(MoveObject* obj){
    obj->setySpeed(0);
}
