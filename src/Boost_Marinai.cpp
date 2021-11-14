#include "Boost_Marinai.h"
#include "Control.h"

#define SPEED 1
extern Control con;

Boost_Marinai::Boost_Marinai(int _X, int _Y, BattleScene* Battle):BaseMarinai(_X, _Y, Battle)
{
    Strength = 200;
    Speed = 1;
    _attack = 5;
    _type = LAND;

    QPixmap pix(":/boost_Marinai.png");
    setPixmap(pix);
    setFixedSize(80,90);
    setScaledContents(true);
    move(START_X + LocX * CARD_WIDTH + BIAS, START_Y + LocY * CARD_WIDTH);
    this->setParent(_cur_battlescene);
    Timer = new QTimer;
    _action_counter = 0;
    connect(Timer,&QTimer::timeout,this,[=](){
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
                _action_counter++;
                if(_action_counter > 30)
                {
                    for(auto& cur_marinai : con.MarinaiList)
                    {
                        BattleScene* cur_scene = dynamic_cast<BattleScene*>(this->parent());
                        QLabel* boost_label = new QLabel(cur_scene);
                        boost_label->setPixmap(QPixmap(":/boost.png"));
                        boost_label->setFixedSize(50, 50);
                        boost_label->setScaledContents(true);
                        boost_label->move(cur_marinai->x(), cur_marinai->y());
                        boost_label->show();
                        QTimer::singleShot(1000, boost_label, [=](){
                            cur_marinai->Strength += 100;
                            boost_label->close();
                            delete boost_label;
                        });
                    }
                    _action_counter = 0;
                }
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
