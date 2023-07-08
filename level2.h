#ifndef LEVEL2_H
#define LEVEL2_H

#include <QGraphicsView>
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include<QVector>
#include <QMediaPlayer>


#include "player.h"
#include "floor.h"
#include "bulls.h"

class Level2:public QWidget{
    Q_OBJECT

private:
    Level2(QWidget *parent=NULL,QWidget *next=NULL);
    virtual ~Level2();

    static Level2* uniqueInstance;
    Player *player;
    QPixmap buffer;
    QPixmap ground;
    QPixmap water;
    QPixmap ret[2];
    QTimer engine;
    Floor *floor;
    int indexWater;

    QTimer clock;
    Bulls *bull0;
    QVector<Bulls*> bulllist;
    bool leftKeyPressed;
    bool rightKeyPressed;
    QWidget* main;
    bool pause;//
    bool indexPause;//
    QWidget* next;
    QMediaPlayer cursor;
    QMediaPlayer enter;

public:
    static Level2* instance(QWidget *parent,QWidget *next);
    void drawToBuffer();
    void ifdead();
    void reset();
    int tmp;

protected:
    void showEvent(QShowEvent *event);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void paintEvent(QPaintEvent *);

public slots:
    void advance();
    void bullborn();
};

#endif // Level2_H
