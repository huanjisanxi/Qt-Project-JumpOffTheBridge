#ifndef LEVEL3_H
#define LEVEL3_H

#include <QGraphicsView>
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QMediaPlayer>


#include "key.h"
#include "wall.h"
#include "signboard.h"
#include "player.h"
#include "floor.h"

class Level3:public QWidget{
    Q_OBJECT

private:
    Level3(QWidget *parent=NULL,QWidget *next=NULL);
    virtual ~Level3();

    static Level3* uniqueInstance;
    QPixmap buffer;
    QPixmap ground;
    QPixmap water;
    QPixmap banner;
    QPixmap ret[2];
    QTimer engine;
    Player *player;
    Floor *floor;
    SignBoard *board;
    Key *key;
    Wall *wall;
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
    static Level3* instance(QWidget *parent,QWidget *next);
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

#endif // LEVEL3_H
