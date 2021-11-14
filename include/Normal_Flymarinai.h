#ifndef NORMAL_FLYMARINAI_H
#define NORMAL_FLYMARINAI_H

#include "FlyMarinai.h"

class Normal_FlyMarinai : public FlyMarinai
{
public:
    Normal_FlyMarinai(int _X,int _Y,BattleScene* Battle);
    void fall() override;
};

#endif // NORMAL_FLYMARINAI_H
