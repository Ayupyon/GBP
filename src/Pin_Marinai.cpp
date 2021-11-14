#include "Pin_Marinai.h"
#include "Control.h"
#include "Pin_Bullet.h"

extern Control con;

#define SPEED 1

Pin_Marinai::Pin_Marinai(int _X, int _Y, BattleScene* Battle):BaseMarinai(_X, _Y, Battle)
{
    Strength = 200;
    Speed = 1;
    _attack = 5;
    _type = LAND;

    QPixmap pix(":/pin_marinai.png");
    setPixmap(pix);
    setFixedSize(90,90);
    setScaledContents(true);
    move(START_X + LocX * CARD_WIDTH + BIAS, START_Y + LocY * CARD_WIDTH);
    this->setParent(_cur_battlescene);
    Timer = new QTimer;
    _action_counter = 0;
    connect(Timer,&QTimer::timeout,this,[=](){
        _action_counter++;
        if(Strength > 0 && x() > 0)
        {
            if(_speed_down_counter)
            {
                _speed_down_counter--;
                _action_counter--;
            }
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
            if(_action_counter > 10)
            {
                BattleScene* cur_scene = dynamic_cast<BattleScene*>(this->parent());
                Pin_Bullet* pin = new Pin_Bullet(LocX, LocY);
                pin->setParent(cur_scene);
                pin->show();
                _action_counter = 0;
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
