#include "Moca.h"
#include "Ran.h"
#include "Himari.h"
#include "Tomoe.h"
#include "Tsugu.h"
#include "Control.h"
#include <QDebug>

#define STRENGTH 200

extern Control con;

QString logo_path = ":/ag_logo.png";

Moca::Moca(int _X,int _Y,StarBoard*):BaseGirls(_X, _Y)
{
    _kind = MOCA;
    Strength = STRENGTH;
    QPixmap pix(":/Moca_Battling.png");
    setPixmap(pix);
    setFixedSize(CARD_WIDTH, CARD_WIDTH);
    setScaledContents(true);
    move(START_X + LocX * 90, START_Y + LocY * 90);
    Timer = new QTimer;
    _action_counter = 0;
    connect(Timer, &QTimer::timeout, this, [&](){
        _action_counter++;
        if(Strength > 0)
        {
            if(Strength < STRENGTH / 5)
                setPixmap(QPixmap(":/Moca_Exhausted.png"));
            if(_action_counter > 8)
            {
                Enhance();
                _action_counter = 0;
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

void Moca::Enhance()
{
    for(auto& cur_girl:con.GirlsList)
    {
        if((cur_girl->LocX == LocX && (cur_girl->LocY == LocY + 1 || cur_girl->LocY == LocY - 1)) || (cur_girl->LocY == LocY && (cur_girl->LocX == LocX + 1 || cur_girl->LocX == LocX - 1)))
        {

            switch (cur_girl->_kind)
            {
            case RAN:
            {
                set_logo(cur_girl);
                Ran* ran = dynamic_cast<Ran*>(cur_girl);
                ran->_prepare_counter += 10;
                break;
            }
            case HIMARI:
            {
                set_logo(cur_girl);
                Himari* himari = dynamic_cast<Himari*>(cur_girl);
                himari->_action_counter += 5;
                if(himari->Strength < STRENGTH)
                    himari->Strength += 25;
                break;
            }
            case TOMOE:
            {
                set_logo(cur_girl);
                Tomoe* tomoe = dynamic_cast<Tomoe*>(cur_girl);
                tomoe->_attack = 3600;
                break;
            }
            case TSUGU:
            {
                set_logo(cur_girl);
                Tsugu* tsugu = dynamic_cast<Tsugu*>(cur_girl);
                tsugu->isEnhanced = true;
            }
            default:
                break;
            }
        }
    }
}

void Moca::set_logo(BaseGirls* cur_girl)
{
    BattleScene* cur_scene = dynamic_cast<BattleScene*>(this->parent());
    QLabel* logo = new QLabel(cur_scene);
    logo->setPixmap(QPixmap(logo_path));
    logo->setFixedSize(90, 60);
    logo->setScaledContents(true);
    logo->move(START_X + cur_girl->LocX * 90, START_Y + cur_girl->LocY * 90);
    QTimer::singleShot(1500, logo, [=](){
       logo->close();
       delete logo;
    });
    logo->show();
}
