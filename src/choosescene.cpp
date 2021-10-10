#include "choosescene.h"
#include <QIcon>
#include <QPainter>
#include <QDebug>
#include <QTimer>

ChooseScene::ChooseScene(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1334/1.5,1002/1.5);
    setWindowIcon(QIcon("://Icon.png"));
    setWindowTitle("GirlBand vs Marinai");
    for(int i=0;i<5;i++)
    {
        QString str = QString(":/Stage%1").arg(i+1);
        StageBtns[i] = new MyBtn(str);
        StageBtns[i]->setParent(this);
        //StageBtns[i]->index = i+1;
        StageBtns[i]->setFixedSize(StageBtns[i]->width()*2,StageBtns[i]->height()*2);
        StageBtns[i]->setIconSize(QSize(StageBtns[i]->width(),StageBtns[i]->height()));
        StageBtns[i]->move(10+180*i,200);
        StageBtns[i]->show();

        connect(StageBtns[i],&QPushButton::clicked,[=](){
       //     qDebug() << "点击了第" << i+1 << "关";
            StageBtns[i]->JumpDown();
            StageBtns[i]->JumpUp();
            QTimer::singleShot(500,this,[=](){
                this->hide();
                Battle = new BattleScene(i);
                Battle->show();
                //Battle->ProduceMarinai();
                connect(Battle,&BattleScene::getBack,this,[&](){
                    Battle->close();
                    delete Battle;
                    this->show();
                });
            });
        });

    }
}

void ChooseScene::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter ScenePainter(this);
    QPixmap pix(":/ChoiceBG.png");
    ScenePainter.drawPixmap(0,0,this->width(),this->height(),pix);
}
