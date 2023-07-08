#include <QDebug>
#include<QVector>
#include<QRandomGenerator>

#include "level8.h"
#include "parameter.cpp"

Level8::Level8(QWidget *parent,QWidget *_next):main(parent),next(_next){
    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
    engine.setInterval(20);

    engine.start();

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

    buffer = QPixmap(size());
    buffer.fill(Qt::transparent);

    player = new Player(playerX, playerY, playerW, playerH);
    floor = new Floor(floorX, floorY, floorW, floorH);
    arrowShelf = new ArrowShelf(shelfX, shelfY, shelfW, shelfH);
    dragon = new Dragon(dragonX, dragonY, dragonW, dragonH);
    leftKeyPressed=false;
    rightKeyPressed=false;
    ret[0]=QPixmap(":/images/ret1.png");//
    ret[1]=QPixmap(":/images/ret2.png");//
    pause=false;//
    indexPause=false;//
    cursor.setMedia(QUrl("qrc:/music/cursor.mp4"));
    enter.setMedia(QUrl("qrc:/music/enter.ogg"));
}

Level8::~Level8(){

}

Level8* Level8::uniqueInstance = 0;
Level8* Level8::instance(QWidget *parent,QWidget *next)
{
    if(uniqueInstance == 0)
        uniqueInstance = new Level8(parent,next);
    return uniqueInstance;
}

void Level8::reset(){
    delete player;
    player = NULL;
    pause=false;
    player = new Player(playerX,playerY,playerW,playerH);

    arrowList.clear();
    bombList.clear();

    delete dragon;
    dragon = NULL;
    dragon = new Dragon(dragonX, dragonY, dragonW, dragonH);
    indexPause=0;
}
void Level8::showEvent(QShowEvent *event)
{
    reset();
    QWidget::showEvent(event); //调用基类的showEvent函数
}

void Level8::keyPressEvent(QKeyEvent *e){
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
        case Qt::Key_W:
            for(int i = 0; i < arrowList.size(); i++){
                player->pickUp(arrowList[i]);
            }
            break;
        case Qt::Key_E:
            player->throwing();
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

void Level8::keyReleaseEvent(QKeyEvent *e){
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

void Level8::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(rect(),buffer);
}

void Level8::drawToBuffer(){
    buffer.fill(Qt::transparent);
    QPainter painter(&buffer);

    if(!pause){
        player->draw(&painter);
        for(int i=0;i!=arrowList.size();i++){
            arrowList[i]->draw(&painter);
        }
        for(int i=0;i!=bombList.size();i++){
            bombList[i]->draw(&painter);
        }
        painter.drawPixmap(600+indexWater/2,904,water);
        painter.drawPixmap(0,0,ground);
        indexWater++;
        indexWater%=5;
        arrowShelf->draw(&painter);

        dragon->draw(&painter);
        if(player->playerState==Player::Death)
            painter.drawPixmap(0,0,QPixmap(":/images/death.png"));
    }
    else{
        painter.drawPixmap(0,0,ret[indexPause]);
    }

    update();
}

void Level8::ifdead(){
    for(int i=0;i != bombList.size();i++){
        if((player->mRect.x()>=(bombList[i]->mRect.x()-player->mRect.width()))&&
            (player->mRect.x()<=(bombList[i]->mRect.x()+ bombList[i]->mRect.width()))){
            if(((player->mRect.y()+player->mRect.width())>bombList[i]->mRect.y())&&
                (player->mRect.y()<bombList[i]->mRect.y()+bombList[i]->mRect.width())){
                player->setDeath();
            }
        }
    }
    if(dragon->isAlive()){
        if(player->rect().x() + player->rect().width() >= dragon->rect().x()){
            player->setDeath();
        }
    }
}

void Level8::generateArrow(){
    bool is_there = 0;
    for(int i = 0; i != arrowList.size(); i++){
        if(arrowList[i]->rect().x() == arrowX && arrowList[i]->rect().y() == arrowY){
            is_there = 1;
            break;
        }
    }
    if(!is_there){
        arrowList.append(new Arrow(arrowX, arrowY, arrowW, arrowH));
    }
}

void Level8::deleteArrow(){
    for(int i = 0; i < arrowList.size(); i++){
        if(arrowList[i]->rect().x() + arrowList[i]->rect().width() >= dragon->rect().x()
            || arrowList[i]->rect().x() + arrowList[i]->rect().width() < 0){
            delete arrowList[i];
            arrowList[i] = NULL;
            arrowList.erase(arrowList.begin() + i);
        }
    }
}

void Level8::advance(){
    if(player->rect().y()>1220){
        this->hide();
        reset();
        next->show();
    }
    ifdead();

    player->updateRect();
    floor->detect(player);
    for(int i = 0; i != bombList.size(); i++){
        bombList[i]->updateRect();
    }

    generateArrow();

    if(dragon->isShootBomb()){
        bombList.append(new Bomb(bombX, bombY, bombW, bombH));
    }

    for(int i=0;i!=arrowList.size();i++){
        floor->detect(arrowList[i]);
        arrowList[i]->updateRect();
    }

    dragon->updateState(arrowList);

    deleteArrow();

    drawToBuffer();
}
