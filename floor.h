#ifndef FLOOR_H
#define FLOOR_H

#include "staticObject.h"
#include "moveobject.h"
#include "player.h"

class Floor:public StaticObject{
    Q_OBJECT

public:
    Floor(qreal x, qreal y, qreal width, qreal height);
    ~Floor();

    bool touch(MoveObject* obj);
    bool detect(Player *player);
    bool detect(MoveObject* obj);
    void upForce(MoveObject* obj);

private:

};

#endif // FLOOR_H
