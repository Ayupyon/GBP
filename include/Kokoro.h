#ifndef KOKORO_H
#define KOKORO_H

#include "basegirls.h"
#include "basemarinai.h"

class Kokoro : public BaseGirls
{
public:
    Kokoro(int _X, int _Y, StarBoard*);
    BaseMarinai* get_closest_marinai();
    int _attack_counter;
};

#endif // KOKORO_H
