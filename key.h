#ifndef KEY_H
#define KEY_H

#include "moveobject.h"

class Key:public MoveObject{
    Q_OBJECT

public:
    Key(qreal x, qreal y, qreal width, qreal height);
    ~Key();

    void updateRect();
};


#endif // KEY_H
