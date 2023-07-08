#include "dragon.h"
#include "parameter.cpp"

#include <QDebug>
#include<QRandomGenerator>

Dragon::Dragon(qreal x,
               qreal y,
               qreal width,
               qreal height):
    StaticObject(x, y, width, height){
    dragonState = Rest;
    attackTimer = 0;
    attackedTimer = 0;
    attackTime = QRandomGenerator::global()->bounded(2,6);
    attackTime *= 5;
    strength = 3;
    deathTimer = 0;
    shootBomb = 0;

    restG.load(DRAGON2);
    attackG.load(DRAGON1);
    attackedG.load(DRAGON3);
    redHeartG.load(REDHEART);
    whiteHeartG.load(WHITEHEART);
    blackHeartG.load(BLACKHEART);
}

Dragon::~Dragon(){

}

void Dragon::updateState(const QVector<Arrow*>& arrowList){
    if(dragonState != Dead){
        for(int i = 0; i != arrowList.size(); i++){
            if(arrowList[i]->rect().x() + arrowList[i]->rect().width() >= rect().x()){
                strength--;
                if(strength > 0){
                    dragonState = Attacked;
                }
                else{
                    dragonState = Dead;
                }
                attackedTimer = 0;
                break;
            }
        }
    }

    if(dragonState == Attacked || attackedTimer > 0){
        attackedTimer++;
        if(attackedTimer > 8){
            dragonState = Rest;
            attackedTimer = 0;
        }
    }
    else if(dragonState == Dead){
        deathTimer++;
        if(deathTimer > 16){
            deathTimer = 16;
        }
    }
    else{
        attackTimer++;
        if(attackTimer == attackTime){
            dragonState = Attack;
            shootBomb = 1;
        }
        else{
            shootBomb = 0;
            if(attackTimer >= attackTime + 5){
                attackTimer = 0;
                attackTime = QRandomGenerator::global()->bounded(2,6);
                attackTime *= 10;
            }
            else if(attackTimer < attackTime){
                dragonState = Rest;
            }
        }
    }
}

void Dragon::draw(QPainter *painter){
    switch(dragonState){
    case Rest:
        painter->drawPixmap(dragonX, floorY - restG.rect().height(), restG.rect().width(), restG.rect().height(), restG);
        break;
    case Attack:
        painter->drawPixmap(dragonX - 20, floorY - attackG.rect().height(), attackG.rect().width(), attackG.rect().height(), attackG);
        break;
    case Attacked:
        painter->drawPixmap(dragonX, floorY - attackedG.rect().height(), attackedG.rect().width(), attackedG.rect().height(), attackedG);
        break;
    case Dead:
        if(deathTimer / 2 % 2 != 0){
            painter->drawPixmap(dragonX, floorY - attackedG.rect().height(), attackedG.rect().width(), attackedG.rect().height(), attackedG);
            for(int i = 0; i < 3; i++){
                painter->drawPixmap(dragonX + i * 35, dragonY - 35, blackHeartG.rect().width(), blackHeartG.rect().height(), blackHeartG);
            }
        }
        break;
    default:
        break;
    }

    if(dragonState != Dead){
        for(int i = 0; i < strength; i++){
            painter->drawPixmap(dragonX + i * 35, dragonY - 35, redHeartG.rect().width(), redHeartG.rect().height(), redHeartG);
        }
        if(strength < 3){
            if(attackedTimer / 2 % 2 == 0){
                painter->drawPixmap(dragonX + strength * 35, dragonY - 35, blackHeartG.rect().width(), blackHeartG.rect().height(), blackHeartG);
            }
            else{
                painter->drawPixmap(dragonX + strength * 35, dragonY - 35, whiteHeartG.rect().width(), whiteHeartG.rect().height(), whiteHeartG);
            }
        }
        for(int i = strength + 1; i < 3; i++){
            painter->drawPixmap(dragonX + i * 35, dragonY - 35, blackHeartG.rect().width(), blackHeartG.rect().height(), blackHeartG);
        }
    }
}

bool Dragon::isAlive(){
    return dragonState != Dead;
}

bool Dragon::isShootBomb(){
    return shootBomb;
}



