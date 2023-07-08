#include <QDebug>

#include "level5.h"
#include "parameter.cpp"

Level5::Level5(QWidget *parent,QWidget *_next):main(parent),next(_next){

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

    player = new Player(playerX,playerY,playerW,playerH);
    floor = new Floor(floorX,floorY,floorW,floorH);
    board = new ActiveBoard(activeBoardX, activeBoardY, activeBoardW, activeBoardH);
    bullet = new Bullet(bulletX, bulletY, bulletW, bulletH);
    //-------TODO-------
    leftKeyPressed=false;
    rightKeyPressed=false;
    ret[0]=QPixmap(":/images/ret1.png");//
    ret[1]=QPixmap(":/images/ret2.png");//
    pause=false;//
    indexPause=false;//
    cursor.setMedia(QUrl("qrc:/music/cursor.mp4"));
    enter.setMedia(QUrl("qrc:/music/enter.ogg"));
}

Level5::~Level5(){
    //-------TODO-------
}

Level5* Level5::uniqueInstance = 0;
Level5* Level5::instance(QWidget *parent,QWidget *next)
{
    if(uniqueInstance == 0)
        uniqueInstance = new Level5(parent,next);
    return uniqueInstance;
}

void Level5::showEvent(QShowEvent *event)
{
    reset();
    QWidget::showEvent(event); //调用基类的showEvent函数
}
void Level5::reset(){
    delete player;
    player=NULL;
    player = new Player(playerX,playerY,playerW,playerH);

    delete board;
    board = NULL;
    board = new ActiveBoard(activeBoardX, activeBoardY, activeBoardW, activeBoardH);

    pause=false;
    delete bullet;
    bullet = NULL;
    bullet = new Bullet(bulletX, bulletY, bulletW, bulletH);
    indexPause=0;
}

void Level5::keyPressEvent(QKeyEvent *e){
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

void Level5::keyReleaseEvent(QKeyEvent *e){
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

void Level5::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(rect(),buffer);

}

void Level5::drawBullet(QPainter* painter){
    if(bullet->xSpeed() != 0){
        bullet->draw(painter);
    }
}

void Level5::drawToBuffer(){
    buffer.fill(Qt::transparent);
    QPainter painter(&buffer);

    if(!pause){
        player->draw(&painter);
        painter.drawPixmap(600+indexWater/2,904,water);
        painter.drawPixmap(0,0,ground);
        indexWater++;
        indexWater%=5;
        board->draw(&painter);
        drawBullet(&painter);
        if(player->playerState==Player::Death)
            painter.drawPixmap(0,0,QPixmap(":/images/death.png"));
    }
    else{
        painter.drawPixmap(0,0,ret[indexPause]);
    }

    update();
}

void Level5::ifdead(){
    if(player->rect().x() + player->rect().width() >= bullet->rect().x()
        && player->rect().x() <= bullet->rect().x() + bullet->rect().width()
        && player->rect().y() + player->rect().height() >= bullet->rect().y()
        && player->rect().y() <= bullet->rect().y() + bullet->rect().height()){
            player->setDeath();
    }
}

void Level5::shootBullet(){
    if(board->is_active()){
            bullet->setxSpeed(-20);
    }
}

//状态更新
void Level5::advance(){
    if(player->rect().y()>1220){
            this->hide();
            reset();
            next->show();
    }

    shootBullet();

    ifdead();

    player->updateRect();
    board->updateRect(player);
    bullet->updateRect();

    floor->detect(player);
    floor->detect(board);

    drawToBuffer();
}
