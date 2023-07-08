#include "bullet.h"
#include "parameter.cpp"

#include <QDebug>
#include <QPixmap>

Bullet::Bullet(qreal x,
               qreal y,
               qreal width,
               qreal height):
    MoveObject(x, y, width, height){
    mxSpeed = 0;
    mySpeed = 0;
    mGraph.load(BULLETLEFT);
}

Bullet::~Bullet(){

}
