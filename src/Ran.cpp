#include "Ran.h"
#include "Control.h"
#include "BoostBullet.h"

#define STRENGTH 200

extern Control con;

Ran::Ran(int _X, int _Y, StarBoard*):BaseGirls(_X, _Y)
{
    _kind = RAN;
    Strength = STRENGTH;
    QPixmap pix(":/Ran_Battling.png");
    setPixmap(pix);
    setFixedSize(CARD_WIDTH, CARD_WIDTH);
    setScaledContents(true);
    move(START_X + LocX * 90, START_Y + LocY * 90);
    Timer = new QTimer;
    _prepare_counter = 0;
    _bullet_counter = 0;
    connect(Timer,&QTimer::timeout,this,[=](){
        _prepare_counter++;
        if(Strength > 0)
        {
            if(Strength < STRENGTH / 5)
                setPixmap(QPixmap(":/Ran_Exhausted.png"));
            if(_prepare_counter > 20)
                setPixmap(QPixmap(":/Ran_Prepared.png"));
            if(FindMarinais())
            {
                BattleScene* cur_scene = dynamic_cast<BattleScene*>(this->parent());
                if(_prepare_counter > 20)
                {
                    for(int i = 0; i < 5; ++i)
                    {
                        QTimer::singleShot(200 * (i + 1), this, [=](){
                            ProduceBullet(cur_scene);
                        });
                    }
                    setPixmap(QPixmap(":/Ran_Battling.png"));
                    _bullet_counter = 0;
                    _prepare_counter = 0;
                }
                else
                {
                    _bullet_counter++;
                    if(_bullet_counter > 4)
                    {
                        ProduceBullet(cur_scene);
                        _bullet_counter = 0;
                    }
                     _prepare_counter = 0;
                }
            }
            else
                _bullet_counter = 0;
        }
        else
        {
            Timer->stop();
            auto it = con.GirlsList.find(this);
            if(it!=con.GirlsList.end()) con.GirlsList.erase(it);
            this->close();
            delete this;
        }
    });
    Timer->start(500);
    con.GirlsList.insert(this);
}

void Ran::ProduceBullet(BattleScene* scene)
{
    BoostBullet* boost = new BoostBullet(LocX, LocY);
    boost->setParent(scene);
    boost->show();
}

bool Ran::FindMarinais()
{
    for(auto Marinai:con.MarinaiList)
    {
        if(LocY == Marinai->LocY)
            return true;
    }
    return false;
}
