#ifndef MOCA_H
#define MOCA_H

#include "basegirls.h"

class Moca : public BaseGirls
{
public:
    Moca(int _X,int _Y,StarBoard*);
    void Enhance();
    void set_logo(BaseGirls* cur_girl);
    int _action_counter;
};

#endif // MOCA_H
