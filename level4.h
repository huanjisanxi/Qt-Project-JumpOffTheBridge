#ifndef LEVEL4_H
#define LEVEL4_H

#include <QGraphicsView>
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QMediaPlayer>


#include "player.h"
#include "floor2.h"
#include "signboard.h"

class Level4:public QWidget{
    Q_OBJECT

private:
    Level4(QWidget *parent=NULL,QWidget *next=NULL);
    virtual ~Level4();

    static Level4* uniqueInstance;
    Player *player;
    QPixmap buffer;
    QPixmap ground;
    QPixmap water;
    QPixmap man1;
    QPixmap man2;
    QPixmap banner;
    QPixmap bridge;
    QPixmap ret[2];
    QTimer engine;
    Floor2 *floor;
    int indexWater;
    SignBoard* board;
    int indexBoard;
    bool leftKeyPressed;
    bool rightKeyPressed;
    QWidget* main;
    bool pause;//
    bool indexPause;//
    QWidget* next;
    QMediaPlayer cursor;
    QMediaPlayer enter;

public:
    static Level4* instance(QWidget *parent,QWidget *next);

protected:
    void showEvent(QShowEvent *event);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void paintEvent(QPaintEvent *);
    void drawBridge(QPainter *);
    void drawMan(QPainter *);
    void drawBanner(QPainter *);
    void drawToBuffer();
    void reset();

public slots:
    void advance();
};

#endif // LEVEL4_H
