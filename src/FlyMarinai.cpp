#include "FlyMarinai.h"

FlyMarinai::FlyMarinai(int _X, int _Y, BattleScene* Battle): BaseMarinai(_X, _Y, Battle)
{
    _type = SKY;
}

void FlyMarinai::fall(){}
