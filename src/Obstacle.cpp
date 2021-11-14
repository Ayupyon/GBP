#include "Obstacle.h"
#include "Control.h"
#include "QPropertyAnimation"

#define STRENGTH 500

extern Control con;

Obstacle::Obstacle(int _X, int _Y, BattleScene* Battle, BaseMarinai* producer):BaseMarinai(_X, _Y, Battle), _producer(producer)
{
    Strength = STRENGTH;
    Speed = 0;
    _attack = 100;
    _type = LAND;

    QPixmap pix(":/obstacle.png");
    setPixmap(pix);
    setFixedSize(90,90);
    setScaledContents(true);
    move(START_X + LocX * CARD_WIDTH, START_Y + LocY * CARD_WIDTH);
    this->setParent(_cur_battlescene);
    Timer = new QTimer;

    connect(Timer,&QTimer::timeout,this,[=](){
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
        }
        else
        {
            auto it = con.MarinaiList.find(this);
            if(it!=con.MarinaiList.end()) con.MarinaiList.erase(it);
            this->close();
            delete this;
        }
    });
    this->show();
    Timer->start(200);
    con.MarinaiList.insert(this);
}

