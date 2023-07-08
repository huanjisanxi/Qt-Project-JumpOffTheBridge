#include <QDebug>

#include "level7.h"
#include "parameter.cpp"

Level7::Level7(QWidget *parent,QWidget *_next):main(parent),next(_next){

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
    shelf=QPixmap(SHELF);


    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(this->backgroundRole(), color);
    setPalette(palette);

    buffer = QPixmap(size());
    buffer.fill(Qt::transparent);

    player = new Player(playerX,playerY,playerW,playerH);
    floor = new Floor(floorX,floorY,floorW,floorH);
    ghost[0] = new Ghost(250,floorY-42,28,40);
    ghost[1] = new Ghost(400,floorY-42,28,40);
    ghost[2]=new Ghost(500,floorY-42,28,40);
    ghost[3]=new Ghost(640,floorY-42,28,40);
    trap[0] = new Trap(130,floorY-35,40,35);
    trap[1] = new Trap(410,floorY-35,40,35);
    trap[2] = new Trap(590,floorY-35,40,35);
    trap[3] = new Trap(718,floorY-35,40,35);
    rtrap0 = new Trap(39,floorY-215,40,35);
    rtrap0->statictrap.load(RGRASS);
    for(int i=0;i<15;i++){
        rtrap0 = new Trap(39+i*40,floorY-215,40,35);
        rtrap0->statictrap.load(RGRASS);
        rtrap.append(rtrap0);
    }
    tmp=false;


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

Level7::~Level7(){
    //-------TODO-------
}

Level7* Level7::uniqueInstance = 0;
Level7* Level7::instance(QWidget *parent,QWidget *next)
{
    if(uniqueInstance == 0)
        uniqueInstance = new Level7(parent,next);
    return uniqueInstance;
}

void Level7::exchange(){
    for(int i=0;i<2;i++){
        if(ghost[i]->mRect.x()>=380)
            ghost[i]->setxSpeed(-3);
        if(ghost[i]->mRect.x()<=170)
            ghost[i]->setxSpeed(3);
    }
    if(ghost[2]->mRect.x()<=450)
        ghost[2]->setxSpeed(3);
    if(ghost[2]->mRect.x()>=560)
        ghost[2]->setxSpeed(-3);
    if(ghost[3]->mRect.x()<=630)
        ghost[3]->setxSpeed(3);
    if(ghost[3]->mRect.x()>=690)
        ghost[3]->setxSpeed(-3);
}

void Level7::ifdead(){
    for(int i=0;i<4;i++){
        if((player->mRect.x()>=(trap[i]->mRect.x()-player->mRect.width()))&&
            (player->mRect.x()<=(trap[i]->mRect.x()+trap[i]->mRect.width()))){
            if(((player->mRect.y()+player->mRect.height())>trap[i]->mRect.y())&&
                (player->mRect.y()<trap[i]->mRect.y()+trap[i]->mRect.height())){
                player->setDeath();
                tmp=true;
            }
        }
    }
    if(player->mRect.x()>=39&&player->mRect.x()<=679){
        if(player->mRect.y()<=floorY-180){
            tmp=true;
            player->setDeath();
        }
    }
}

void Level7::ghostattack(){
    for(int i=0;i<4;i++){
        ghost[i]->state=1;
        if((player->mRect.x()>=(ghost[i]->mRect.x()-player->mRect.width()))&&
            (player->mRect.x()<=(ghost[i]->mRect.x()+ghost[i]->mRect.width()))){
            if(((player->mRect.y()+player->mRect.height())>ghost[i]->mRect.y())&&
                (player->mRect.y()<ghost[i]->mRect.y()+ghost[i]->mRect.height())){
                if(!tmp){

                    player->setySpeed(-30);
                    ghost[i]->state=0;

                }
            }
        }
    }
}

void Level7::showEvent(QShowEvent *event)
{
    reset();
    QWidget::showEvent(event); //调用基类的showEvent函数
}
void Level7::reset(){
    delete player;
    pause=false;
    player = NULL;
    player = new Player(playerX,playerY,playerW,playerH);
    tmp=false;
    indexPause=0;
}

void Level7::keyPressEvent(QKeyEvent *e){
    //-------TODO-------
    if(!pause){switch (e->key()) {
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
    }}
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

void Level7::keyReleaseEvent(QKeyEvent *e){
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

void Level7::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(rect(),buffer);

}

void Level7::drawToBuffer(){
    buffer.fill(Qt::transparent);
    QPainter painter(&buffer);
    if(!pause){
        painter.drawPixmap(0,floorY-shelf.height(),shelf);
        player->draw(&painter);
        painter.drawPixmap(600+indexWater/2,904,water);
        painter.drawPixmap(0,0,ground);

        for(int i=0;i<4;i++){
            ghost[i]->draw(&painter);
            trap[i]->draw(&painter);
        }
        for(int i=0;i<15;i++){
            rtrap[i]->draw(&painter);
        }
        indexWater++;
        indexWater%=5;
        if(player->playerState==Player::Death)
            painter.drawPixmap(0,0,QPixmap(":/images/death.png"));
    }
    else{
        painter.drawPixmap(0,0,ret[indexPause]);
    }

    update();
}

//状态更新
void Level7::advance(){
    if(player->rect().y()>1220){
        this->hide();
        reset();
        next->show();
    }
    ghostattack();
    player->updateRect();
    exchange();
    ifdead();

    for(int i=0;i<4;i++){
        ghost[i]->updateRect();
    }

    floor->detect(player);
    drawToBuffer();
}
