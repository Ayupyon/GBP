#include "starbullet.h"
#include "basemarinai.h"
#include "Control.h"
#include "arisa.h"
#include "Tsugu.h"

extern Control con;

StarBullet::StarBullet(int _X,int _Y)
{
    _speed = 10;
    _attack = 20;
    LocX = _X;
    LocY = _Y;
    Strength = 1;
    QPixmap pix(":/starBullet1.png");
    setPixmap(pix);
    setFixedSize(30,30);
    setScaledContents(true);
    move(START_X + LocX * 90 + CARD_WIDTH / 2, START_Y + LocY * 90 + CARD_WIDTH / 2);
    Timer = new QTimer;
    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0 && x() < 1002)
        {
            if(CollideWithMarinai()) Strength = 0;
            else this->move(this->x() + _speed, this->y());
            LocX = (x() - START_X) / (double)CARD_WIDTH;
            if(EncounterWithTsugu())
                _speed = -_speed;
        }
        else
        {
            this->close();
            delete this;
        }
    });
    Timer->start(40);
}

bool StarBullet::CollideWithMarinai()
{
    for(auto Marinai:con.MarinaiList)
    {
        if(Marinai->_type == LAND && LocY == Marinai->LocY && Marinai->x()-x() >= -50 && Marinai->x() - x() < 10)
        {
            Marinai->Damage(_attack);
            return true;
        }
    }
    return false;
}

bool StarBullet::EncounterWithTsugu()
{
    for(auto& cur_girl:con.GirlsList)
    {
        if(cur_girl->_kind == TSUGU && cur_girl->LocX == LocX && cur_girl->LocY == LocY)
        {
            Tsugu* tsugu = dynamic_cast<Tsugu*>(cur_girl);
            if(tsugu->isEnhanced && _attack == 20)
                _attack *= 2;
            return true;
        }
    }
    return false;
}


