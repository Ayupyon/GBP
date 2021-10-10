#include "rimi.h"
#include "Control.h"

extern Control con;

Rimi::Rimi(int _X,int _Y,StarBoard*):BaseGirls(_X,_Y)
{
    Strength = 850;
    QPixmap pix(":/Rimi_Battling.png");
    setPixmap(pix);
    setFixedSize(90,90);
    setScaledContents(true);
    move(80+(LocY-1)*90,100+(LocX-1)*90);
    Timer = new QTimer;
    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0)
        {
            if(Strength < 100)
            {
                setPixmap(QPixmap(":/Rimi_Exhausted.png"));
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
    Timer->start(500);
    con.GirlsList.insert(this);
}
