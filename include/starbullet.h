#ifndef STARBULLET_H
#define STARBULLET_H
#include "baseobject.h"
#include <QTimer>

class StarBullet : public BaseObject
{
public:
    StarBullet(int _X,int _Y);
    bool CollideWithMarinai();
    int LocX;
    int LocY;
    QTimer* Timer;
};

#endif // STARBULLET_H
