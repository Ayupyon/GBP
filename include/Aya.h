#ifndef AYA_H
#define AYA_H

#include "basegirls.h"

class Aya : public BaseGirls
{
public:
    Aya(int _X, int _Y, StarBoard* Board);
    StarBoard* _board;
};

#endif // AYA_H
