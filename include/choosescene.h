#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QWidget>
#include "mybtn.h"
#include "battlescene.h"

class ChooseScene : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    BattleScene* Battle;
    MyBtn* StageBtns[5];

signals:

};

#endif // CHOOSESCENE_H
