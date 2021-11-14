#include "basemarinai.h"
#include <QDebug>
#include "starbullet.h"
#include "battlescene.h"
#include "Control.h"

extern Control con;

BaseMarinai::BaseMarinai(int _X, int _Y, BattleScene* Battle):
LocX(_X), LocY(_Y), _cur_battlescene(Battle)
{
    _speed_down_counter = 0;
}

BaseGirls* BaseMarinai::EncounterWithGirls()
{
    BaseGirls* cur_girl = nullptr;
    for(auto& Girl : con.GirlsList)
    {
        if(LocX == Girl->LocX && LocY == Girl->LocY && Girl->_kind != HIMARI)
        {
            cur_girl = Girl;
            break;
        }
    }
    return cur_girl;
}

void BaseMarinai::repeled()
{
    move(x() + 90, y());
}

void BaseMarinai::Damage(int damage)
{
    Strength -= damage;
}

void BaseMarinai::speed_down(int down)
{
    Speed -= down;
    _speed_down_counter = 50;
}


