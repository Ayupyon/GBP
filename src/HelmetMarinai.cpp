#include "HelmetMarinai.h"
#include "Control.h"

extern Control con;

#define SPEED 3

HelmetMarinai::HelmetMarinai(int _X, int _Y, BattleScene* scene):
BaseMarinai(_X, _Y, scene)
{
    Strength = 500;
    Speed = 3;
    _attack = 10;
    _type = LAND;

    QPixmap pix(":/helmet_marinai.png");
    setPixmap(pix);
    setFixedSize(60,90);
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
            if(Strength < 100)
                setPixmap(QPixmap(":/Marinai.png"));
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
