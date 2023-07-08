#include "ghost.h"
#include "parameter.cpp"


Ghost::Ghost(qreal x, qreal y, qreal width, qreal height)
    :MoveObject(x,y,width,height){
    g[0].load(GHOSTLEFT);
    g[1].load(GHOSTRIGHT);
    bg[0].load(BGHOSTLEFT);
    bg[1].load(BGHOSTRIGHT);
    mxSpeed=3;
    mySpeed=0;
    state=1;
    tmp=0;
    index=0;

}
Ghost::~Ghost(){}

void Ghost::draw(QPainter *painter){
    index=(index+1)%4;
    if(index<2) tmp=1;
    else tmp=0;
    if(mxSpeed<0){
        if(state)
            painter->drawPixmap(mRect.x(),mRect.y()+3*tmp,g[0]);
        else
            painter->drawPixmap(mRect.x(),mRect.y(),bg[0]);
    }
    else
        if(state)
            painter->drawPixmap(mRect.x(),mRect.y()+3*tmp,g[1]);
        else
            painter->drawPixmap(mRect.x(),mRect.y(),bg[1]);
}

void Ghost::updateRect(){
        mRect.translate(mxSpeed,mySpeed);
}


