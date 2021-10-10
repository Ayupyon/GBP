#ifndef STARBOARD_H
#define STARBOARD_H
#include "baseobject.h"
#include <QLabel>
#include <QTimer>


class StarBoard : public BaseObject
{
public:
    StarBoard();
    void StarReduce(int num);
    int StarNum = 50;
    QLabel* numLabel;
};

#endif // STARBOARD_H
