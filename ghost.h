#ifndef GHOST_H
#define GHOST_H

#include "moveobject.h"
#include "staticObject.h"

class Ghost :public MoveObject
{
    Q_OBJECT
private:

    QPixmap g[2];
    QPixmap bg[2];
public:
    Ghost(qreal x,qreal y,qreal width,qreal height);
    ~Ghost();

    void draw(QPainter *painter);
    int state;
    int tmp;
    int index;
    void updateRect();
};

#endif // GHOST_H
