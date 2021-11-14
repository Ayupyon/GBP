#ifndef BASEMARINAI_H
#define BASEMARINAI_H

#include "baseobject.h"
#include "basegirls.h"
#include "battlescene.h"
#include <QTimer>

#define COLLIDE_DIS 70

#define BIAS CARD_WIDTH / 2

#define LAND 0
#define SKY 1

class BaseMarinai : public BaseObject
{
public:
    BaseMarinai(int _X, int _Y, BattleScene* Battle);
    void Damage(int damage);
    void repeled();
    void speed_down(int down);
    BaseGirls* EncounterWithGirls();

    int LocX;
    int LocY;
    int _type;
    int Speed;
    int _attack;
    QTimer* Timer = NULL;
    BattleScene* _cur_battlescene;
    int _speed_down_counter;
};

#endif // BASEMARINAI_H
