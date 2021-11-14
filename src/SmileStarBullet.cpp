#include "SmileStarBullet.h"
#include "basemarinai.h"
#include "Control.h"
#include "Flymarinai.h"
#include <QPropertyAnimation>

extern Control con;

SmileStarBullet::SmileStarBullet(int startX, int startY, int endX, int endY):
_startX(startX), _startY(startY), _endX(endX), _endY(endY)
{
    LocX = _startX;
    LocY = _startY;
    _attack = 20;
    QPixmap pix(":/SmileStarBullet.png");
    setPixmap(pix);
    setFixedSize(30,30);
    setScaledContents(true);
    move(START_X + LocX * 90 + CARD_WIDTH / 2, START_Y + LocY * 90 + CARD_WIDTH / 2);
}

void SmileStarBullet::shoot()
{
    QPropertyAnimation *Animate = new QPropertyAnimation(this,"geometry");
    Animate->setDuration(1500);
    Animate->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    Animate->setEndValue(QRect(START_X + _endX * 90 + CARD_WIDTH / 2 - BIAS, START_Y + _endY * 90 + CARD_WIDTH / 2, this->width(), this->height()));
    Animate->setEasingCurve(QEasingCurve::Linear);
    Animate->start();
    QTimer::singleShot(1500, this, [=](){
        for(auto& cur_marinai : con.MarinaiList)
        {
            if(cur_marinai->LocX == _endX && cur_marinai->LocY == _endY)
            {
                if(cur_marinai->_type == SKY)
                {
                    FlyMarinai* marinai = dynamic_cast<FlyMarinai*>(cur_marinai);
                    marinai->fall();
                }
                cur_marinai->Damage(_attack);
            }
        }
        this->close();
        delete this;
    });
}
