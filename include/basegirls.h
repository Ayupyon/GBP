#ifndef BASEGIRLS_H
#define BASEGIRLS_H
#include "baseobject.h"
#include <QTimer>

class BaseGirls : public BaseObject
{
public:
    BaseGirls(int _X,int _Y);
    void Damage();
    bool CollideWithMarinais();
    int LocX;
    int LocY;
    QTimer* Timer;
};

#endif // BASEGIRLS_H
