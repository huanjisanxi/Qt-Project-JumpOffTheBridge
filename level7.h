#ifndef LEVEL7_H
#define LEVEL7_H

#include <QGraphicsView>
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QVector>
#include <QMediaPlayer>

#include "player.h"
#include "floor.h"
#include "trap.h"
#include "ghost.h"

class Level7:public QWidget{
    Q_OBJECT

private:
    Level7(QWidget *parent=NULL,QWidget *next=NULL);
    virtual ~Level7();

    static Level7* uniqueInstance;
    Player *player;
    QPixmap buffer;
    QPixmap ground;
    QPixmap water;
    QPixmap ret[2];
    QTimer engine;
    Floor *floor;
    int indexWater;
    QPixmap shelf;
    Ghost *ghost[4];
    Trap *trap[4];
    Trap* rtrap0;
    QVector<Trap*> rtrap;
    bool tmp;
    void exchange();
    void ifdead();
    void ghostattack();
    void reset();
    bool leftKeyPressed;
    bool rightKeyPressed;
    QWidget* main;
    bool pause;//
    bool indexPause;//
    QWidget* next;
    QMediaPlayer cursor;
    QMediaPlayer enter;
public:
    static Level7* instance(QWidget *parent,QWidget *next);

protected:
    void showEvent(QShowEvent *event);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void paintEvent(QPaintEvent *);
    void drawToBuffer();

public slots:
    void advance();
};

#endif // LEVEL7_H
