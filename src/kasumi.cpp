#include "kasumi.h"
#include "Control.h"
#include "starstone.h"

extern Control con;

Kasumi::Kasumi(int _X, int _Y, StarBoard* Board):BaseGirls(_X, _Y)
{
    Strength = 100;
    QPixmap pix(":/Kasumi_Battling.png");
    setPixmap(pix);
    setFixedSize(90,90);
    setScaledContents(true);
    move(80+(LocY-1)*90,100+(LocX-1)*90);
    Timer = new QTimer;
    ProduceTimer = new QTimer;
    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0)
        {
            if(Strength < 20)
            {
                setPixmap(QPixmap(":/Kasumi_Exhausted.png"));
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
    connect(ProduceTimer,&QTimer::timeout,this,[=](){
        StarStone* star = new StarStone(Board);
        star->setParent((QWidget*)this->parent());
        star->move(100+(LocY-1)*90,120+(LocX-1)*90);
        star->show();
        star->KasumiProduce();
    });
    ProduceTimer->start(12000);
    con.GirlsList.insert(this);
}


