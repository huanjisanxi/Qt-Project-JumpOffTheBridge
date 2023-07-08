#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QTimer>
#include <QPainter>
#include <QWidget>

#include "player.h"
#include "floor.h"

class Game:public QWidget{
    Q_OBJECT

private:
    Game();
    virtual ~Game();

    static Game* uniqueInstance;
    Player *player;
    QPixmap buffer;
    QPixmap ground;
    QPixmap water;
    QTimer engine;
    Floor *floor;
    int indexWater;

public:
    static Game* instance();

protected:   
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void paintEvent(QPaintEvent *);
    virtual void drawToBuffer();

public slots:
    void advance();
};

#endif // GAME_H
