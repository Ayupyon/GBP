#ifndef CARD_H
#define CARD_H
#include "baseobject.h"
#include "starboard.h"

#define KASUMI 0
#define ARISA 1
#define RIMI 2
#define SAYA 3
#define OTAE 4
#define RAN 5
#define MOCA 6
#define HIMARI 7
#define TOMOE 8
#define TSUGU 9
#define AYA 10
#define KOKORO 15
#define KAORU 16

#define MICHELLE_REMOVER 26

class Card : public BaseObject
{
    typedef bool (Card::*func)(int, int, int);
public:
    Card(QString path,QString pressedPath,StarBoard* board,int cost,int coolDown,int index, int type, QWidget* parent);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    QString Path;
    QString PressedPath;
    StarBoard* Board;
    int Cost;
    int CoolDown;
    int Index;
    int _card_type;
    int Counter;
    QTimer* Timer = nullptr;

    bool set_kasumi(int _X, int _Y, int type);
    bool set_arisa(int _X, int _Y, int type);
    bool set_rimi(int _X, int _Y, int type);
    bool set_saya(int _X, int _Y, int type);
    bool set_otae(int _X, int _Y, int type);
    bool set_ran(int _X, int _Y, int type);
    bool set_moca(int _X, int _Y, int type);
    bool set_himari(int _X, int _Y, int type);
    bool set_tomoe(int _X, int _Y, int type);
    bool set_tsugu(int _X, int _Y, int type);
    bool set_aya(int _X, int _Y, int type);
    bool set_kokoro(int _X, int _Y, int type);
    bool set_kaoru(int _X, int _Y, int type);
    func set_card[25] = {&Card::set_kasumi, &Card::set_arisa, &Card::set_rimi, &Card::set_saya, &Card::set_otae,
                         &Card::set_ran, &Card::set_moca, &Card::set_himari, &Card::set_tomoe, &Card::set_tsugu,
                        &Card::set_aya, nullptr, nullptr, nullptr, nullptr,
                        &Card::set_kokoro, &Card::set_kaoru};
};

#endif // CARD_H
