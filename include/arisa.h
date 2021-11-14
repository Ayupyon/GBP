#ifndef ARISA_H
#define ARISA_H
#include "basegirls.h"
#include "starboard.h"

class Arisa : public BaseGirls
{
public:
    Arisa(int _X, int _Y, StarBoard*);
    bool FindMarinais();
    int _attack_counter;
};

#endif // ARISA_H
