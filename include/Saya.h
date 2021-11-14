#ifndef SAYA_H
#define SAYA_H
#include "basegirls.h"
#include "starboard.h"
#include "basemarinai.h"

class Saya : public BaseGirls
{
public:
    Saya(int _X, int _Y, StarBoard*);
    BaseMarinai* get_closest_marinai();
    void set_chocoriro(BaseMarinai* res_marinai);
    StarBoard* _board;
    QTimer* ready_timer;
    int ready_counter;
};

#endif // SAYA_H
