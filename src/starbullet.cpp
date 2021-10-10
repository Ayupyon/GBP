#include "starbullet.h"
#include "basemarinai.h"
#include "Control.h"

extern Control con;

StarBullet::StarBullet(int _X,int _Y)
{
    LocX = _X;
    LocY = _Y;
    Strength = 1;
    QPixmap pix(":/starBullet1.png");
    setPixmap(pix);
    setFixedSize(30,30);
    setScaledContents(true);
    this->move(125+(LocY-1)*90,145+(LocX-1)*90);
    Timer = new QTimer;
    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0 && x() < 1002)
        {
            if(CollideWithMarinai()) Strength = 0;
            else this->move(this->x()+10,this->y());
        }
        else
        {
            this->close();
            delete this;
        }
    });
    Timer->start(40);
}

bool StarBullet::CollideWithMarinai()
{
    for(auto Marinai:con.MarinaiList)
    {
        if(LocX == Marinai->LocX && Marinai->x()-x() >= -50 && Marinai->x() - x() < 10)
        {
            Marinai->Damage();
            return true;
        }
    }
    return false;
}


