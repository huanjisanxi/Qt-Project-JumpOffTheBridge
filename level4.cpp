#include <QDebug>

#include "level4.h"
#include "parameter.cpp"

Level4::Level4(QWidget *parent,QWidget *_next):main(parent),next(_next){

    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
    engine.setInterval(20);

    engine.start();

    setFixedHeight(960);
    setFixedWidth(1200);
    setWindowTitle("Jump Off The Bridge");

    QColor color(backgroundR,backgroundG,backgroundB);

    ground = QPixmap(SCENE4);
    water = QPixmap(WATER);
    bridge = QPixmap(BRIDGE);
    banner = QPixmap(BANNER4);
    man1 = QPixmap(MAN1);
    man2 = QPixmap(MAN2);

    indexWater = 0;
    indexBoard = 0;

    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(this->backgroundRole(), color);
    setPalette(palette);

    buffer = QPixmap(3600,960);
    buffer.fill(Qt::transparent);

    player = new Player(1200+playerX,playerY,playerW,playerH);
    floor = new Floor2(1200,floorY,floorW,floorH);
    board = new SignBoard(1200+man1X, man1Y, man1W, man1H);
    leftKeyPressed=false;
    rightKeyPressed=false;
    ret[0]=QPixmap(":/images/ret1.png");//
    ret[1]=QPixmap(":/images/ret2.png");//
    pause=false;//
    indexPause=false;//
    cursor.setMedia(QUrl("qrc:/music/cursor.mp4"));
    enter.setMedia(QUrl("qrc:/music/enter.ogg"));
}

Level4::~Level4(){
    //-------TODO-------
}

Level4* Level4::uniqueInstance = 0;
Level4* Level4::instance(QWidget *parent,QWidget *next)
{
    if(uniqueInstance == 0)
        uniqueInstance = new Level4(parent,next);
    return uniqueInstance;
}

void Level4::showEvent(QShowEvent *event)
{
    reset();
    QWidget::showEvent(event); //调用基类的showEvent函数
}
void Level4::reset(){
    delete player;
    player=NULL;
    pause=false;
    player = new Player(1200+playerX,playerY,playerW,playerH);

    delete board;
    board=NULL;
    board = new SignBoard(1200+man1X,man1Y,man1W,man1H);
    indexPause=0;
}

void Level4::keyPressEvent(QKeyEvent *e){
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

void Level4::keyReleaseEvent(QKeyEvent *e){
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

void Level4::paintEvent(QPaintEvent *){
    QPainter painter(this);
    if(!pause){
        if(player->mRect.x()<1200){
            painter.drawPixmap(0,0,3600,960,buffer);
        }
        else if(player->rect().x() < 2400){
            painter.drawPixmap(-1200,0,3600,960,buffer);
        }
        else{
            painter.drawPixmap(-2400,0,3600,960,buffer);
        }
    }
    else{
        painter.drawPixmap(0,0,buffer);
    }
}

void Level4::drawBridge(QPainter *painter){
    if(player->rect().x() > 400 + 1200 && player->rect().x() <= 2400){
        painter->drawPixmap(player->rect().x() - 1180, bridgeY, bridge);
    }
}

void Level4::drawMan(QPainter *painter){
    if(board->is_touched()){
        indexBoard  = (indexBoard + 1) % 4;
        switch(indexBoard){
        case 0:
        case 1:
            painter->drawPixmap(1200 + man1X, man1Y, man1);
            break;
        case 2:
        case 3:
            painter->drawPixmap(1200 + man2X, man2Y, man2);
            break;
        }
    }
    else{
        indexBoard = 0;
        painter->drawPixmap(1200 + man1X, man1Y, man1);
    }
}

void Level4::drawBanner(QPainter *painter){
    if(board->is_touched()){
        painter->drawPixmap(1200,0,banner);
    }
}

void Level4::drawToBuffer(){
    buffer.fill(Qt::transparent);
    QPainter painter(&buffer);

    if(!pause){
        if(player->rect().x() > 3600){
            player->setPos(player->rect().x() - 1200, player->rect().y());
        }
        player->draw(&painter);

        drawBridge(&painter);

        painter.drawPixmap(-indexWater/2,904,water);
        painter.drawPixmap(1200+600+indexWater/2,904,water);
        painter.drawPixmap(1800+600+indexWater/2,904,water);
        painter.drawPixmap(2400+600+indexWater/2,904,water);
        painter.drawPixmap(0,0,ground);
        indexWater++;
        indexWater%=5;

        drawMan(&painter);
        drawBanner(&painter);
        if(player->playerState==Player::Death)
            painter.drawPixmap(0,0,QPixmap(":/images/death.png"));
    }
    else{
        painter.drawPixmap(0,0,ret[indexPause]);
    }

    update();
}

//状态更新
void Level4::advance(){
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
