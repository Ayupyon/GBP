#ifndef BASEMARINAI_H
#define BASEMARINAI_H
#include "baseobject.h"
#include "battlescene.h"
#include <QTimer>

class BaseMarinai : public BaseObject
{
public:
    BaseMarinai(int _X,int _Y,BattleScene* Battle);
    void Damage();
    bool EncounterWithGirls();
    //bool CollideWithStarBullets(BaseObject* Bullets);
    int LocX;
    int LocY;
    int Speed = 10;
    QTimer* Timer = NULL;
};

#endif // BASEMARINAI_H
