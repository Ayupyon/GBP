#include "Kokoro.h"
#include "SmileStarBullet.h"
#include "Control.h"

#define STRENGTH 200

extern Control con;

Kokoro::Kokoro(int _X, int _Y, StarBoard*):BaseGirls(_X, _Y)
{
    _kind = KOKORO;
    Strength = STRENGTH;
    _attack_counter = 0;
    QPixmap pix(":/Kokoro_Battling1.png");
    setPixmap(pix);
    setFixedSize(CARD_WIDTH, CARD_WIDTH);
    setScaledContents(true);
    move(START_X + LocX * 90, START_Y + LocY * 90);

    Timer = new QTimer;
    connect(Timer, &QTimer::timeout, this, [=](){
        if(Strength > 0)
        {
            if(Strength < STRENGTH / 5)
                setPixmap(QPixmap(":/Kokoro_Exhausted.png"));
            BaseMarinai* res_marinai = get_closest_marinai();
            if(res_marinai != nullptr)
            {
                setPixmap(QPixmap(":/Kokoro_Battling2"));
                BattleScene* cur_scene = dynamic_cast<BattleScene*>(this->parent());
                SmileStarBullet* bullet = new SmileStarBullet(LocX, LocY, res_marinai->LocX, res_marinai->LocY);
                bullet->setParent(cur_scene);
                bullet->show();
                bullet->shoot();
            }
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
    Timer->start(1000);
    con.GirlsList.insert(this);
}

BaseMarinai* Kokoro::get_closest_marinai()
{
    BaseMarinai* res_marinai = nullptr;
    int x_min = INT_MAX;
    for(auto& cur_marinai: con.MarinaiList)
    {
        if(cur_marinai->LocX < x_min)
        {
            x_min = cur_marinai->LocX;
            res_marinai = cur_marinai;
        }
    }
    return res_marinai;
}
