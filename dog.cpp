#include "dog.h"
#include "parameter.cpp"

#include <QDebug>
#include <QPixmap>

Dog::Dog(qreal x,
         qreal y,
         qreal width,
         qreal height):
    MoveObject(x , y, width, height){
    mxSpeed=0;
    mySpeed=0;
    actdog[0].load(DOG1);
    actdog[1].load(DOG2);
    actdog[2].load(DOG3);
    beLift=false;
    tmp=0;
}

Dog::~Dog(){

}

void Dog::updateRect(){
    if(!onFloor&&!beLift)
        mySpeed+=GRIVATY;
    if(onFloor)
        mxSpeed=0;
    mRect.translate(mxSpeed, mySpeed);
}

void Dog::draw(QPainter *painter){
    tmp=(tmp+1)%6;
    if(tmp<2)
       painter->drawPixmap(mRect.x(),mRect.y(),actdog[0].width(),actdog[0].height(),actdog[0]);
    else if(tmp>=2&&tmp<4)
       painter->drawPixmap(mRect.x(),mRect.y(),actdog[1].width(),actdog[1].height(),actdog[1]);
    else
       painter->drawPixmap(mRect.x(),mRect.y()+2,actdog[2].width(),actdog[2].height(),actdog[2]);
}
