#include "WheelMarinai.h"
#include "Control.h"

extern Control con;

static int SPEED = 5;

WheelMarinai::WheelMarinai(int _X, int _Y, BattleScene* scene):
BaseMarinai(_X, _Y, scene)
{
    Strength = 100;
    Speed = 5;
    _attack = 1000;
    _type = LAND;
    _first_collide = true;

    QPixmap pix(":/wheel_marinai.png");
    setPixmap(pix);
    setFixedSize(60, 120);
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
            {
                cur_girl->Damage(_attack);
                if(_first_collide)
                {
                    setFixedSize(60, 90);
                    setPixmap(QPixmap(":/Marinai.png"));
                    SPEED = 1;
                    _first_collide = false;
                    _attack = 5;
                }
            }
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
