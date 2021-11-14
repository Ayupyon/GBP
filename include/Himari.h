#ifndef HIMARI_H
#define HIMARI_H

#include "basegirls.h"
#include "basemarinai.h"

class Himari : public BaseGirls
{
public:
    Himari(int _X, int _Y, StarBoard*);
    BaseMarinai* GetEncounteredMarinai();
    int _action_counter;
};

#endif // HIMARI_H
