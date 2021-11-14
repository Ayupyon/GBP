#ifndef TOMOE_H
#define TOMOE_H

#include "basegirls.h"
#include "basemarinai.h"

#define LEFT 1
#define RIGHT 2

class Tomoe : public BaseGirls
{
public:
    Tomoe(int _X, int _Y, StarBoard*);
    int FindMarinais();
    void AttackLeft();
    void AttackRight();
    void AttackMarinais(int direction);

    int _attack;
};

#endif // TOMOE_H
