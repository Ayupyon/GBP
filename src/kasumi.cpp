#include "kasumi.h"
#include "Control.h"
#include "starstone.h"

extern Control con;

#define STRENGTH 200

Kasumi::Kasumi(int _X, int _Y, StarBoard* Board):BaseGirls(_X, _Y)
{
    _kind = KASUMI;
    Strength = STRENGTH;
    QPixmap pix(":/Kasumi_Battling.png");
    setPixmap(pix);
    setFixedSize(90,90);
    setScaledContents(true);
    move(START_X + LocX * 90, START_Y + LocY * 90);
    Timer = new QTimer;
    ProduceTimer = new QTimer;
    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0)
        {
            if(Strength < STRENGTH / 5)
            {
                setPixmap(QPixmap(":/Kasumi_Exhausted.png"));
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
    Timer->start(500);
    connect(ProduceTimer,&QTimer::timeout,this,[=](){
        StarStone* star = new StarStone(Board);
        star->setParent((QWidget*)this->parent());
        star->move(START_X + LocX * 90, START_Y + LocY * 90);
        star->show();
        star->CardProduce();
    });
    ProduceTimer->start(20000);
    con.GirlsList.insert(this);
}


