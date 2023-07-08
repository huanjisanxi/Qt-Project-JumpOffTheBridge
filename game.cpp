#include <QDebug>

#include "game.h"
#include "parameter.cpp"

Game::Game(){

    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
    engine.setInterval(20);

    engine.start();

    setFixedHeight(960);
    setFixedWidth(1200);

    QColor color(backgroundR,backgroundG,backgroundB);

    ground = QPixmap(GROUND);
    water = QPixmap(WATER);
    indexWater = 0;

    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(this->backgroundRole(), color);
    setPalette(palette);

    buffer = QPixmap(size());
    buffer.fill(Qt::transparent);

    player = new Player(playerX,playerY,playerW,playerH);
    floor = new Floor(floorX,floorY,floorW,floorH);
    //-------TODO-------
}

Game::~Game(){
    //-------TODO-------
}

Game* Game::uniqueInstance = 0;
Game* Game::instance()
{
    if(uniqueInstance == 0)
        uniqueInstance = new Game();
    return uniqueInstance;
}

void Game::keyPressEvent(QKeyEvent *e){
    //-------TODO-------
    switch (e->key()) {
    case Qt::Key_Left:
        player->moveLeft();
        break;
    case Qt::Key_Right:
        player->moveRight();
        break;
    case Qt::Key_Space:
        player->jump();
        break;
    default:
        break;
    }
}

void Game::keyReleaseEvent(QKeyEvent *e){
    //-------TODO-------
    switch(e->key()){
    case Qt::Key_Left:
    case Qt::Key_Right:
        player->moveNo();
        break;
    default:
        break;
    }
}

void Game::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(rect(),buffer);

}

void Game::drawToBuffer(){
    buffer.fill(Qt::transparent);
    QPainter painter(&buffer);

    player->draw(&painter);
    painter.drawPixmap(600+indexWater/2,904,water);
    painter.drawPixmap(0,0,ground);
    indexWater++;
    indexWater%=5;

    update();
}

//状态更新
void Game::advance(){
    player->updateRect();
    floor->detect(player);
    drawToBuffer();
}
