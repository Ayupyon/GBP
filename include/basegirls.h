#ifndef BASEGIRLS_H
#define BASEGIRLS_H
#include "baseobject.h"
#include <QTimer>
#include "Land.h"
#include "card.h"

#define CARD_WIDTH LAND_WIDTH

class BaseGirls : public BaseObject
{
public:
    BaseGirls(int _X,int _Y);
    void Damage(int damage);
    bool CollideWithMarinais();
    int LocX;
    int LocY;
    int _kind;
    QTimer* Timer;
};

#endif // BASEGIRLS_H
