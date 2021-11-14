#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "basemarinai.h"

class Obstacle : public BaseMarinai
{
public:
    Obstacle(int _X, int _Y, BattleScene* Battle, BaseMarinai* producer);

    BaseMarinai* _producer;
};

#endif // OBSTACLE_H
