#include "rimi.h"
#include "Control.h"

extern Control con;

#define STRENGTH 1500

Rimi::Rimi(int _X,int _Y,StarBoard*):BaseGirls(_X,_Y)
{
    _kind = RIMI;
    Strength = STRENGTH;
    QPixmap pix(":/Rimi_Battling.png");
    setPixmap(pix);
    setFixedSize(90,90);
    setScaledContents(true);
    move(START_X + LocX * 90, START_Y + LocY * 90);
    Timer = new QTimer;
    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0)
        {
            if(Strength < STRENGTH / 5)
                setPixmap(QPixmap(":/Rimi_Exhausted.png"));
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
