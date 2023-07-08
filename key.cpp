#include "key.h"
#include "parameter.cpp"

#include <QDebug>
#include <QPixmap>

Key::Key(qreal x,
        qreal y,
        qreal width,
        qreal height):
        MoveObject(x , y, width, height){
    mGraph.load(KEY);
    mxSpeed=0;
    mySpeed=0;
    beLift=false;
}

Key::~Key(){

}

void Key::updateRect(){
    if(!onFloor&&!beLift)
        mySpeed+=GRIVATY;
    if(onFloor)
        mxSpeed=0;
    mRect.translate(mxSpeed, mySpeed);
}
