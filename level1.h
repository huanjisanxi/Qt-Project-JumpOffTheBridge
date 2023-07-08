#ifndef LEVEL1_H
#define LEVEL1_H

#include <QGraphicsView>
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QMediaPlayer>


#include "player.h"
#include "floor.h"
#include "signboard.h"

class Level1:public QWidget{
    Q_OBJECT

private:
    Level1(QWidget *parent=NULL,QWidget *next=NULL);
    virtual ~Level1();

    static Level1* uniqueInstance;
    Player *player;
    QPixmap buffer;
    QPixmap ground;
    QPixmap water;
    QPixmap banner;
    QPixmap ret[2];
    QTimer engine;
    Floor *floor;
    int indexWater;
    SignBoard* board;
    bool leftKeyPressed;
    bool rightKeyPressed;
    QWidget* main;
    bool pause;
    bool indexPause;
    QWidget* next;
    QMediaPlayer cursor;
    QMediaPlayer enter;

public:
    static Level1* instance(QWidget *parent,QWidget *next);
    void drawBanner(QPainter *);
    void drawToBuffer();
    void reset();

protected:
    void showEvent(QShowEvent *event);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void paintEvent(QPaintEvent *);

public slots:
    void advance();
};

#endif // LEVEL1_H
