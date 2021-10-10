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

void BaseGirls::Damage()
{
    Strength -= 10;
}

bool BaseGirls::CollideWithMarinais()
{
    int minDis = INF;
    for(auto Marinai:con.MarinaiList)
    {
        if(LocX == Marinai->LocX)
        {
            int Dis = Marinai->x()-x();
            if(Dis > 0 && Dis < minDis)
            {
                minDis = Dis;
            }
        }
    }
    return minDis < 70;
}
