#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include <QWidget>
#include <QTimer>
#include <QSet>
#include "basegirls.h"
#include "starboard.h"
#include "Land.h"

#define LAND_X 9
#define LAND_Y 5

#define NORMAL_MARINAI 1
#define WHEEL_MARINAI 2
#define HELMET_MARINAI 3
#define MICHELLE_STATUE 4
#define NORMAL_FLYMARINAI 5
#define OBSTACLE_FLYMARINAI 6
#define CART_MARINAI 7
#define PIN_MARINAI 8
#define BOOST_MARINAI 9

#define PRODUCE_MARINAI(type)   \
    for(int i = 0; i < info._num; ++i)  \
    {   \
       BaseMarinai* marinai = new type(8, rand() % 5, this); \
       marinai->show();  \
    }

class ProduceMarinaiInfo
{
public:
     ProduceMarinaiInfo():_type(0), _num(0){}
     ProduceMarinaiInfo(int type, int num):_type(type), _num(num){}
     int _type;
     int _num;
};

typedef QVector<ProduceMarinaiInfo> WaveInfo;

class BattleScene : public QWidget
{
    Q_OBJECT
public:
    BattleScene(int index);
    void paintEvent(QPaintEvent* event);
    void ProduceMarinai(int wave);
    void ProduceStarStone();
    void SetLand();
    void SetWave();
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
    QVector<WaveInfo> WaveList;
    int land_type[LAND_Y][LAND_X];
    QTimer* Timer = nullptr;

signals:
    void getBack();

};

#endif // BATTLESCENE_H
