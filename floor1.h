#ifndef FLOOR1_H
#define FLOOR1_H

#include "staticObject.h"
#include "moveobject.h"

class Floor1:public StaticObject{
    Q_OBJECT

public:
    Floor1(qreal x, qreal y, qreal width, qreal height);
    ~Floor1();

    bool touch(MoveObject* obj);
    bool detect(MoveObject* obj);
    void upForce(MoveObject* obj);

private:

};

#endif // FLOOR1_H
