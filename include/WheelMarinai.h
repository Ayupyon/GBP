#ifndef WHEELMARINAI_H
#define WHEELMARINAI_H

#include "basemarinai.h"

class WheelMarinai : public BaseMarinai
{
public:
    WheelMarinai(int _X, int _Y, BattleScene* scene);
    bool _first_collide = true;
};

#endif // WHEELMARINAI_H
