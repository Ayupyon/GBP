#include "basemarinai.h"
#include <QDebug>
#include "starbullet.h"
#include "StartScene.h"
#include "choosescene.h"
#include "battlescene.h"
#include "Control.h"

extern Control con;

#define INF 99999

BaseMarinai::BaseMarinai(int _X,int _Y,BattleScene* Battle)
{
    Type = marinais;
    LocX = _X;
    LocY = _Y;
    Strength = 100;
    QPixmap pix(":/Marinai.png");
    setPixmap(pix);
    setFixedSize(70,100);
    setScaledContents(true);
    move(LocY*90+20,LocX*90);
    setParent(Battle);
   // move(150,150);
   // qDebug() << "产生了一个Marinai";
    Timer = new QTimer;
    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0 && x() > 0)
        {
            if(!EncounterWithGirls())
            {
                this->move(this->x()-4,this->y());
               // Strength -= 1;
            }
        }
        else
        {
            auto it = con.MarinaiList.find(this);
            if(it!=con.MarinaiList.end()) con.MarinaiList.erase(it);
            this->close();
            //Battle->LeftMarinai--;
            delete this;
        }
    });
    Timer->start(320);
    //qDebug()<<this;
    con.MarinaiList.insert(this);
}

bool BaseMarinai::EncounterWithGirls()
{
    int minDis = INF;
    for(auto Girl:con.GirlsList)
    {
        if(LocX==Girl->LocX)
        {
            int Dis = x()-Girl->x();
            if(Dis > 0 && Dis < minDis)
            {
                minDis = Dis;
            }
        }
    }
    return minDis < 70;
}

void BaseMarinai::Damage()
{
    Strength -= 10;
}


