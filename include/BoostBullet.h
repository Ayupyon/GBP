#ifndef BOOSTBULLET_H
#define BOOSTBULLET_H

#include "baseobject.h"
#include "basemarinai.h"

class BoostBullet : public BaseObject
{
public:
    BoostBullet(int _X, int _Y);
    bool CollideWithMarinai();
    bool EncounterWithTsugu();
    int LocX;
    int LocY;
    int _speed;
    int _attack;
    QTimer* _attack_timer;
};

#endif // BOOSTBULLET_H
