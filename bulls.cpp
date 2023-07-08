#include "bulls.h"
#include "parameter.cpp"

int Bulls::temp=0;

Bulls::Bulls(qreal x,
               qreal y,
               qreal width,
               qreal height):MoveObject(x,y,width,height)
{
    mxSpeed=13;
    mySpeed=0;
    bull[0].load(YELLOWBULL1);
    bull[1].load(YELLOWBULL2);
    redbull[0].load(REDBULL1);
    redbull[1].load(REDBULL2);
    yellowbull[0].load(YELLOWBULL1);
    yellowbull[1].load(YELLOWBULL2);
    blackbull[0].load(BLACKBULL1);
    blackbull[1].load(BLACKBULL2);
    temp++;
    temp%=3;
    color=temp;
}
Bulls::~Bulls(){

}

void Bulls::draw(QPainter *painter){
    switch(color){
    case 0:
        if(indexbull <2){
            painter->drawPixmap(mRect.x()+3,mRect.y(),redbull[0].width(),redbull[0].height(),redbull[0]);
        }
        else{
            painter->drawPixmap(mRect.x()+3,mRect.y(),redbull[1].width(),redbull[1].height(),redbull[1]);
        }
        indexbull++;
        indexbull%=4;
        break;
    case 1:
        if(indexbull <2){
            painter->drawPixmap(mRect.x()+3,mRect.y(),yellowbull[0].width(),yellowbull[0].height(),yellowbull[0]);
        }
        else{
            painter->drawPixmap(mRect.x()+3,mRect.y(),yellowbull[1].width(),yellowbull[1].height(),yellowbull[1]);
        }
        indexbull++;
        indexbull%=4;
        break;
    case 2:
        if(indexbull <2){
            painter->drawPixmap(mRect.x()+3,mRect.y(),blackbull[0].width(),blackbull[0].height(),blackbull[0]);
        }
        else{
            painter->drawPixmap(mRect.x()+3,mRect.y(),blackbull[1].width(),blackbull[1].height(),blackbull[1]);
        }
        indexbull++;
        indexbull%=4;
        break;
    default: break;
    }
}

void Bulls::updateRect(){
    MoveObject::updateRect();
}
