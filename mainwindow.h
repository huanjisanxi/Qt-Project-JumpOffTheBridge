#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "level6.h"
#include "level7.h"
#include "level8.h"

class MainWindow:public QWidget{
    Q_OBJECT
public:
    static MainWindow* instance();

private:
    static MainWindow* uniqueInstance;
    QPixmap main;
    QPixmap list;
    QPixmap button;
    QPixmap buffer;
    QPixmap tip[3];
    QPixmap chooseLevel[8];
    QMediaPlayer bgm;
    QMediaPlayer begin;
    QMediaPlayer cursor;
    QMediaPlayer enter;
    QMediaPlaylist playlist;
    QWidget* level[8];
    QTimer engine;
    bool isMain;
    bool indexMain;
    int indexList;
    int indexTip;


    MainWindow();
    ~MainWindow();
    void showEvent(QShowEvent *event);
    void keyPressEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *);
    void drawToBuffer();
    void reset();

public slots:
    void advance();
};

#endif // MAINWINDOW_H
