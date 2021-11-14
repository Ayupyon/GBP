#include "Aya.h"
#include "Control.h"
#include "starstone.h"

#define STRENGTH 200

extern Control con;

Aya::Aya(int _X, int _Y, StarBoard* Board):BaseGirls(_X, _Y), _board(Board)
{
    _kind = AYA;
    Strength = STRENGTH;
    QPixmap pix(":/Aya_Battling.png");
    setPixmap(pix);
    setFixedSize(CARD_WIDTH, CARD_WIDTH);
    setScaledContents(true);
    move(START_X + LocX * 90, START_Y + LocY * 90);
    Timer = new QTimer;

    connect(Timer,&QTimer::timeout,this,[=](){
        if(Strength > 0)
        {
            if(Strength < STRENGTH / 5)
                setPixmap(QPixmap(":/Aya_Exhausted.png"));
            if(CollideWithMarinais())
            {
                setPixmap(QPixmap(":/Aya_Exhausted.png"));
                for(auto& cur_marinai : con.MarinaiList)
                {
                    if(cur_marinai->LocX == LocX && cur_marinai->LocY == LocY)
                        cur_marinai->Damage(1800);
                }
                Timer->stop();
                QTimer::singleShot(1500, this, [=](){
                    auto it = con.GirlsList.find(this);
                    if(it!=con.GirlsList.end()) con.GirlsList.erase(it);
                    this->close();
                    delete this;
                });
                for(int i = 0; i < 5; ++i)
                {
                    QWidget* cur_scene = dynamic_cast<QWidget*>(this->parent());
                    StarStone* star = new StarStone(_board);
                    star->setParent(cur_scene);
                    star->move(START_X + LocX * 90, START_Y + LocY * 90);
                    QTimer::singleShot(500 + 200 * i, this, [=](){
                        star->show();
                        star->CardProduce();
                    });
                }
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
    con.GirlsList.insert(this);
}
