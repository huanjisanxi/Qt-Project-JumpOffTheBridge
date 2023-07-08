#include "bomb.h"
#include "parameter.cpp"

#include <QDebug>
#include <QPixmap>
#include <cmath>

Bomb::Bomb(qreal x,
               qreal y,
               qreal width,
               qreal height):
    MoveObject(x, y, width, height){
    mxSpeed = -5;
    mySpeed = -omega * amplitude * std::sin(omega * (x - bombX));
    mGraph.load(BOMB);
}

Bomb::~Bomb(){

}

void Bomb::updateState(){
    setySpeed(-omega * amplitude * std::sin(omega * (rect().x() - bombX)));
}

void Bomb::updateRect(){
    updateState();
    MoveObject::updateRect();
}
