#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include "gameobject.h"

class StaticObject:public GameObject{
    Q_OBJECT

public:
    StaticObject(qreal x, qreal y, qreal width, qreal height);
    virtual ~StaticObject();
};

#endif // STATICOBJECT_H
