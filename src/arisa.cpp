#include "arisa.h"
#include "Control.h"
#include "starbullet.h"
#include "choosescene.h"
#include "StartScene.h"

#define STRENGTH 200

extern Control con;

Arisa::Arisa(int _X, int _Y, StarBoard*):BaseGirls(_X, _Y)
{
    _kind = ARISA;
    Strength = STRENGTH;
    QPixmap pix(":/Arisa_Battling.png");
    setPixmap(pix);
    setFixedSize(CARD_WIDTH, CARD_WIDTH);
    setScaledContents(true);
    move(START_X + LocX * 90, START_Y + LocY * 90);
    Timer = new QTimer;
    _attack_counter = 0;
    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0)
        {
            if(Strength < STRENGTH / 5)
                setPixmap(QPixmap(":/Arisa_Exhausted.png"));
            if(FindMarinais())
            {
                _attack_counter++;
                if(_attack_counter > 4)
                {
                    StarBullet* star = new StarBullet(LocX,LocY);
                    star->setParent((QWidget*)this->parent());
                    star->show();
                    _attack_counter = 0;
                }
            }
            else
                _attack_counter = 0;
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

bool Arisa::FindMarinais()
{
    for(auto Marinai:con.MarinaiList)
    {
        if(LocY == Marinai->LocY)
            return true;
    }
    return false;
}
