#include "battlescene.h"
#include "arisa.h"
#include "kasumi.h"
#include "rimi.h"
#include "card.h"
#include "starstone.h"
#include "Control.h"
#include <QDebug>
#include <QIcon>
#include <QPainter>
#include <cstdlib>
#include <basemarinai.h>

extern Control con;
const int SquareWidth = 90;
QVector<QVector<int>> BattleScene::WaveList={{1,1,1,3,5,8,10,15,20,30,40,50,50,50},{100},{100},{100},{100}};

BattleScene::BattleScene(int index)
{
    srand(time(NULL));
    setFixedSize(1334/1.5,1002/1.5);
    setWindowIcon(QIcon("://Icon.png"));
    setWindowTitle("GirlBand vs Marinai");

    Board = new StarBoard();
    Board->setParent(this);
    Board->show();
    QFont font;
    font.setFamily("Cooper Black");
    font.setPixelSize(20);
    font.setBold(true);
    WaveLabel = new QLabel;
    WaveLabel->setParent(this);
    WaveLabel->setFont(font);
    WaveLabel->setFixedSize(200,30);
    WaveLabel->move(650,50);
    WaveLabel->setStyleSheet("Color:cyan;");

    ResLabel = new QLabel;
    ResLabel->setParent(this);
    ResLabel->setFixedSize(300,300);
    font.setFamily("华文彩云");
    font.setPixelSize(100);
    ResLabel->setFont(font);
    ResLabel->move((this->width()-ResLabel->width())/2,(this->height()-ResLabel->height())/2);
    ResLabel->setAlignment(Qt::AlignCenter);
    ResLabel->raise();

    StageIndex = index;

    switch (index + 1) {
        case 1:
        {
            Card* Card_Kasumi = new Card(":/Card_Kasumi.png",":/Kasumi_Battling.png",Board,50,7000,1);
            Card* Card_Arisa = new Card(":/Card_Arisa.png",":/Arisa_Battling.png",Board,100,7000,2);
            Card* Card_Rimi = new Card(":/Card_Rimi.png",":/Rimi_Battling.png",Board,50,30000,3);
            Card_Kasumi->setParent(this);
            Card_Arisa->setParent(this);
            Card_Rimi->setParent(this);
            Card_Kasumi->show();
            Card_Arisa->show();
            Card_Rimi->show();
            break;
        }
        default:
            break;
    }

    Card* Michelle = new Card(":/michelle_seal.png",":/michelle_seal2.png",Board,0,0,26);
    Michelle->setParent(this);
    Michelle->show();


    Wave = 0;
    CurWaveNum = 0;
    LeftMarinai = 0;

    QString str = QString("当前波数：%1/%2").arg(Wave).arg(WaveList[StageIndex].size());
    WaveLabel->setText(str);

    StarCounter = 1;
    WaveTimeCounter = -80;
    MarinaiCounter = -30;
    Timer = new QTimer(this);
    connect(Timer,&QTimer::timeout,this,[&](){
        StarCounter++;
        WaveTimeCounter++;
        MarinaiCounter++;
        if(StarCounter % 12 == 0)
        {
            ProduceStarStone();
        }
        if(MarinaiCounter > 0 && MarinaiCounter % 2 == 0)
        {
            if(CurWaveNum > 0)
            {
                ProduceMarinai();
                CurWaveNum--;
            }
            else if(con.MarinaiList.empty())
            {
                if(Wave < WaveList[StageIndex].size())
                {
                    CurWaveNum += WaveList[StageIndex][Wave++];
                    WaveTimeCounter = 0;
                    QString str = QString("当前波数：%1 / %2").arg(Wave).arg(WaveList[StageIndex].size());
                    WaveLabel->setText(str);
                }
                else
                {
                    qDebug() << "获得了胜利";
                    ResLabel->setStyleSheet("Color:red;");
                    ResLabel->setText("WIN!");
                    Timer->stop();
                    QTimer::singleShot(5000,this,[=](){
                        emit getBack();
                    });
                }
            }
        }
        if(WaveTimeCounter > 0 && WaveTimeCounter % 50 == 0)
        {
            if(Wave < WaveList[StageIndex].size())
            {
                CurWaveNum += WaveList[StageIndex][Wave++];
                WaveTimeCounter = 0;
                QString str = QString("当前波数：%1 / %2").arg(Wave).arg(WaveList[StageIndex].size());
                WaveLabel->setText(str);
            }
        }
        for(auto Marinai : con.MarinaiList)
        {
            if(Marinai->x() < 20)
            {
                qDebug() << "游戏失败";
                ResLabel->setText("LOSE");
                Timer->stop();
                QTimer::singleShot(5000,this,[=](){
                    emit getBack();
                });
            }
        }
    });
    Timer->start(1000);
}

void BattleScene::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter ScenePainter(this);
    QPixmap pix(":/BattleBackGroud.png");
    ScenePainter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/BattleSquare.png");
    for(int i=0;i<54;i++)
    {
        ScenePainter.drawPixmap(80+(i%9)*SquareWidth,100+(i/9)*SquareWidth,SquareWidth,SquareWidth,pix);
    }
    pix.load(":/StarStone1.png");
    ScenePainter.drawPixmap(0,0,80,80,pix);
//    pix.load(":/ShowStarStone.png");
//    ScenePainter.drawPixmap(0,80,80,80,pix);
}

void BattleScene::ProduceMarinai()
{
    BaseMarinai* marinai = new BaseMarinai(rand()%6+1,9,this);
    marinai->show();
}

void BattleScene::ProduceStarStone()
{
    StarStone* Stone = new StarStone(Board);
    Stone->setParent(this);
    Stone->move(rand()%300+200,rand()%50-100);
    Stone->show();
    Stone->autoProduce();
}
