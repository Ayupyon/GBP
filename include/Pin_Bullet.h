#ifndef PIN_BULLET_H
#define PIN_BULLET_H

#include "baseobject.h"
#include "basegirls.h"

class Pin_Bullet : public BaseObject
{
public:
    Pin_Bullet(int _X, int _Y);
    BaseGirls* get_encountered_girl();
    int LocX;
    int LocY;
    int _speed;
    int _attack;
    QTimer* _timer;
};

#endif // PIN_BULLET_H
