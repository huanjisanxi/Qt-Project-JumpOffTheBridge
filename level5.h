#ifndef LEVEL5_H
#define LEVEL5_H

#include <QGraphicsView>
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include<QVector>
#include <QMediaPlayer>


#include "player.h"
#include "floor.h"
#include "activeBoard.h"
#include "bullet.h"

class Level5:public QWidget{
    Q_OBJECT

private:
    Level5(QWidget *parent=NULL,QWidget *next=NULL);
    virtual ~Level5();

    static Level5* uniqueInstance;
    Player *player;
    QPixmap buffer;
    QPixmap ground;
    QPixmap water;
    QPixmap ret[2];
    QTimer engine;
    Floor *floor;
    ActiveBoard *board;
    Bullet *bullet;
    int indexWater;
    bool leftKeyPressed;
    bool rightKeyPressed;
    QWidget* main;
    bool pause;//
    bool indexPause;//
    QWidget* next;
    QMediaPlayer cursor;
    QMediaPlayer enter;

public:
    static Level5* instance(QWidget *parent,QWidget *next);
    void drawToBuffer();
    void ifdead();
    void drawBullet(QPainter *);
    void shootBullet();
    void reset();

protected:
    void showEvent(QShowEvent *event);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void paintEvent(QPaintEvent *);

public slots:
    void advance();
};

#endif // LEVEL5_H
