#ifndef CONTROL_H
#define CONTROL_H
#include <QSet>
#include <QVector>
#include "basemarinai.h"
#include "basegirls.h"

class Control
{
public:
    Control();
    QSet<BaseMarinai*> MarinaiList;
    QSet<BaseGirls*> GirlsList;
};

#endif // CONTROL_H
