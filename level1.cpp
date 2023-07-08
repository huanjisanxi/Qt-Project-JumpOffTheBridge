#include <QDebug>

#include "level1.h"
#include "parameter.cpp"

Level1::Level1(QWidget *parent,QWidget *_next):main(parent),next(_next)
{
    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
    engine.setInterval(20);

    engine.start();

    setFixedHeight(960);
    setFixedWidth(1200);
    setWindowTitle("Jump Off The Bridge");

    QColor color(backgroundR,backgroundG,backgroundB);

    ground = QPixmap(GROUND);
    water = QPixmap(WATER);
    banner = QPixmap(BANNER1);

    indexWater = 0;

    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(this->backgroundRole(), color);
    setPalette(palette);

    buffer = QPixmap(size());
    buffer.fill(Qt::transparent);

    player = new Player(playerX,playerY,playerW,playerH);
    floor = new Floor(floorX,floorY,floorW,floorH);
    board = new SignBoard(boardX, boardY, boardW, boardH);

    leftKeyPressed=false;
    rightKeyPressed=false;

    ret[0]=QPixmap(":/images/ret1.png");//
    ret[1]=QPixmap(":/images/ret2.png");//
    pause=false;//
    indexPause=false;//
    cursor.setMedia(QUrl("qrc:/music/cursor.mp4"));
    enter.setMedia(QUrl("qrc:/music/enter.ogg"));
}

Level1::~Level1(){

}

void Level1::showEvent(QShowEvent *event)
{
    reset();
    QWidget::showEvent(event); //调用基类的showEvent函数
}

Level1* Level1::uniqueInstance = 0;
Level1* Level1::instance(QWidget *parent,QWidget *next){
    if(uniqueInstance == 0)
        uniqueInstance = new Level1(parent,next);
    return uniqueInstance;
}

void Level1::reset(){
    delete player;
    player = NULL;
    pause=false;
    player = new Player(playerX, playerY, playerW, playerH);
    indexPause=0;
}

void Level1::keyPressEvent(QKeyEvent *e){//
    if(!pause){
        switch (e->key()) {
        case Qt::Key_Left:
            player->moveLeft();
            leftKeyPressed=true;
            break;
        case Qt::Key_Right:
            player->moveRight();
            rightKeyPressed=true;
            break;
        case Qt::Key_Space:
            player->jump();
            break;
        case Qt::Key_R:
            reset();
            break;
        case Qt::Key_Escape:
            pause=true;
            break;
        default:
            break;
        }
    }
    else{
        switch (e->key()){
        case Qt::Key_Left:
            cursor.setPosition(0);
            cursor.play();
            indexPause=false;
            break;
        case Qt::Key_Right:
            cursor.setPosition(0);
            cursor.play();
            indexPause=true;
            break;
        case Qt::Key_Return:
            enter.setPosition(0);
            enter.play();
            if(!indexPause){
                pause=false;
                this->reset();
            }
            else{
                this->hide();
                main->show();
            }
            break;
        default:
            break;
        }
    }
}

void Level1::keyReleaseEvent(QKeyEvent *e){
    //-------TODO-------
    switch(e->key()){
    case Qt::Key_Left:
        if(!rightKeyPressed)
            player->moveNo();
        leftKeyPressed=false;
        break;
    case Qt::Key_Right:
        if(!leftKeyPressed)
            player->moveNo();
        rightKeyPressed=false;
        break;
    default:
        break;
    }
}

void Level1::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(rect(),buffer);

    if(player->playerState==Player::Death)
        painter.drawPixmap(0,0,QPixmap(":/images/death.png"));

}

void Level1::drawBanner(QPainter *painter){
    if(board->is_touched()){
        painter->drawPixmap(0,0,banner);
    }
}

void Level1::drawToBuffer(){//
    buffer.fill(Qt::transparent);
    QPainter painter(&buffer);
    if(!pause){

        player->draw(&painter);
        painter.drawPixmap(600+indexWater/2,904,water);
        painter.drawPixmap(0,0,ground);
        board->draw(&painter);
        indexWater++;
        indexWater%=5;
        drawBanner(&painter);

    }
    else{
        painter.drawPixmap(0,0,ret[indexPause]);
    }
    update();
}

//状态更新
void Level1::advance(){
    if(player->rect().y()>1220){
        this->hide();
        reset();
        next->show();
    }
    player->updateRect();
    floor->detect(player);
    board->detect(player);
    drawToBuffer();
}

















