#ifndef FLYMARINAI_H
#define FLYMARINAI_H

#include "basemarinai.h"

class FlyMarinai : public BaseMarinai
{
public:
    FlyMarinai(int _X, int _Y, BattleScene* Battle);
    virtual void fall();
    bool _is_fall;
};

#endif // FLYMARINAI_H
