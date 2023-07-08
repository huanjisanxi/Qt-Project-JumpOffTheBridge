#include "gameobject.h"

GameObject::GameObject(qreal x,
                       qreal y,
                       qreal width,
                       qreal height):mRect(x,y,width,height)
{
    //-------TODO-------
}

GameObject::~GameObject(){
    //-------TODO-------
}

void GameObject::updateRect(){

}

void GameObject::draw(QPainter *painter){
    painter->drawPixmap(mRect.x(),mRect.y(),mRect.width(),mRect.height(),mGraph);
}

bool GameObject::collision(GameObject* obj){
    return mRect.intersects(obj->mRect);
}
