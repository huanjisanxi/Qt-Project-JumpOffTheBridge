#include <QDebug>

#include "level6.h"
#include "parameter.cpp"

Level6::Level6(QWidget *parent,QWidget *_next):main(parent),next(_next){

    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
    engine.setInterval(20);

    engine.start();

    setFixedHeight(960);
    setFixedWidth(1200);
    setWindowTitle("Jump Off The Bridge");

    QColor color(backgroundR,backgroundG,backgroundB);

    ground = QPixmap(SCENE4);
    water = QPixmap(WATER);
    banner1=QPixmap(BANNER61);
    banner2=QPixmap(BANNER62);
    indexWater = 0;

    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(this->backgroundRole(), color);
    setPalette(palette);

    buffer = QPixmap(2400,960);
    buffer.fill(Qt::transparent);

    player = new Player(1200+playerX,playerY,playerW,playerH);
    floor = new Floor1(1200,floorY,floorW,floorH);
    man = new Oldlady(1200+man1X,man1Y,man1W,man1H);
    dog = new Dog(560+playerX,floorY-DOGH,DOGW,DOGH);

    for(int i=0;i<4;i++){
        trap = new Trap(750+100*i,floorY-TRAPH,TRAPW,TRAPH);
        traplist.append(trap);
    }
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

Level6::~Level6(){
    //-------TODO-------
}

Level6* Level6::uniqueInstance = 0;
Level6* Level6::instance(QWidget *parent,QWidget *next)
{
    if(uniqueInstance == 0)
        uniqueInstance = new Level6(parent,next);
    return uniqueInstance;
}

void Level6::ladyattack(){
    man->detect(player);
    man->state=0;
    if(man->detect(player)&&man->state==0){
        player->setxSpeed(0);
        man->state=1;
    }
    if((man->detect(player)||player->mRect.x()>man->mRect.x()-40)&&(player->mRect.y()<man->mRect.y()-5)
        &&man->state==1){
        man->state=2;
        player->setxSpeed(-5);
    }
}

void Level6::ifdead(){
    for(int i=0;i!=traplist.size();i++){
        if((player->mRect.x()>=(traplist[i]->mRect.x()-player->mRect.width()))&&
            (player->mRect.x()<=(traplist[i]->mRect.x()+traplist[i]->mRect.width()))){
            if(((player->mRect.y()+player->mRect.height())>traplist[i]->mRect.y())&&
                (player->mRect.y()<traplist[i]->mRect.y()+traplist[i]->mRect.height())){
                player->setDeath();
            }
        }
    }
    if(player->mRect.x()<560&&player->mRect.y()>=900)
        player->setDeath();

}

void Level6::reset(){
    delete player;
    pause=false;
    player=NULL;
    player = new Player(1200+playerX,playerY,playerW,playerH);
    delete dog;
    dog=NULL;
    dog = new Dog(560+playerX,floorY-DOGH,DOGW,DOGH);
    delete man;
    man=NULL;
    man = new Oldlady(1200+man1X,man1Y,man1W,man1H);
    indexPause=0;
}

void Level6::showEvent(QShowEvent *event)
{
    reset();
    QWidget::showEvent(event); //调用基类的showEvent函数
}
void Level6::keyPressEvent(QKeyEvent *e){
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
            player->pickUp(dog);
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

void Level6::keyReleaseEvent(QKeyEvent *e){
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

void Level6::paintEvent(QPaintEvent *){
    QPainter painter(this);
    if(!pause){
        if(player->mRect.x()<1200){
            painter.drawPixmap(0,0,2400,960,buffer);
        }
        else
            painter.drawPixmap(-1200,0,2400,960,buffer);
    }
    else{
        painter.drawPixmap(0,0,2400,960,buffer);
    }
}

void Level6::drawToBuffer(){
    buffer.fill(Qt::transparent);
    QPainter painter(&buffer);

    if(!pause){
        painter.drawPixmap(1200+600+indexWater/2,904,water);
        painter.drawPixmap(0,0,ground);
        indexWater++;
        indexWater%=5;
        player->draw(&painter);
        man->draw(&painter);
        if(man->state!=3)
            dog->draw(&painter);
        for(int i=0;i!=traplist.size();i++){
            traplist[i]->draw(&painter);
        }
        if(man->state==1)
            painter.drawPixmap(1200,0,banner1);
        if(man->state==3)
            painter.drawPixmap(1200,0,banner2);
        if(player->playerState==Player::Death)
            painter.drawPixmap(0,0,QPixmap(":/images/death.png"));
    }
    else{
        painter.drawPixmap(0,0,ret[indexPause]);
    }
    update();
}

//状态更新
void Level6::advance(){
    if(player->rect().y()>1220){
        this->hide();
        reset();
        next->show();
    }
    ifdead();
    if(man->detect(dog)&&dog!=NULL){
        man->state=3;
        dog->setBeLift(false);
        player->throwing();
    }
    if(man->state!=3){
        ladyattack();
    }
    player->updateRect();
    if(man->state!=3)
        dog->updateRect();
    floor->detect(player);
    floor->detect(dog);

    drawToBuffer();
}
