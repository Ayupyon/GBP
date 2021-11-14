#ifndef SMILESTARBULLET_H
#define SMILESTARBULLET_H

#include "baseobject.h"


class SmileStarBullet : public BaseObject
{
public:
    SmileStarBullet(int startX, int startY, int endX, int endY);
    void shoot();
    int _startX, _startY, _endX, _endY;
    int LocX;
    int LocY;
    int _attack;
};

#endif // SMILESTARBULLET_H
