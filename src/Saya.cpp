#include "Saya.h"
#include "Control.h"
#include "rimi.h"

#define STRENGTH 200

extern Control con;

Saya::Saya(int _X, int _Y, StarBoard* board):BaseGirls(_X, _Y), _board(board)
{
    _kind = SAYA;
    Strength = STRENGTH;
    QPixmap pix_normal(":/Saya_Battling.png");
    setPixmap(pix_normal);
    setFixedSize(CARD_WIDTH, CARD_WIDTH);
    setScaledContents(true);
    move(START_X + LocX * 90, START_Y + LocY * 90);

    ready_timer = new QTimer;
    ready_counter = 0;
    connect(ready_timer, &QTimer::timeout, this, [=](){
        ready_counter++;
        if(Strength > 0)
        {
            if(Strength < STRENGTH / 5)
                setPixmap(QPixmap(":/Saya_Exhausted.png"));
            if(ready_counter > 15)
            {
                setPixmap(QPixmap(":/Saya_Ready.png"));
                BaseMarinai* res_marinai = get_closest_marinai();
                if(res_marinai != nullptr)
                {
                    set_chocoriro(res_marinai);
                    ready_counter = 0;
                    setPixmap(pix_normal);
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
    ready_timer->start(1000);
    con.GirlsList.insert(this);
}

BaseMarinai* Saya::get_closest_marinai()
{
    BaseMarinai* res_marinai = nullptr;
    int x_min = INT_MAX;
    for(auto& cur_marinai: con.MarinaiList)
    {
        if(cur_marinai->_type == LAND && cur_marinai->LocX < x_min && cur_marinai->LocX >= 1 && !cur_marinai->EncounterWithGirls())
        {
            x_min = cur_marinai->LocX;
            res_marinai = cur_marinai;
        }
    }
    return res_marinai;
}

void Saya::set_chocoriro(BaseMarinai* res_marinai)
{
    for(auto& girl : con.GirlsList)
    {
        if(girl->LocX == res_marinai->LocX && girl->LocY == res_marinai->LocY)
            return;
    }
    QLabel* chocoriro = new QLabel((QWidget*)this->parent());
    chocoriro->setFixedSize(CARD_WIDTH, CARD_WIDTH);
    setScaledContents(true);
    chocoriro->setPixmap(QPixmap(":/chocoriro.png"));
    chocoriro->move(START_X + res_marinai->LocX * CARD_WIDTH, START_Y + res_marinai->LocY * CARD_WIDTH);
    chocoriro->show();
    QTimer::singleShot(1000, this, [=](){
        chocoriro->close();
        Rimi* rimi = new Rimi(res_marinai->LocX, res_marinai->LocY, _board);
        rimi->setParent((QWidget*)this->parent());
        rimi->show();
    });
}
