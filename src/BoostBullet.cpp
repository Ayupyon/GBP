#include "BoostBullet.h"
#include "Tsugu.h"
#include "Control.h"

extern Control con;

BoostBullet::BoostBullet(int _X, int _Y):LocX(_X), LocY(_Y)
{
    _attack = 30;
    _speed = 10;
    QPixmap pix(":/boostbullet.png");
    setPixmap(pix);
    setFixedSize(30,30);
    setScaledContents(true);
    move(START_X + LocX * 90 + CARD_WIDTH / 2, START_Y + LocY * 90 + CARD_WIDTH / 2);

    _attack_timer = new QTimer;
    connect(_attack_timer, &QTimer::timeout, this, [=](){
        if(EncounterWithTsugu())
            _speed = -_speed;
        if(Strength > 0 && x() < 1002)
        {
            if(CollideWithMarinai())
                Strength = 0;
            else
                this->move(this->x() + _speed,this->y());
            LocX = (x() - START_X) / (double)CARD_WIDTH;
        }
        else
        {
            this->close();
            delete this;
        }
    });
    _attack_timer->start(40);
}

bool BoostBullet::CollideWithMarinai()
{
    for(auto cur_marinai:con.MarinaiList)
    {
        if(cur_marinai->_type == LAND && cur_marinai->x()-x() >= -50 && cur_marinai->x() - x() < 10 && LocY == cur_marinai->LocY)
        {
            cur_marinai->Damage(_attack);
            return true;
        }
    }
    return false;
}

bool BoostBullet::EncounterWithTsugu()
{
    for(auto& cur_girl:con.GirlsList)
    {
        if(cur_girl->_kind == TSUGU && cur_girl->LocX == LocX && cur_girl->LocY == LocY)
        {
            Tsugu* tsugu = dynamic_cast<Tsugu*>(cur_girl);
            if(tsugu->isEnhanced && _attack == 30)
                _attack *= 2;
            return true;
        }
    }
    return false;
}
