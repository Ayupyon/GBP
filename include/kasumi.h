#ifndef KASUMI_H
#define KASUMI_H
#include "basegirls.h"
#include "starboard.h"

class Kasumi : public BaseGirls
{
public:
    Kasumi(int _X, int _Y, StarBoard* Board);
    QTimer* ProduceTimer;
};

#endif // KASUMI_H
