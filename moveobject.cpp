#include "moveobject.h"
#include "parameter.cpp"

#include <QDebug>

MoveObject::MoveObject(qreal x,
                       qreal y,
                       qreal width,
                       qreal height):GameObject(x,y,width,height){
    //-------TODO-------
}

MoveObject::~MoveObject(){
    //-------TODO-------
}

//更新物体位置
void MoveObject::updateRect(){
    if(!onFloor)
        mySpeed+=GRIVATY;
    mRect.translate(mxSpeed, mySpeed);
}
