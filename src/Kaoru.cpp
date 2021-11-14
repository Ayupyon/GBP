#include "Kaoru.h"
#include "Control.h"

#define STRENGTH 200

extern Control con;

Kaoru::Kaoru(int _X, int _Y, StarBoard*):BaseGirls(_X, _Y)
{
    _kind = KAORU;
    Strength = STRENGTH;
    QPixmap pix(":/Kaoru_Battling.png");
    setPixmap(pix);
    setFixedSize(CARD_WIDTH, CARD_WIDTH);
    setScaledContents(true);
    move(START_X + LocX * 90, START_Y + LocY * 90);
    QTimer::singleShot(750, this, [=](){setPixmap(QPixmap(":/Kaoru_Prepared.png"));});
    QTimer::singleShot(1500, this, [=](){
        for(auto& cur_marinai : con.MarinaiList)
            cur_marinai->speed_down(cur_marinai->Speed);
        this->close();
        delete this;
    });
}
