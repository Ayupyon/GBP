#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include <QWidget>
#include <QTimer>
#include <baseobject.h>
#include "starboard.h"

class BattleScene : public QWidget
{
    Q_OBJECT
public:
//    explicit BattleScene(QWidget *parent = nullptr);
    BattleScene(int index);
    void paintEvent(QPaintEvent* event);
    void ProduceMarinai();
    void ProduceStarStone();
    int StageIndex;
    int Wave;
    int CurWaveNum;
    int LeftMarinai;
    int StarCounter;
    int WaveTimeCounter;
    int MarinaiCounter;
    QLabel* ResLabel = nullptr;
    QLabel* WaveLabel = nullptr;
    StarBoard* Board;
    static QVector<QVector<int>> WaveList;
    //QList<BaseObject*> ObjectList;
    QTimer* Timer = nullptr;

signals:
    void getBack();

};

#endif // BATTLESCENE_H
