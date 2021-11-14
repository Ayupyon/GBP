#ifndef MICHELLE_STATUE_H
#define MICHELLE_STATUE_H

#include "basemarinai.h"

#define NORMAL_MARINAI 1
#define WHEEL_MARINAI 2
#define HELMET_MARINAI 3

#define MICHELLE_PRODUCE_MARINAI(type)     \
       BattleScene* cur_scene = dynamic_cast<BattleScene*>(this->parent());    \
       BaseMarinai* marinai = new type(8, LocY, cur_scene); \
       marinai->show();  \

class Michelle_Statue : public BaseMarinai
{
public:
    Michelle_Statue(int _X,int _Y,BattleScene* Battle);
    void produce_marinai();
    int _action_counter;
};

#endif // MICHELLE_STATUE_H
