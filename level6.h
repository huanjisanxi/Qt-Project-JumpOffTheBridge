#ifndef LEVEL6_H
#define LEVEL6_H

#include <QGraphicsView>
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QVector>
#include <QMediaPlayer>

#include "player.h"
#include "floor1.h"
#include "oldLady.h"
#include "dog.h"
#include "trap.h"

class Level6:public QWidget{
    Q_OBJECT

private:
    Level6(QWidget *parent=NULL,QWidget *next=NULL);
    virtual ~Level6();

    static Level6* uniqueInstance;
    Player *player;
    QPixmap buffer;
    QPixmap ground;
    QPixmap water;
    QPixmap ret[2];
    QTimer engine;
    Floor1 *floor;
    int indexWater;
    Dog *dog;
    Oldlady *man;
    Trap* trap;
    QVector<Trap*> traplist;
    QPixmap banner1;
    QPixmap banner2;
    bool leftKeyPressed;
    bool rightKeyPressed;
    QWidget* main;
    bool pause;//
    bool indexPause;//
    QWidget* next;
    QMediaPlayer cursor;
    QMediaPlayer enter;

public:
    static Level6* instance(QWidget *parent,QWidget *next);
    void ifdead();
    void reset();

protected:
    void showEvent(QShowEvent *event);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void paintEvent(QPaintEvent *);
    void drawToBuffer();
    void ladyattack();

public slots:
    void advance();
};

#endif // LEVEL6_H
