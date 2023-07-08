#include "oldLady.h"
#include "parameter.cpp"

Oldlady::Oldlady(qreal x, qreal y, qreal width, qreal height):
    StaticObject(x,y,width,height)

{
    talk[0].load(WOMAN1);
    talk[1].load(WOMAN2);
    attack[0].load(WOMANHIT1);
    attack[1].load(WOMANHIT2);
    dogman[0].load(DOGMAN1);
    dogman[1].load(DOGMAN2);
    state=0;
    indexlady=0;
    temp=0;
}

Oldlady::~Oldlady(){}


void Oldlady::draw(QPainter *painter){
    indexlady=(indexlady+1)%4;
    switch(state){
    case 0:
        painter->drawPixmap(mRect.x(),mRect.y(),talk[0].width(),talk[0].height(),talk[0]);
        break;
    case 1:
        if(indexlady<2){
            painter->drawPixmap(mRect.x(),mRect.y(),talk[0].width(),talk[0].height(),talk[0]);
        }
        else{
            painter->drawPixmap(mRect.x(),mRect.y()-4,talk[1].width(),talk[1].height(),talk[1]);
        }
        break;
    case 2:
        if(temp<8){
            painter->drawPixmap(mRect.x(),mRect.y()-55,attack[0].width(),attack[0].height(),attack[0]);
        }
        else{
            painter->drawPixmap(mRect.x(),mRect.y()-55,attack[1].width(),attack[1].height(),attack[1]);
        }
        temp=(temp+1)%16;
        break;
    case 3:
        if(indexlady<2){
            painter->drawPixmap(mRect.x(),mRect.y(),dogman[0].width(),dogman[0].height(),dogman[0]);
        }
        else{
            painter->drawPixmap(mRect.x(),mRect.y(),dogman[1].width(),dogman[1].height(),dogman[1]);
        }
        break;
    default:break;
    }
}



bool Oldlady::detect(MoveObject* obj){
    if(obj->rect().x() + obj->rect().width() >= rect().x()
        && obj->xSpeed() >= 0){
        obj->setxSpeed(0);
        return true;
    }
    return false;
}







