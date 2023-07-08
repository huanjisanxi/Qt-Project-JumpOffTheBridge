#include "mainwindow.h"

MainWindow* MainWindow::uniqueInstance = 0;
MainWindow* MainWindow::instance()
{
    if(uniqueInstance == 0)
        uniqueInstance = new MainWindow();
    return uniqueInstance;
}

MainWindow::MainWindow():isMain(true),indexMain(true),indexList(0),indexTip(0){
    main.load(":/images/main.png");
    button.load(":/images/button.png");
    list.load(":/images/list.png");
    for(int i=0;i<8;++i){
        chooseLevel[i].load(QString(":/images/chooselevel%1.png").arg(i+1));
    }
    for(int i=0;i<3;++i){
        tip[i].load(QString(":/images/tip%1.png").arg(i+1));
    }

    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
    engine.setInterval(20);

    engine.start();

    setFixedHeight(960);
    setFixedWidth(1200);
    setWindowTitle("Jump Off The Bridge");

    buffer = QPixmap(size());
    buffer.fill(Qt::transparent);

    level[7]=Level8::instance(this,this);
    level[6]=Level7::instance(this,level[7]);
    level[5]=Level6::instance(this,level[6]);
    level[4]=Level5::instance(this,level[5]);
    level[3]=Level4::instance(this,level[4]);
    level[2]=Level3::instance(this,level[3]);
    level[1]=Level2::instance(this,level[2]);
    level[0]=Level1::instance(this,level[1]);

    begin.setMedia(QUrl("qrc:/music/begin.mp3"));
    begin.play();

    cursor.setMedia(QUrl("qrc:/music/cursor.mp4"));
    enter.setMedia(QUrl("qrc:/music/enter.ogg"));

    playlist.addMedia(QUrl("qrc:/music/backgroundmusic.mp3"));
    playlist.setPlaybackMode(QMediaPlaylist::Loop);
    bgm.setPlaylist(&playlist);
    bgm.setVolume(50);
}

MainWindow::~MainWindow(){

}

void MainWindow::showEvent(QShowEvent *event)
{
    reset();
    QWidget::showEvent(event); //调用基类的showEvent函数
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if(isMain){
        switch(e->key()){
        case Qt::Key_Up:
            indexMain=true;
            cursor.setPosition(0);
            cursor.play();
            break;
        case Qt::Key_Down:
            indexMain=false;
            cursor.setPosition(0);
            cursor.play();
            break;
        case Qt::Key_Return:
            enter.setPosition(0);
            enter.play();
            if(indexMain)
                isMain=false;
            else
                this->close();
        default:
            break;
        }
    }
    else{
        switch(e->key()){
        case Qt::Key_Right:
            cursor.setPosition(0);
            cursor.play();
            if(indexList<7)
                indexList++;
            break;
        case Qt::Key_Left:
            cursor.setPosition(0);
            cursor.play();
            if(indexList>0)
                indexList--;
            break;
        case Qt::Key_Return:
            enter.setPosition(0);
            enter.play();
            this->hide();
            level[indexList]->show();
        case Qt::Key_Escape:
            isMain=true;
        default:
            break;
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(rect(),buffer);
}

void MainWindow::drawToBuffer(){
    buffer.fill(Qt::transparent);
    QPainter painter(&buffer);
    if(isMain){
        painter.drawPixmap(0,0,main);
        painter.drawPixmap(124,473+93*(!indexMain),button);
    }
    else{
        painter.drawPixmap(0,0,list);
        painter.drawPixmap(80+120*indexList,128,chooseLevel[indexList]);
    }
    painter.drawPixmap(30,909,tip[indexTip/4]);
    indexTip++;
    indexTip%=12;

    update();
}

void MainWindow::reset(){
    isMain=true;
    indexList=0;
}

void MainWindow::advance(){
    if(begin.state() == QMediaPlayer::StoppedState)
        bgm.play();
    drawToBuffer();
}

