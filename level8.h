#ifndef LEVEL8_H
#define LEVEL8_H

#include <QGraphicsView>
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QVector>
#include <QMediaPlayer>

#include "player.h"
#include "floor.h"
#include "arrow.h"
#include "arrowshelf.h"
#include "dragon.h"
#include "bomb.h"

class Level8:public QWidget{
    Q_OBJECT;

private:
    Level8(QWidget *parent=NULL,QWidget *next=NULL);
    ~Level8();

    static Level8* uniqueInstance;
    Player *player;
    QPixmap buffer;
    QPixmap ground;
    QPixmap water;
    QPixmap ret[2];
    QTimer engine;

    Floor *floor;
    QVector<Arrow*> arrowList;
    ArrowShelf *arrowShelf;
    Dragon *dragon;
    QVector<Bomb*> bombList;

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
    static Level8* instance(QWidget *parent,QWidget *next);

protected:
    void showEvent(QShowEvent *event);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void paintEvent(QPaintEvent *);
    void drawToBuffer();
    void ifdead();
    void generateArrow();
    void deleteArrow();
    void detectPlayer();
    void reset();

public slots:
    void advance();
};

#endif // LEVEL8_H
