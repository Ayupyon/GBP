#include "Himari.h"
#include "Control.h"

extern Control con;

#define STRENGTH 200

Himari::Himari(int _X, int _Y, StarBoard*):BaseGirls(_X, _Y)
{
    _kind = HIMARI;
    Strength = STRENGTH;
    QPixmap pix(":/Himari_Battling.png");
    setPixmap(pix);
    setFixedSize(CARD_WIDTH, CARD_WIDTH);
    setScaledContents(true);
    move(START_X + LocX * 90, START_Y + LocY * 90);
    Timer = new QTimer;
    _action_counter = 0;
    connect(Timer, &QTimer::timeout, this, [=](){
        _action_counter++;
        if(Strength > 0)
        {
            if(Strength < STRENGTH / 5)
                setPixmap(QPixmap(":/Himari_Exhausted.png"));
            else
                setPixmap(pix);
        }
        else
        {
            Timer->stop();
            auto it = con.GirlsList.find(this);
            if(it!=con.GirlsList.end()) con.GirlsList.erase(it);
            this->close();
            delete this;
        }
        if(_action_counter > 10)
        {
            BaseMarinai* cur_marinai = GetEncounteredMarinai();
            if(cur_marinai != nullptr)
            {
                move(x() - CARD_WIDTH / 2, y());
                QTimer::singleShot(300, this, [&](){
                    move(x() + CARD_WIDTH / 2, y());
                });
                cur_marinai->repeled();
                cur_marinai->Damage(50);
                this->Damage(25);
            }
            _action_counter = 0;
        }
    });
    Timer->start(500);
    con.GirlsList.insert(this);
}

BaseMarinai* Himari::GetEncounteredMarinai()
{
    for(auto& cur_marinai:con.MarinaiList)
    {
        if(cur_marinai->LocX == LocX && cur_marinai->LocY == LocY && cur_marinai->_type == LAND)
            return cur_marinai;
    }
    return nullptr;
}
