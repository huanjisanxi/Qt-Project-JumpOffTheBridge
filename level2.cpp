#include <QDebug>
#include<QVector>
#include<QRandomGenerator>

#include "level2.h"
#include "parameter.cpp"
#include "bulls.h"

Level2::Level2(QWidget *parent,QWidget *_next):main(parent),next(_next){

    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
    engine.setInterval(20);

    QObject::connect(&clock, SIGNAL(timeout()), this, SLOT(bullborn()));
    clock.setInterval(800);

    engine.start();
    clock.start();

    setFixedHeight(960);
    setFixedWidth(1200);
    setWindowTitle("Jump Off The Bridge");

    QColor color(backgroundR,backgroundG,backgroundB);

    ground = QPixmap(GROUND);
    water = QPixmap(WATER);
    indexWater = 0;

    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(this->backgroundRole(), color);
    setPalette(palette);

    buffer = QPixmap(1300,960);
    buffer.fill(Qt::transparent);

    tmp=0;
    player = new Player(playerX,playerY,playerW,playerH);
    floor = new Floor(floorX,floorY,floorW,floorH);

    leftKeyPressed=false;
    rightKeyPressed=false;
    //-------TODO-------
    ret[0]=QPixmap(":/images/ret1.png");//
    ret[1]=QPixmap(":/images/ret2.png");//
    pause=false;//
    indexPause=false;//
    cursor.setMedia(QUrl("qrc:/music/cursor.mp4"));
    enter.setMedia(QUrl("qrc:/music/enter.ogg"));
}

Level2::~Level2(){
    //-------TODO-------
}
void Level2::showEvent(QShowEvent *event)
{
    reset();
    QWidget::showEvent(event); //调用基类的showEvent函数
}

void Level2::reset(){
    delete player;
    player=NULL;
    bulllist.clear();
    pause=false;
    player = new Player(playerX,playerY,playerW,playerH);
    indexPause=0;
}

Level2* Level2::uniqueInstance = 0;
Level2* Level2::instance(QWidget *parent,QWidget *next)
{
    if(uniqueInstance == 0)
        uniqueInstance = new Level2(parent,next);
    return uniqueInstance;
}

void Level2::keyPressEvent(QKeyEvent *e){
    //-------TODO-------
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

void Level2::keyReleaseEvent(QKeyEvent *e){
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


void Level2::paintEvent(QPaintEvent *){
    QPainter painter(this);
    int t = QRandomGenerator::global()->bounded(0,7);

    if(!pause){
        painter.drawPixmap(-1*t,t,1300,960,buffer);
        if(player->playerState==Player::Death)
            painter.drawPixmap(0,0,QPixmap(":/images/death.png"));
    }
    else
        painter.drawPixmap(0,0,buffer);


}

void Level2::drawToBuffer(){
    buffer.fill(Qt::transparent);
    QPainter painter(&buffer);

    if(!pause){
        painter.drawPixmap(600+indexWater/2,904,water);
        painter.drawPixmap(0,0,ground);
        indexWater++;
        indexWater%=5;
        player->draw(&painter);
        for(int i=0;i!=bulllist.size();i++){
            bulllist[i]->draw(&painter);
        }
    }
    else{
        painter.drawPixmap(0,0,ret[indexPause]);
    }
    update();
}

void Level2::ifdead(){
    for(int i=0;i!=bulllist.size();i++){
        if((player->mRect.x()>=(bulllist[i]->mRect.x()-player->mRect.width()))&&
            (player->mRect.x()<=(bulllist[i]->mRect.x()+bulllist[i]->mRect.width()))){
            if(((player->mRect.y()+player->mRect.height())>bulllist[i]->mRect.y())&&
                (player->mRect.y()<bulllist[i]->mRect.y()+bulllist[i]->mRect.height())){
                player->setDeath();
            }
        }
    }
}

//状态更新
void Level2::advance(){
    if(player->rect().y()>1220){
        this->hide();
        reset();
        next->show();
    }
    ifdead();
    player->updateRect();
    floor->detect(player);

    for(int i=0;i!=bulllist.size();i++){
        bulllist[i]->updateRect();
        floor->detect(bulllist[i]);
        if(bulllist[i]->mRect.y()>=850){
            bulllist.erase(bulllist.begin()+i);
        }
    }

    drawToBuffer();
}


void Level2::bullborn(){
    bull0 = new Bulls(bullX,bullY,bullW,bullH);
    bulllist.append(bull0);
}
