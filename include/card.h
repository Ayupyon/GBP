#ifndef CARD_H
#define CARD_H
#include "baseobject.h"
#include "starboard.h"

class Card : public BaseObject
{
public:
    Card(QString path,QString pressedPath,StarBoard* board,int cost,int coolDown,int index);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    QString Path;
    QString PressedPath;
    static QVector<QString> GirlsPixPath;
    StarBoard* Board;
    int Cost;
    int CoolDown;
    int Index;
    int Counter;
    QTimer* Timer = nullptr;
};

#endif // CARD_H
