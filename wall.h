#ifndef WALL_H
#define WALL_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "staticObject.h"
#include "moveobject.h"

class Wall:public StaticObject{
    Q_OBJECT

private:
    bool alive;
    int deathTimer;

public:
    Wall(qreal x, qreal y, qreal width, qreal height);
    ~Wall();

    bool detect(MoveObject* obj);
    void updateState(MoveObject * obj);
    void draw(QPainter *painter);
};

#endif // WALL_H
