#include "mybtn.h"
#include <QPropertyAnimation>


MyBtn::MyBtn(QString InitPic)
{
    QPixmap pix;
    pix.load(InitPic);
    this->setFixedSize(pix.width()/5,pix.height()/5);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width()/5,pix.height()/5));
}

void MyBtn::JumpDown()
{
    QPropertyAnimation *Animate=new QPropertyAnimation(this,"geometry");
    Animate->setDuration(200);
    Animate->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    Animate->setEndValue(QRect(this->x(),this->y()+15,this->width(),this->height()));
    Animate->setEasingCurve(QEasingCurve::OutBounce);
    Animate->start();
}

void MyBtn::JumpUp()
{
    QPropertyAnimation *Animate=new QPropertyAnimation(this,"geometry");
    Animate->setDuration(200);
    Animate->setStartValue(QRect(this->x(),this->y()+15,this->width(),this->height()));
    Animate->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    Animate->setEasingCurve(QEasingCurve::OutBounce);
    Animate->start();
}


