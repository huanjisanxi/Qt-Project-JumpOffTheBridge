#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H

#include "gameobject.h"

class MoveObject:public GameObject{
    Q_OBJECT

public:
    MoveObject(qreal x, qreal y, qreal width, qreal height);
    virtual ~MoveObject();

    qreal const xSpeed(){return mxSpeed;}
    qreal const ySpeed(){return mySpeed;}

    void setOnFloor(const bool& _){onFloor=_;}
    bool onfloor(){return onFloor;}

    void setxSpeed(const qreal& xSpeed){mxSpeed=xSpeed;}
    void setySpeed(const qreal& ySpeed){mySpeed=ySpeed;}
    void setPos(const qreal& x,const qreal& y){
        mRect.setRect(x, y, mRect.width(), mRect.height());
    }

    //更新物体位置
    virtual void updateRect();

    void setBeLift(bool val){beLift=val;}

protected:
    qreal mxSpeed;
    qreal mySpeed;
    bool onFloor;
    bool beLift;
    MoveObject* father;

};

#endif // MOVEOBJECT_H
