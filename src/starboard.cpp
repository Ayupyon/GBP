#include "starboard.h"
#include "starstone.h"
#include "battlescene.h"
#include <QPalette>

StarBoard::StarBoard(QWidget* parent)
{
    QPixmap pix(":/ShowStarStone.png");
    setFixedSize(80,80);
    setScaledContents(true);
    setPixmap(pix);
    move(0,80);
    this->setParent(parent);
    numLabel = new QLabel;
    numLabel->setParent(this);
    numLabel->setFixedSize(40,30);
    QFont font;
    font.setPixelSize(20);
    numLabel->setFont(font);
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
