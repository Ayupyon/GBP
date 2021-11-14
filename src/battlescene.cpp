#include "battlescene.h"
#include "NormalMarinai.h"
#include "WheelMarinai.h"
#include "HelmetMarinai.h"
#include "Michelle_Statue.h"
#include "Normal_Flymarinai.h"
#include "Obstacle_Flymarinai.h"
#include "Cart_Marinai.h"
#include "Pin_Marinai.h"
#include "Boost_Marinai.h"
#include "arisa.h"
#include "kasumi.h"
#include "rimi.h"
#include "card.h"
#include "starstone.h"
#include <QDebug>
#include <QTextStream>
#include <QIcon>
#include <QPainter>
#include <QFile>
#include <cstdlib>
#include <QString>

#include "Control.h"

extern Control con;

BattleScene::BattleScene(int index)
{
    srand(time(NULL));
    setFixedSize(1334/1.5,1002/1.5);
    setWindowIcon(QIcon("://Icon.png"));
    setWindowTitle("GirlBand vs Marinai");

    Board = new StarBoard(this);
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

    StageIndex = index;

    SetLand();
    SetWave();

    switch (index + 1) {
    case 1:
    {
        Card* Card_Kasumi = new Card(":/Card_Kasumi.png",":/Kasumi_Battling.png",Board,50,7000,0, KASUMI,this);
        Card* Card_Arisa = new Card(":/Card_Arisa.png",":/Arisa_Battling.png",Board,100,7000,1, ARISA,this);
        Card* Card_Rimi = new Card(":/Card_Rimi.png",":/Rimi_Battling.png",Board,50,30000,2, RIMI,this);
        Card* Card_Saya = new Card(":/Card_Saya.png", ":/Saya_Battling.png", Board, 250, 50000, 3, SAYA, this);
        Card* Card_Otae = new Card(":/Card_Otae.png", ":/Otae_Battling.png", Board, 25, 30000, 4, OTAE, this);
        Card* Card_Ran = new Card(":/Card_Ran.png", ":/Ran_Battling.png", Board, 150, 7000, 5, RAN, this);
        break;
    }
    case 2:
    {
        Card* Card_Kasumi = new Card(":/Card_Kasumi.png",":/Kasumi_Battling.png",Board,50,7000,0, KASUMI,this);
        Card* Card_Rimi = new Card(":/Card_Rimi.png",":/Rimi_Battling.png",Board,50,30000,1, RIMI,this);
        Card* Card_Otae = new Card(":/Card_Otae.png", ":/Otae_Battling.png", Board, 25, 30000, 2, OTAE, this);
        Card* Card_Ran = new Card(":/Card_Ran.png", ":/Ran_Battling.png", Board, 150, 7000, 3, RAN, this);
        Card* Card_Moca = new Card(":/Card_Moca.png", ":/Moca_Battling.png", Board, 75, 7000, 4, MOCA, this);
        Card* Card_Himari = new Card(":/Card_Himari.png", ":/Himari_Battling.png", Board, 75, 15000, 5, HIMARI, this);
        Card* Card_Tomoe = new Card(":/Card_Tomoe.png", ":/Tomoe_Battling.png", Board, 50, 30000, 6, TOMOE, this);
        Card* Card_Tsugu = new Card(":/Card_Tsugu.png", ":/Tsugu_Battling.png", Board, 75, 7000, 7, TSUGU, this);
        break;
    }
    case 4:
    {
        Card* Card_Kasumi = new Card(":/Card_Kasumi.png",":/Kasumi_Battling.png",Board,50,7000,0, KASUMI,this);
        Card* Card_Rimi = new Card(":/Card_Rimi.png",":/Rimi_Battling.png",Board,50,30000,1, RIMI,this);
        Card* Card_Arisa = new Card(":/Card_Arisa.png", ":/Arisa_Battling.png", Board, 100, 7000, 2, ARISA, this);
        Card* Card_Tomoe = new Card(":/Card_Tomoe.png", ":/Tomoe_Battling.png", Board, 50, 30000, 3, TOMOE, this);
        Card* Card_Himari = new Card(":/Card_Himari.png", ":/Himari_Battling.png", Board, 75, 15000, 4, HIMARI, this);
        Card* Card_Aya = new Card(":/Card_Aya.png", ":/Aya_Battling.png", Board, 25, 20000, 5, AYA, this);
        Card* Card_Ran = new Card(":/Card_Ran.png", ":/Ran_Battling.png", Board, 150, 7000, 6, RAN, this);
        Card* Card_Kokoro = new Card(":/Card_Kokoro.png", ":/Kokoro_Battling1.png", Board, 250, 25000, 7, KOKORO, this);
        Card* Card_Kaoru = new Card(":/Card_Kaoru.png", ":/Kaoru_Battling", Board, 75, 25000, 8, KAORU, this);
    }
        default:
            break;
    }

    Card* Michelle_remover = new Card(":/michelle_seal.png",":/michelle_seal2.png",Board,0,0,10, MICHELLE_REMOVER, this);

    Wave = 0;

    QString str = QString("当前波数：%1/%2").arg(Wave).arg(WaveList.size());
    WaveLabel->setText(str);

    StarCounter = 1;
    WaveTimeCounter = -20;
    Timer = new QTimer(this);
    connect(Timer,&QTimer::timeout,this,[&](){
        StarCounter++;
        WaveTimeCounter++;
        MarinaiCounter++;
        if(StarCounter % 12 == 0)
            ProduceStarStone();
        if(con.MarinaiList.empty() && WaveTimeCounter > 0)
        {
            if(Wave < WaveList.size())
            {
                ProduceMarinai(Wave++);
                QString str = QString("当前波数：%1/%2").arg(Wave).arg(WaveList.size());
                WaveLabel->setText(str);
                WaveTimeCounter = 0;
            }
            else
            {
                qDebug() << "获得了胜利";
                ResLabel->setStyleSheet("Color:red;");
                ResLabel->setText("WIN!");
                ResLabel->raise();
                ResLabel->show();
                Timer->stop();
                QTimer::singleShot(5000,this,[=](){
                    emit getBack();
                });
                con.GirlsList.clear();
                con.MarinaiList.clear();
            }
        }
        else if(WaveTimeCounter >= 50 && Wave < WaveList.size())
        {
            ProduceMarinai(Wave++);
            QString str = QString("当前波数：%1/%2").arg(Wave).arg(WaveList.size());
            WaveLabel->setText(str);
            WaveTimeCounter = 0;
        }
        for(auto& cur_marinai : con.MarinaiList) //判断是否失败
        {
            if(cur_marinai->x() < 40)
            {
                qDebug() << "游戏失败";
                ResLabel->setStyleSheet("Color:black;");
                ResLabel->setText("LOSE");
                ResLabel->raise();
                ResLabel->show();
                Timer->stop();
                QTimer::singleShot(5000,this,[=](){
                    emit getBack();
                });
                con.GirlsList.clear();
                con.MarinaiList.clear();
                break;
            }
        }
    });
    Timer->start(1000);
}

void BattleScene::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter ScenePainter(this);
    QString bg_path = QString(":/battle_%1.png").arg(StageIndex + 1);
    QPixmap pix(bg_path);
    ScenePainter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/StarStone1.png");
    ScenePainter.drawPixmap(0,0,80,80,pix);
}

void BattleScene::SetLand()
{
    QString f_path = QString("../GBP/resource/stage_%1.txt").arg(StageIndex + 1);
    QFile f_land(f_path);
    if(f_land.open(QIODevice::ReadOnly))
    {
        QTextStream s_land(&f_land);
        for(int i = 0; i < LAND_Y; ++i)
        {
            for(int j = 0; j < LAND_X ; ++j)
            {
                s_land >> land_type[i][j];
                Land* land = new Land(j, i, land_type[i][j], this);
            }
        }
        f_land.close();
    }
}


//wavelist格式：每行第一个数字表示怪物种类，后每两个数字表示怪物类型和数量
void BattleScene::SetWave()
{
    QString f_path = QString("../GBP/resource/wavelist_%1.txt").arg(StageIndex + 1);
    QFile f_wave(f_path);
    if(f_wave.open(QIODevice::ReadOnly))
    {
        QTextStream s_wave(&f_wave);
        int size, type, num;
        while(!s_wave.atEnd())
        {
            s_wave >> size;
            //qDebug() << size;
            WaveInfo cur_wave;
            cur_wave.resize(size);
            for(int i = 0; i < size; ++i)
            {
                s_wave >> type >> num;
                //qDebug() << type << num;
                cur_wave[i] = ProduceMarinaiInfo(type, num);
            }
            WaveList.push_back(cur_wave);
        }
        f_wave.close();
    }
}

void BattleScene::ProduceMarinai(int wave)
{
    int i = 0;
    for(auto& info: WaveList[wave])
    {
        QTimer::singleShot(1000 * i++, this, [=](){
            switch (info._type)
            {
            case NORMAL_MARINAI:
            {
                PRODUCE_MARINAI(NormalMarinai)
                break;
            }
            case WHEEL_MARINAI:
            {
                PRODUCE_MARINAI(WheelMarinai)
                break;
            }
            case HELMET_MARINAI:
            {
                PRODUCE_MARINAI(HelmetMarinai)
                break;
            }
            case MICHELLE_STATUE:
            {
                PRODUCE_MARINAI(Michelle_Statue)
                break;
            }
            case NORMAL_FLYMARINAI:
            {
                PRODUCE_MARINAI(Normal_FlyMarinai)
                break;
            }
            case OBSTACLE_FLYMARINAI:
            {
                PRODUCE_MARINAI(Obstacle_FlyMarinai)
                break;
            }
            case CART_MARINAI:
            {
                PRODUCE_MARINAI(Cart_Marinai)
                break;
            }
            case PIN_MARINAI:
            {
                PRODUCE_MARINAI(Pin_Marinai)
                break;
            }
            case BOOST_MARINAI:
            {
                PRODUCE_MARINAI(Boost_Marinai)
                break;
            }
            default:
                break;
            }
        });

    }
}

void BattleScene::ProduceStarStone()
{
    StarStone* Stone = new StarStone(Board);
    Stone->setParent(this);
    Stone->move(rand() % 300 + 200, rand() % 50 - 100);
    Stone->show();
    Stone->autoProduce();
}
