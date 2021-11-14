#include "Pin_Bullet.h"
#include "basemarinai.h"
#include "Control.h"

extern Control con;

Pin_Bullet::Pin_Bullet(int _X, int _Y) : LocX(_X), LocY(_Y)
{
    _speed = 10;
    _attack = 10;

    Strength = 1;
    QPixmap pix(":/pin.png");
    setPixmap(pix);
    setFixedSize(60,30);
    setScaledContents(true);
    move(START_X + LocX * 90 + CARD_WIDTH / 2, START_Y + LocY * 90 + CARD_WIDTH / 2);

    _timer = new QTimer;
    connect(_timer,&QTimer::timeout,this,[=](){
        if(Strength > 0 && x() > 0)
        {
            BaseGirls* res_girl = get_encountered_girl();
            if(res_girl)
            {
                res_girl->Damage(_attack);
                Strength = 0;
            }
            else
            {
                move(x() - _speed, y());
                LocX = (x() - START_X) / (double)CARD_WIDTH;
            }
        }
        else
        {
            this->close();
            delete this;
        }
    });
    _timer->start(40);
}

BaseGirls* Pin_Bullet::get_encountered_girl()
{
    BaseGirls* res_girl = nullptr;
    for(auto& cur_girl : con.GirlsList)
    {
        if(cur_girl->LocX == LocX && cur_girl->LocY == LocY)
        {
            res_girl = cur_girl;
            break;
        }
    }
    return res_girl;
}
