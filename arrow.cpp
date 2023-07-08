#include "arrow.h"
#include "parameter.cpp"

#include <QDebug>
#include <QPixmap>

Arrow::Arrow(qreal x,
         qreal y,
         qreal width,
         qreal height):
    MoveObject(x , y, width, height){
    mGraph.load(WEAPON);
    mxSpeed=0;
    mySpeed=0;
    beLift=false;
}

Arrow::~Arrow(){

}

void Arrow::updateRect(){
    if(!onFloor&&!beLift)
        mySpeed+=GRIVATY;
    if(onFloor)
        mxSpeed=0;
    mRect.translate(mxSpeed, mySpeed);
}
