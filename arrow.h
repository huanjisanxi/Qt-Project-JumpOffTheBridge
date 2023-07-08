#ifndef ARROW_H
#define ARROW_H

#include "moveobject.h"

class Arrow:public MoveObject{
    Q_OBJECT

public:
    Arrow(qreal x, qreal y, qreal width, qreal height);
    ~Arrow();

    void updateRect();
};


#endif // ARROW_H
