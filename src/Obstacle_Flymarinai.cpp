#include "Obstacle_Flymarinai.h"
#include "Control.h"
#include "Obstacle.h"

extern Control con;

#define STRENGTH 300

static int SPEED = 3;

Obstacle_FlyMarinai::Obstacle_FlyMarinai(int _X, int _Y, BattleScene* Battle):FlyMarinai(_X, _Y, Battle)
{
    Strength = STRENGTH;
    Speed = SPEED;
    _attack = 5;
    _is_fall = false;

    QPixmap pix(":/obs_flying_marinai.png");
    setPixmap(pix);
    setFixedSize(90, 60);
    setScaledContents(true);
    move(START_X + LocX * CARD_WIDTH + BIAS, START_Y + LocY * CARD_WIDTH - BIAS);
    this->setParent(_cur_battlescene);
    Timer = new QTimer;
    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0 && x() > 0)
        {
            if(_speed_down_counter)
                _speed_down_counter--;
            if(_speed_down_counter == 0)
                Speed = SPEED;
            BaseGirls* cur_girl = _is_fall ? _speed_down_counter ? nullptr : EncounterWithGirls() : nullptr;
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

void Obstacle_FlyMarinai::fall()
{
    if(_is_fall == true)
        return;
    setPixmap(QPixmap(":/Marinai.png"));
    setFixedSize(60, 90);
    Obstacle *new_obstacle = new Obstacle(LocX, LocY, _cur_battlescene, this);
    move(START_X + LocX * CARD_WIDTH + BIAS, START_Y + LocY * CARD_WIDTH);
    _is_fall = true;
    _type = LAND;
    SPEED = 1;
}
