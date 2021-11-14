#ifndef OBSTACLE_FLYMARINAI_H
#define OBSTACLE_FLYMARINAI_H

#include "FlyMarinai.h"

class Obstacle_FlyMarinai: public FlyMarinai
{
public:
    Obstacle_FlyMarinai(int _X, int _Y, BattleScene* Battle);
    void fall() override;
};

#endif // OBSTACLE_FLYMARINAI_H
