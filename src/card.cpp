#include "card.h"
#include "kasumi.h"
#include "arisa.h"
#include "rimi.h"
#include "Saya.h"
#include "Ran.h"
#include "Moca.h"
#include "Himari.h"
#include "Tomoe.h"
#include "Tsugu.h"
#include "Aya.h"
#include "Kokoro.h"
#include "Kaoru.h"
#include "Control.h"
#include "Land.h"
#include "Otae.h"
#include <QDebug>
#include <QMouseEvent>

extern Control con;

Card::Card(QString path,QString pressedPath,StarBoard* board,int cost,int coolDown,int index, int type, QWidget* parent):
    Path(path),PressedPath(pressedPath),Board(board),Cost(cost),CoolDown(coolDown),Index(index),_card_type(type)
{   
    QPixmap pix(Path);
    setPixmap(pix);
    setFixedSize(90,90);
    setScaledContents(true);
    this->setParent(parent);

    if(Index == 10)
        move(90 * 6, 0);
    else 
        move(90 + 90 * (Index % 5), 90 * (Index / 5));
    Counter = 0;
    Timer = new QTimer;
    connect(Timer,&QTimer::timeout,this,[&](){
        Counter -= 100;
        if(Counter == 0)
        {
            this->show();
            Timer->setInterval(0);
            Timer->stop();
        }
    });
    this->show();
}

void Card::mousePressEvent(QMouseEvent *event)
{
    if(Board->StarNum < Cost || Counter > 0)
    {
        event->ignore();
        return;
    }
    QPixmap pix=QPixmap(PressedPath).scaled(90,90);
    setCursor(pix);
}

void Card::mouseReleaseEvent(QMouseEvent *event)
{
    if(Board->StarNum < Cost || Counter > 0)
    {
        event->ignore();
        return;
    }
    qDebug() << event->x() << event->y();
    if(event->x() + x() < START_X || event->y() + y() < START_Y)
    {
        unsetCursor();
        return;
    }
    int _X=(event->x() + x() - START_X)/(double)CARD_WIDTH;
    int _Y=(event->y() + y() - START_Y)/(double)CARD_WIDTH;
    if(_X >= 9 || _Y >= 5)
    {
        unsetCursor();
        return;
    }
    if(_card_type != 26)
    {
        for(auto Girl:con.GirlsList)
        {
            if(Girl->LocX == _X && Girl->LocY == _Y)
            {
                unsetCursor();
                return;
            }
        }
        BattleScene* cur_scene = dynamic_cast<BattleScene*>(this->parent());
        if((this->*set_card[_card_type])(_X, _Y, cur_scene->land_type[_Y][_X]))
        {
            Board->StarReduce(Cost);
            this->hide();
            Counter = CoolDown;
            Timer->start(100);
        }
    }
    else
    {
        for(auto Girl:con.GirlsList)
        {
            if(Girl->LocX == _X && Girl->LocY==_Y)
                Girl->Strength = 0;
        }
    }

    unsetCursor();
}

bool Card::set_kasumi(int _X, int _Y, int type)
{
    if(type == NORMAL || type == PPP_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Kasumi* kasumi = new Kasumi(_X,_Y,Board);
    kasumi->setParent((QWidget*)this->parent());
    kasumi->show();
    return true;
}

bool Card::set_arisa(int _X, int _Y, int type)
{
    if(type == NORMAL || type == PPP_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Arisa* arisa = new Arisa(_X,_Y,Board);
    arisa->setParent((QWidget*)this->parent());
    arisa->show();
    return true;
}

bool Card::set_rimi(int _X, int _Y, int type)
{
    if(type == NORMAL || type == PPP_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Rimi* rimi = new Rimi(_X,_Y,Board);
    rimi->setParent((QWidget*)this->parent());
    rimi->show();
    return true;
}

bool Card::set_saya(int _X, int _Y, int type)
{
    if(type == NORMAL || type == PPP_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Saya* saya = new Saya(_X, _Y, Board);
    saya->setParent((QWidget*)this->parent());
    saya->show();
    return true;
}

bool Card::set_otae(int _X, int _Y, int type)
{
    if(type == NORMAL || type == PPP_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Otae* otae = new Otae(_X, _Y, Board);
    otae->setParent((QWidget*)this->parent());
    otae->show();
    return true;
}

bool Card::set_ran(int _X, int _Y, int type)
{
    if(type == NORMAL || type == AG_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Ran* ran = new Ran(_X, _Y, Board);
    ran->setParent((QWidget*)this->parent());
    ran->show();
    return true;
}

bool Card::set_moca(int _X, int _Y, int type)
{
    if(type == NORMAL || type == AG_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Moca* moca = new Moca(_X, _Y, Board);
    moca->setParent((QWidget*)this->parent());
    moca->show();
    return true;
}

bool Card::set_himari(int _X, int _Y, int type)
{
    if(type == NORMAL || type == AG_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Himari* himari = new Himari(_X, _Y, Board);
    himari->setParent((QWidget*)this->parent());
    himari->show();
    return true;
}

bool Card::set_tomoe(int _X, int _Y, int type)
{
    if(type == NORMAL || type == AG_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Tomoe* tomoe = new Tomoe(_X, _Y, Board);
    tomoe->setParent((QWidget*)this->parent());
    tomoe->show();
    return true;
}

bool Card::set_tsugu(int _X, int _Y, int type)
{
    if(type == NORMAL || type == AG_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Tsugu* tsugu = new Tsugu(_X, _Y, Board);
    tsugu->setParent((QWidget*)this->parent());
    tsugu->show();
    return true;
}

bool Card::set_aya(int _X, int _Y, int type)
{
    if(type == NORMAL || type == PP_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Aya* aya = new Aya(_X, _Y, Board);
    aya->setParent((QWidget*)this->parent());
    aya->show();
    return true;
}

bool Card::set_kokoro(int _X, int _Y, int type)
{
    if(type == NORMAL || type == HHW_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Kokoro* kokoro = new Kokoro(_X, _Y, Board);
    kokoro->setParent((QWidget*)this->parent());
    kokoro->show();
    return true;
}

bool Card::set_kaoru(int _X, int _Y, int type)
{
    if(type == NORMAL || type == HHW_LAND);
    else if(type == SKY)
    {

    }
    else
         return false;
    Kaoru* kaoru = new Kaoru(_X, _Y, Board);
    kaoru->setParent((QWidget*)this->parent());
    kaoru->show();
    return true;
}
