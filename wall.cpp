#include "wall.h"
#include "parameter.cpp"

#include <QDebug>
#include <QPixmap>
#include <cmath>

Wall::Wall(qreal x,
            qreal y,
            qreal width,
            qreal height):
            StaticObject(x , y, width, height){
    mGraph.load(WALL);
    alive = 1;
    deathTimer = 16;
}

Wall::~Wall(){

}

void Wall::updateState(MoveObject * obj){
    if(obj->rect().x() + obj->rect().width() >= rect().x()){
        alive = 0;
    }
    if(alive == 0){
        deathTimer = std::max(deathTimer - 1, 0);
    }
}

//判断碰撞
bool Wall::detect(MoveObject* obj){
    if(alive){
        if(obj->rect().x() + obj->rect().width() >= rect().x()
            && obj->xSpeed() > 0){
            obj->setxSpeed(0);
            return true;
        }
    }
    return false;
}

void Wall::draw(QPainter *painter){
    if(alive){
        StaticObject::draw(painter);
    }
    else if(deathTimer / 2 % 2 == 1){
        StaticObject::draw(painter);
    }
}
