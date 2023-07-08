#ifndef FLOOR2_H
#define FLOOR2_H

#include "staticObject.h"
#include "moveobject.h"

class Floor2:public StaticObject{
    Q_OBJECT

public:
    Floor2(qreal x, qreal y, qreal width, qreal height);
    ~Floor2();

    bool touch(MoveObject* obj);
    bool detect(MoveObject* obj);
    void upForce(MoveObject* obj);

private:

};

#endif // FLOOR2_H
