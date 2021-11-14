#ifndef TSUGU_H
#define TSUGU_H

#include "basegirls.h"

class Tsugu : public BaseGirls
{
public:
    Tsugu(int _X, int _Y, StarBoard*);
    bool isEnhanced;
};

#endif // TSUGU_H
