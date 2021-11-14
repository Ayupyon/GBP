#ifndef PIN_MARINAI_H
#define PIN_MARINAI_H

#include "basemarinai.h"

class Pin_Marinai : public BaseMarinai
{
public:
    Pin_Marinai(int _X, int _Y, BattleScene* Battle);
    int _action_counter;
};

#endif // PIN_MARINAI_H
