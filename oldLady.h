#ifndef OLDLADY_H
#define OLDLADY_H

#include "staticObject.h"
#include "moveobject.h"

class Oldlady:public StaticObject{
    Q_OBJECT
private:
    QPixmap talk[2];
    QPixmap attack[2];
    QPixmap dogman[2];

public:
    Oldlady(qreal x,qreal y,qreal width,qreal height);
    ~Oldlady();

    int state;
    int indexlady;
    int temp;
    void draw(QPainter *painter);
    bool detect(MoveObject* obj);
};

#endif //OLDLADY_H
