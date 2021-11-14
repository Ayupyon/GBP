#include "basegirls.h"
#include "basemarinai.h"
#include "Control.h"

extern Control con;
#define INF 99999

BaseGirls::BaseGirls(int _X,int _Y)
{
    LocX = _X;
    LocY = _Y;
}

void BaseGirls::Damage(int damage)
{
    Strength -= damage;
}

bool BaseGirls::CollideWithMarinais()
{
    for(auto Marinai:con.MarinaiList)
    {
        if(LocX == Marinai->LocX && LocY == Marinai->LocY && Marinai->_type == LAND)
            return true;
    }
    return false;
}
