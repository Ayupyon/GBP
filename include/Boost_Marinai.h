#ifndef BOOST_MARINAI_H
#define BOOST_MARINAI_H

#include "basemarinai.h"

class Boost_Marinai:public BaseMarinai
{
public:
    Boost_Marinai(int _X, int _Y, BattleScene* Battle);
    int _action_counter;
};

#endif // BOOST_MARINAI_H
