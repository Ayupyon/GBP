#include "Michelle_Statue.h"
#include "NormalMarinai.h"
#include "WheelMarinai.h"
#include "HelmetMarinai.h"
#include "Control.h"

extern Control con;

Michelle_Statue::Michelle_Statue(int _X,int _Y,BattleScene* Battle):BaseMarinai(_X, _Y, Battle)
{
    Strength = 1000;
    Speed = 0;
    _attack = 0;
    _type = LAND;

    QPixmap pix(":/michelle_statue.png");
    setPixmap(pix);
    setFixedSize(90,100);
    setScaledContents(true);
    move(START_X + LocX * CARD_WIDTH, START_Y + LocY * CARD_WIDTH);
    this->setParent(_cur_battlescene);
    Timer = new QTimer;
    _action_counter = 0;
    connect(Timer,&QTimer::timeout,this,[=](){
        _action_counter++;
        if(Strength > 0 && x() > 0)
        {
            BaseGirls* cur_girl = EncounterWithGirls();
            if(cur_girl == nullptr)
            {
                this->move(this->x() - Speed,this->y());
                LocX = (x() - START_X) / (double)CARD_WIDTH;
            }
            else
                cur_girl->Damage(_attack);
            if(_action_counter >= 50)
            {
                produce_marinai();
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

void Michelle_Statue::produce_marinai()
{
    int type = rand() % 3 + 1;
    switch (type)
    {
    case NORMAL_MARINAI:
    {
        MICHELLE_PRODUCE_MARINAI(NormalMarinai)
        break;
    }
    case WHEEL_MARINAI:
    {
        MICHELLE_PRODUCE_MARINAI(WheelMarinai)
        break;
    }
    case HELMET_MARINAI:
    {
        MICHELLE_PRODUCE_MARINAI(HelmetMarinai)
        break;
    }
    default:
        break;
    }
}
