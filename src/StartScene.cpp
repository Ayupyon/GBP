#include "StartScene.h"
//#include "ui_widget.h"
#include <QPainter>
#include <QTimer>
#include "mybtn.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
//    , ui(new Ui::Widget)
{
//    ui->setupUi(this);
    setFixedSize(1334/1.5,1002/1.5);
    setWindowIcon(QIcon("://Icon.png"));
    setWindowTitle("GirlBand vs Marinai");

    chooseScene= new ChooseScene;
    MyBtn* StartBtn = new MyBtn(":/StartIcon.png");
    StartBtn->setParent(this);
    StartBtn->move(this->width()*0.5-StartBtn->width()*0.5,this->height()*0.6);
    StartBtn->show();
    connect(StartBtn,&MyBtn::clicked,[=](){
        StartBtn->JumpDown();
        StartBtn->JumpUp();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            chooseScene->show();
        });
    });
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter ScenePainter(this);
    QPixmap SceneMap;
    SceneMap.load(":/StartScene.png");
    ScenePainter.drawPixmap(0,0,this->width(),this->height(),SceneMap);
}

Widget::~Widget()
{
//    delete ui;
}

