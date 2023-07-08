#include <QDebug>

#include "level3.h"
#include "parameter.cpp"

Level3::Level3(QWidget *parent,QWidget *_next):main(parent),next(_next){

    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
    engine.setInterval(20);

    engine.start();

    setFixedHeight(960);
    setFixedWidth(1200);
    setWindowTitle("Jump Off The Bridge");

    QColor color(backgroundR,backgroundG,backgroundB);

    ground = QPixmap(GROUND);
    water = QPixmap(WATER);
    banner = QPixmap(BANNER3);

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
    key = new Key(keyX, keyY, keyW, keyH);
    wall = new Wall(wallX, wallY, wallW, wallH);
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

Level3::~Level3(){
    //-------TODO-------
}

Level3* Level3::uniqueInstance = 0;
Level3* Level3::instance(QWidget *parent,QWidget *next)
{
    if(uniqueInstance == 0)
        uniqueInstance = new Level3(parent,next);
    return uniqueInstance;
}
void Level3::showEvent(QShowEvent *event)
{
    reset();
    QWidget::showEvent(event); //调用基类的showEvent函数
}

void Level3::reset(){
    pause=false;
    delete player;
    player=NULL;
    player = new Player(playerX,playerY,playerW,playerH);

    delete key;
    key = NULL;
    key = new Key(keyX, keyY, keyW, keyH);

    delete wall;
    wall = NULL;
    wall = new Wall(wallX, wallY, wallW, wallH);
    indexPause=0;
}

void Level3::keyPressEvent(QKeyEvent *e){
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
            player->pickUp(key);
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
    }       else{
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

void Level3::keyReleaseEvent(QKeyEvent *e){
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

void Level3::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(rect(),buffer);

}

void Level3::drawBanner(QPainter *painter){
    if(board->is_touched()){
        painter->drawPixmap(0,0,banner);
    }
}

void Level3::drawToBuffer(){
    buffer.fill(Qt::transparent);
    QPainter painter(&buffer);

    if(!pause){
        key->draw(&painter);
        player->draw(&painter);
        painter.drawPixmap(600+indexWater/2,904,water);
        painter.drawPixmap(0,0,ground);
        indexWater++;
        indexWater%=5;
        board->draw(&painter);
        drawBanner(&painter);
        wall->draw(&painter);
    }
    else{
        painter.drawPixmap(0,0,ret[indexPause]);
    }

    update();
}

//状态更新
void Level3::advance(){
    if(player->rect().y()>1220){
        this->hide();
        reset();
        next->show();
    }
    wall->detect(player);

    player->updateRect();
    key->updateRect();
    wall->updateState(key);

    floor->detect(player);
    floor->detect(key);
    board->detect(player);

    drawToBuffer();
}
