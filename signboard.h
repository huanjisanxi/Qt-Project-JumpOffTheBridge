#ifndef SIGNBOARD_H
#define SIGNBOARD_H

#include "staticObject.h"
#include "moveobject.h"

class SignBoard:public StaticObject{
    Q_OBJECT

private:
    bool touched;

public:
    SignBoard(qreal x, qreal y, qreal width, qreal height);
    ~SignBoard();

    bool detect(MoveObject* obj);
    bool is_touched();
};

#endif // SIGNBOARD_H
