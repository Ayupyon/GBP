#include "starstone.h"
#include "battlescene.h"
#include <QPropertyAnimation>
#include <QDebug>

StarStone::StarStone(StarBoard* Board)
{
    TargetBoard = Board;
    QPixmap pix(":/StarStone2.png");
    setPixmap(pix);
    setFixedSize(60,60);
    setScaledContents(true);
}

void StarStone::autoProduce()
{
    QPropertyAnimation *Animate = new QPropertyAnimation(this,"geometry");
    Animate->setDuration(5000);
    Animate->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    Animate->setEndValue(QRect(this->x(),this->y()+500,this->width(),this->height()));
    Animate->setEasingCurve(QEasingCurve::Linear);
    Animate->start();
}

void StarStone::KasumiProduce()
{
    QPropertyAnimation *Animate = new QPropertyAnimation(this,"geometry");
    Animate->setDuration(500);
    Animate->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    Animate->setEndValue(QRect(this->x()+20,this->y()+20,this->width(),this->height()));
    Animate->setEasingCurve(QEasingCurve::InExpo);
    Animate->start();
}

void StarStone::collectStar()
{
    TargetBoard->StarNum += 25;
    TargetBoard->numLabel->setNum(TargetBoard->StarNum);
}

void StarStone::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    QPropertyAnimation *Animate = new QPropertyAnimation(this,"geometry");
    Animate->setDuration(500);
    Animate->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    Animate->setEndValue(QRect(0,0,this->width(),this->height()));
    Animate->setEasingCurve(QEasingCurve::Linear);
    Animate->start();
    QTimer::singleShot(500,this,[=](){
        this->close();
        collectStar();
        delete this;
    });
}
