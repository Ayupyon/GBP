#include "Tomoe.h"
#include "Control.h"
#include <QPropertyAnimation>

extern Control con;

#define STRENGTH 200

Tomoe::Tomoe(int _X, int _Y, StarBoard*):BaseGirls(_X, _Y)
{
    _kind = TOMOE;
    Strength = STRENGTH;
    _attack = 1800;
    QPixmap pix(":/Tomoe_Battling.png");
    setPixmap(pix);
    setFixedSize(CARD_WIDTH, CARD_WIDTH);
    setScaledContents(true);
    move(START_X + LocX * 90, START_Y + LocY * 90);
    Timer = new QTimer;

    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0)
        {
            if(Strength < STRENGTH / 5)
                setPixmap(QPixmap(":/Tomoe_Exhausted.png"));
            int res = FindMarinais();
            if(res)
            {
                AttackMarinais(res);
                QTimer::singleShot(1200, this, [=](){
                    close();
                    auto it = con.GirlsList.find(this);
                    if(it!=con.GirlsList.end()) con.GirlsList.erase(it);
                    delete this;
                });
            }
        }
        else
        {
            Timer->stop();
            auto it = con.GirlsList.find(this);
            if(it!=con.GirlsList.end()) con.GirlsList.erase(it);
            this->close();
            delete this;
        }
    });
    Timer->start(500);
    con.GirlsList.insert(this);
}

int Tomoe::FindMarinais()
{
    for(auto& cur_marinai:con.MarinaiList)
    {
        if(cur_marinai->LocY == LocY && cur_marinai->_type == LAND)
        {
            if(cur_marinai->LocX == LocX - 1)
                return LEFT;
            else if(cur_marinai->LocX == LocX + 1 || cur_marinai->LocX == LocX)
                return RIGHT;
        }
    }
    return 0;
}

void Tomoe::AttackLeft()
{
    setPixmap(QPixmap(":/Tomoe_Attacking_left.png"));
    QPropertyAnimation *animate1 = new QPropertyAnimation(this, "geometry");
    animate1->setDuration(500);
    animate1->setStartValue(QRect(x(), y(), width(), height()));
    animate1->setEndValue(QRect(x() - CARD_WIDTH / 2, y() , width(), height()));
    animate1->setEasingCurve(QEasingCurve::OutCubic);
    animate1->start();
    QPropertyAnimation *animate2 = new QPropertyAnimation(this, "geometry");
    animate2->setDuration(500);
    animate2->setStartValue(QRect(x() - CARD_WIDTH / 2, y() - CARD_WIDTH / 2, width(), height()));
    animate2->setEndValue(QRect(x() - CARD_WIDTH, y(), width(), height()));
    animate2->setEasingCurve(QEasingCurve::OutCubic);
    QTimer::singleShot(500, this, [=](){animate2->start();});
}

void Tomoe::AttackRight()
{
    setPixmap(QPixmap(":/Tomoe_Attacking_right.png"));
    QPropertyAnimation *animate1 = new QPropertyAnimation(this, "geometry");
    animate1->setDuration(500);
    animate1->setStartValue(QRect(x(), y(), width(), height()));
    animate1->setEndValue(QRect(x() + CARD_WIDTH / 2, y() - CARD_WIDTH / 2, width(), height()));
    animate1->setEasingCurve(QEasingCurve::OutCubic);
    animate1->start();
    QPropertyAnimation *animate2 = new QPropertyAnimation(this, "geometry");
    animate2->setDuration(500);
    animate2->setStartValue(QRect(x() + CARD_WIDTH / 2, y() - CARD_WIDTH / 2, width(), height()));
    animate2->setEndValue(QRect(x() + CARD_WIDTH, y(), width(), height()));
    animate2->setEasingCurve(QEasingCurve::OutCubic);
    QTimer::singleShot(500, this, [=](){animate2->start();});
}

void Tomoe::AttackMarinais(int direction)
{
    QVector<BaseMarinai*> attack_list;
    switch (direction)
    {
    case LEFT:
    {
        for(auto& cur_marinai:con.MarinaiList)
        {
            if(cur_marinai->LocY == LocY && cur_marinai->LocX == LocX - 1 && cur_marinai->_type == LAND)
                attack_list.push_back(cur_marinai);
        }
        AttackLeft();
        break;
    }
    case RIGHT:
    {
        for(auto& cur_marinai:con.MarinaiList)
        {
            if(cur_marinai->LocY == LocY && (cur_marinai->LocX == LocX || cur_marinai->LocX == LocX + 1) && cur_marinai->_type == LAND)
                attack_list.push_back(cur_marinai);
        }
        AttackRight();
        break;
    }
    default:
        break;
    }
    for(auto& cur_marinai:attack_list)
        cur_marinai->Damage(1800);
}

