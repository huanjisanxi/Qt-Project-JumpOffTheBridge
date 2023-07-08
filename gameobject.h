#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QRectF>
#include <QPixmap>
#include <QPainter>

class GameObject:public QObject{
    Q_OBJECT

public:
    GameObject(qreal x, qreal y, qreal width, qreal height);
    virtual ~GameObject();

    QRectF const rect(){return mRect;}

    virtual void updateRect();
    virtual void draw(QPainter *painter);

    bool collision(GameObject* obj);
    QRectF mRect;

protected:
    QPixmap mGraph;

};

#endif // GAMEOBJECT_H
