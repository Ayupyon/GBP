#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include <QLabel>
#include <QGraphicsView>

#define DefaultType 0
#define girls 1
#define marinais 2
#define bullets 3

class BaseObject : public QLabel
{
public:
    BaseObject();
    int Strength = 1;
    int Type;
};

#endif // BASEOBJECT_H
