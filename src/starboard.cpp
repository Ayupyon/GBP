#include "starboard.h"
#include "starstone.h"
#include <QPalette>

StarBoard::StarBoard()
{
    QPixmap pix(":/ShowStarStone.png");
    setFixedSize(80,80);
    setScaledContents(true);
    setPixmap(pix);
    move(0,80);

    numLabel = new QLabel;
    numLabel->setParent(this);
    numLabel->setFixedSize(40,30);
    QFont font;
    //font.setFamily("华文彩云");
    font.setPixelSize(20);
    numLabel->setFont(font);
    //setPalette(QPalette(QColor(255,0,0)));
    //numLabel->setTextFormat()
    // numLabel->setText(QString::number(StarNum));
    numLabel->setNum(StarNum);
    numLabel->move(20,30);
    numLabel->setAlignment(Qt::AlignCenter);
    numLabel->show();
}

void StarBoard::StarReduce(int num)
{
    StarNum -= num;
    numLabel->setNum(StarNum);
}
