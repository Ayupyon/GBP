#ifndef OTAE_H
#define OTAE_H
#include "basegirls.h"
#include "starboard.h"
#include "basemarinai.h"

class Otae : public BaseGirls
{
public:
    Otae(int _X, int _Y, StarBoard*);
    BaseMarinai* get_collide_marinai();
    QTimer* ready_timer;
    int ready_counter;
};

#endif // OTAE_H
