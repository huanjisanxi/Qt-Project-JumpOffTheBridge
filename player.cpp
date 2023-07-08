#include "player.h"
#include "parameter.cpp"

#include <QDebug>
#include <QRandomGenerator>

Player::Player(qreal x,
               qreal y,
               qreal width,
               qreal height):MoveObject(x,y,width,height)
{
    liftObj=NULL;
    mxSpeed=0;
    mySpeed=0;
    deathTimer = 1;
    indexDirection=true;
    right[0].load(PLAYERRIGHT);
    right[1].load(PLAYERRIGHTMOVE);
    left[0].load(PLAYERLEFT);
    left[1].load(PLAYERLEFTMOVE);
    liftRight[0].load(RIGHTLIFT);
    liftRight[1].load(RIGHTJUMPLIFT);
    liftLeft[0].load(LEFTLIFT);
    liftLeft[1].load(LEFTJUMPLIFT);
    death.load(DEAD);
}

Player::~Player(){
    //-------TODO-------
}

void Player::setIndex(){
    indexRight=0;
    indexLeft=0;
    indexLiftRight=0;
    indexLiftLeft=0;
}

void Player::updateState(){
    if(playerState==Death)
        return;
    if(liftObj){
        if(mxSpeed==0||mySpeed!=0){
            playerState=Lift;
            setIndex();
        }
        else if(mxSpeed<0)
            playerState=LiftMoveLeft;
        else if(mxSpeed>0)
            playerState=LiftMoveRight;
    }
    else{
        if(!onFloor){
            playerState=Jump;
            setIndex();
        }
        else if(mxSpeed==0){
            playerState=Static;
            setIndex();
        }
        else if(mxSpeed<0)
            playerState=MoveLeft;
        else if(mxSpeed>0)
            playerState=MoveRight;
    }
}


void Player::updateRect(){
    updateState();
    MoveObject::updateRect();
    for(int i = 0; i != bloodList.size(); i++){
        bloodList[i]->updateRect();
    }
    if(liftObj){
        liftObj->setPos(rect().x()-(liftObj->rect().width()-rect().width())/2,rect().y()-liftObj->rect().height());
    }
}

void Player::draw(QPainter *painter){
    switch (playerState) {
    case Death:
        painter->drawPixmap(mRect.x()-14,mRect.y(),death.width(),death.height(), death);
        for(int i = 0; i != bloodList.size(); i++){
            bloodList[i]->draw(painter);
        }
        break;
    case Static:
        if(indexDirection)
        painter->drawPixmap(mRect.x(),mRect.y(),right[0].width(),right[0].height(), right[0]);
        else
        painter->drawPixmap(mRect.x(),mRect.y(),right[0].width(),right[0].height(), left[0]);
        break;
    case Jump:
        if(mxSpeed==0)
            if(indexDirection)
                painter->drawPixmap(mRect.x(),mRect.y(),right[0].width(),right[0].height(), right[0]);
            else
                painter->drawPixmap(mRect.x(),mRect.y(),right[0].width(),right[0].height(), left[0]);
        else if(mxSpeed<0)
            painter->drawPixmap(mRect.x(),mRect.y(),left[1].width(),left[1].height(), left[1]);
        else
            painter->drawPixmap(mRect.x(),mRect.y(),right[1].width(),right[1].height(), right[1]);
        break;
    case MoveRight:
        if(indexRight<2)
            painter->drawPixmap(mRect.x(),mRect.y(),right[0].width(),right[0].height(), right[0]);
        else
            painter->drawPixmap(mRect.x()-4,mRect.y(),right[1].width(),right[1].height(), right[1]);
        indexRight++;
        indexRight%=4;
        indexDirection=true;
        break;
    case MoveLeft:
        if(indexLeft<2)
            painter->drawPixmap(mRect.x(),mRect.y(),left[0].width(),left[0].height(), left[0]);
        else
            painter->drawPixmap(mRect.x()-3,mRect.y(),left[1].width(),left[1].height(), left[1]);
        indexLeft++;
        indexLeft%=4;
        indexDirection=false;
        break;
    case Lift:
        if(mxSpeed==0)
            if(indexDirection)
                painter->drawPixmap(mRect.x(),mRect.y(),liftRight[0].width(),liftRight[0].height(), liftRight[0]);
            else
                painter->drawPixmap(mRect.x(),mRect.y(),liftRight[0].width(),liftRight[0].height(), liftLeft[0]);
        else if(mxSpeed<0)
            painter->drawPixmap(mRect.x(),mRect.y(),liftLeft[1].width(),liftLeft[1].height(), liftLeft[1]);
        else
            painter->drawPixmap(mRect.x(),mRect.y(),liftRight[1].width(),liftRight[1].height(), liftRight[1]);
        break;
    case LiftMoveLeft:
        if(indexRight<2)
            painter->drawPixmap(mRect.x(),mRect.y(),liftLeft[0].width(),liftLeft[0].height(), liftLeft[0]);
        else
            painter->drawPixmap(mRect.x()-4,mRect.y(),liftLeft[1].width(),liftLeft[1].height(), liftLeft[1]);
        indexRight++;
        indexRight%=4;
        indexDirection=false;
        break;
    case LiftMoveRight:
        if(indexLeft<2)
            painter->drawPixmap(mRect.x(),mRect.y(),liftRight[0].width(),liftRight[0].height(), liftRight[0]);
        else
            painter->drawPixmap(mRect.x()-3,mRect.y(),liftRight[1].width(),liftRight[1].height(), liftRight[1]);
        indexLeft++;
        indexLeft%=4;
        indexDirection=true;
        break;
    default:
        break;
    }
}

void Player::jump(){
    if(playerState==Death)
        return;
    if(!onFloor){
        return;
    }
    mySpeed=JUMP_SPEED;
    playerState=Jump;
}

void Player::pickUp(MoveObject* obj){
    if(liftObj)
        return;
    if(rect().x()<obj->rect().x()+obj->rect().width()&&rect().x()+rect().width()>=obj->rect().x()&&obj->onfloor()){
        liftObj=obj;
        liftObj->setBeLift(true);
        liftObj->setPos(rect().x()-(obj->rect().width()-rect().width())/2,rect().y()-obj->rect().height());
    }
}

void Player::throwing(){
    if(liftObj){
        liftObj->setySpeed(-OBJYSPEED);
        if(indexDirection){
            liftObj->setxSpeed(OBJXSPEED);
        }
        else{
            liftObj->setxSpeed(-OBJXSPEED);
        }
        liftObj->setBeLift(false);
        liftObj=NULL;
    }
}

void Player::moveRight(){
    if(playerState==Death)
        return;
    setxSpeed(XSPEED);
}

void Player::moveLeft(){
    if(playerState==Death)
        return;
    setxSpeed(-XSPEED);
}

void Player::moveNo(){
    if(playerState==Death)
        return;
    setxSpeed(0);
}

void Player::setDeath(){
    if(playerState==Death)
        return;
    playerState=Death;
    mxSpeed=0,mySpeed=0;
    throwing();
    if(deathTimer > 0){
        int size = 36;
        for(int i = 0; i < size; i++){
            bloodList.append(new Blood(rect().x(), rect().y(), 1.5, 1.5, i % 18));
        }
        deathTimer = std::max(deathTimer - 1, 0);
    }
}

