#include "blood.h"
#include "parameter.cpp"

#include <QDebug>
#include <QPixmap>
#include <QRandomGenerator>

Blood::Blood(qreal x,
             qreal y,
             qreal width,
             qreal height,
             int index):
    MoveObject(x , y, width, height)
{
    mGraph.load(BLOOD[index]);
    do{
        mxSpeed = QRandomGenerator::global()->bounded(-10, 10);
    }while(mxSpeed == 0);
    do{
        mySpeed = QRandomGenerator::global()->bounded(-15, 10);
    }while(mySpeed == 0);
    onFloor = 0;
    beLift = 0;


}

Blood::~Blood(){

}

void Blood::updateRect(){
    if(!onFloor&&!beLift)
        mySpeed+=GRIVATY;
    if(onFloor)
        mxSpeed=0;
    mRect.translate(mxSpeed, mySpeed);
}

void Blood::draw(QPainter *painter){
    painter->drawPixmap(rect().x(), rect().y(), 1.5 * mGraph.width(), 1.5 * mGraph.height(), mGraph);
}
