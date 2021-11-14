#include "Cart_Marinai.h"
#include "Control.h"

#define SPEED 3

extern Control con;

Cart_Marinai::Cart_Marinai(int _X, int _Y, BattleScene* Battle) : BaseMarinai(_X, _Y, Battle)
{
    Strength = 750;
    Speed = SPEED;
    _attack = 2000;
    _type = LAND;

    QPixmap pix(":/Cart_Marinai.png");
    setPixmap(pix);
    setFixedSize(90,90);
    setScaledContents(true);
    move(START_X + LocX * CARD_WIDTH + BIAS, START_Y + LocY * CARD_WIDTH);
    this->setParent(_cur_battlescene);
    Timer = new QTimer;
    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0 && x() > 0)
        {
            if(_speed_down_counter)
                _speed_down_counter--;
            if(_speed_down_counter == 0)
                Speed = SPEED;
            BaseGirls* cur_girl = _speed_down_counter ? nullptr : EncounterWithGirls();
            if(cur_girl == nullptr)
            {
                this->move(this->x() - Speed,this->y());
                LocX = (x() - START_X) / (double)CARD_WIDTH;
            }
            else
                cur_girl->Damage(_attack);
        }
        else
        {
            auto it = con.MarinaiList.find(this);
            if(it!=con.MarinaiList.end()) con.MarinaiList.erase(it);
            this->close();
            delete this;
        }
    });
    Timer->start(200);
    con.MarinaiList.insert(this);
}
