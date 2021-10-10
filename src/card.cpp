#include "card.h"
#include "kasumi.h"
#include "arisa.h"
#include "rimi.h"
#include "Control.h"
#include <QDebug>
#include <QMouseEvent>

extern Control con;

QVector<QString> Card::GirlsPixPath={"",":/Kasumi_Battling.png",":/Arisa_Battling.png",":/Rimi_Battling.png",":/Saya_Battling.png",":/Otae_Battling.png"
                                    "","","","","","","","","","","","","","","","","","","",""};

Card::Card(QString path,QString pressedPath,StarBoard* board,int cost,int coolDown,int index):
    Path(path),PressedPath(pressedPath),Board(board),Cost(cost),CoolDown(coolDown),Index(index)
{
    QPixmap pix(Path);
    setPixmap(pix);
    setFixedSize(90,90);
    setScaledContents(true);
//    QLabel* CoolDownLabel = new QLabel;
//    if(CoolDown > 0)
//    {
//        pix.load(":/CoolDown.png");
//        CoolDownLabel->setParent(this);
//        CoolDownLabel->setPixmap(pix);
//        CoolDownLabel->setFixedSize(90,90);
//        setScaledContents(true);
//    }
    if(Index == 26) move(90*6,0);
    else
    {
        while(index>5) index-=5;
        move(90*index,0);
    }
    Counter = 0;
    Timer = new QTimer;
    connect(Timer,&QTimer::timeout,this,[&](){
        Counter -= 100;
        if(Counter == 0)
        {
           // CoolDownLabel->close();
            this->show();
            Timer->setInterval(0);
            Timer->stop();
        }
    });
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
    if(event->x()+x()<80||event->y()<100)
    {
        unsetCursor();
        return;
    }
    int _X=qRound((event->y()-100)/100.0);
    int _Y=qRound((event->x()+x()-90)/100.0);
    //qDebug()<<_X<<_Y;
    if(Index!=26)
    {
        for(auto Girl:con.GirlsList)
        {
            if(Girl->LocX == _X+1 && Girl->LocY == _Y+1)
            {
                unsetCursor();
                return;
            }
        }
        switch (Index) {
            case 1:
            {
                Kasumi* kasumi = new Kasumi(_X+1,_Y+1,Board);
                kasumi->setParent((QWidget*)this->parent());
                kasumi->show();
                Board->StarReduce(50);
                break;
            }
            case 2:
            {
                Arisa* arisa = new Arisa(_X+1,_Y+1,Board);
                arisa->setParent((QWidget*)this->parent());
                arisa->show();
                Board->StarReduce(100);
                break;
            }
            case 3:
            {
                Rimi* rimi = new Rimi(_X+1,_Y+1,Board);
                rimi->setParent((QWidget*)this->parent());
                rimi->show();
                Board->StarReduce(50);
                break;
            }
            default:
                break;
        }
        this->hide();
        Counter = CoolDown;
        Timer->start(100);
    }
    else
    {
        for(auto Girl:con.GirlsList)
        {
            if(Girl->LocX == _X+1 && Girl->LocY==_Y+1)
            {
                Girl->Strength = 0;
            }
        }
    }

    unsetCursor();
}
