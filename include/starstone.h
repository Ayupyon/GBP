#ifndef STARSTONE_H
#define STARSTONE_H
#include "baseobject.h"
#include "starboard.h"

class StarStone : public BaseObject
{
public:
    StarStone(StarBoard* Board);
    StarBoard* TargetBoard;
    virtual void mousePressEvent(QMouseEvent* event) override;
    void autoProduce();
    void KasumiProduce();
signals:
    void collectStar();
};

#endif // STARSTONE_H
