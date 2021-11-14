#include "Otae.h"
#include "Control.h"

extern Control con;

#define STRENGTH 200

Otae::Otae(int _X, int _Y, StarBoard*):BaseGirls(_X, _Y)
{
    _kind = OTAE;
    Strength = 200;
    QPixmap pix(":/Otae_Prepare.png");
    setPixmap(pix);
    setFixedSize(CARD_WIDTH, CARD_WIDTH);
    setScaledContents(true);
    move(START_X + LocX * 90, START_Y + LocY * 90);

    ready_timer = new QTimer;
    ready_counter = 0;
    connect(ready_timer, &QTimer::timeout, this, [=](){
        ready_counter++;
        if(Strength > 0)
        {
            if(ready_counter > 15)
            {
                setPixmap(QPixmap(":/Otae_Battling.png"));
                BaseMarinai* res_marinai = get_collide_marinai();
                if(res_marinai != nullptr)
                {
                    res_marinai->Damage(1800);
                    auto it = con.GirlsList.find(this);
                    if(it!=con.GirlsList.end()) con.GirlsList.erase(it);
                    this->close();
                    delete this;
                }
            }
        }
        else
        {
            ready_timer->stop();
            auto it = con.GirlsList.find(this);
            if(it!=con.GirlsList.end()) con.GirlsList.erase(it);
            this->close();
            delete this;
        }
    });
    ready_timer->start(1000);
    con.GirlsList.insert(this);
}

BaseMarinai* Otae::get_collide_marinai()
{
    BaseMarinai* res_marinai = nullptr;
    for(auto& cur_marinai: con.MarinaiList)
    {
        if(cur_marinai->LocX == LocX && cur_marinai->LocY == LocY && cur_marinai->_type == LAND)
            res_marinai = cur_marinai;
    }
    return res_marinai;
}
