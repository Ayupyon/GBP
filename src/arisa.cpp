#include "arisa.h"
#include "Control.h"
#include "starbullet.h"
#include "choosescene.h"
#include "StartScene.h"

extern Control con;

Arisa::Arisa(int _X,int _Y,StarBoard*):BaseGirls(_X, _Y)
{
    Strength = 100;
    QPixmap pix(":/Arisa_Battling.png");
    setPixmap(pix);
    setFixedSize(90,90);
    setScaledContents(true);
    move(80+(LocY-1)*90,100+(LocX-1)*90);
    Timer = new QTimer;
    BulletTimer = new QTimer;
    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0)
        {
            if(Strength < 20)
            {
                setPixmap(QPixmap(":/Arisa_Exhausted.png"));
            }
            if(CollideWithMarinais())
            {
                Damage();
            }
        }
        else
        {
            auto it = con.GirlsList.find(this);
            if(it!=con.GirlsList.end()) con.GirlsList.erase(it);
            this->close();
            delete this;
        }
    });
    connect(BulletTimer,&QTimer::timeout,this,[=](){
        if(FindMarinais())
        {
            StarBullet* star = new StarBullet(LocX,LocY);
            star->setParent((QWidget*)this->parent());
            star->show();
        }
    });
    Timer->start(500);
    BulletTimer->start(2000);
    con.GirlsList.insert(this);
}

bool Arisa::FindMarinais()
{
    for(auto Marinai:con.MarinaiList)
    {
        if(LocX == Marinai->LocX && Marinai->x() > x())
            return true;
    }
    return false;
}
