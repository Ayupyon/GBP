#ifndef LAND_H
#define LAND_H
#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QString>

/*
 * Land（地图格子）类：基于QLabel类实现
 * _loc_x,_loc_y存储该格子的位置
 * _type存储类型：
 * NORMAL 普通地面
 * SKY 天空
 * PROHIBIT 无法种植
*/

#define NORMAL 0
#define SKY 1
#define PROHIBIT 2
#define PPP_LAND 3
#define AG_LAND 4
#define PP_LAND 5
#define HHW_LAND 6
#define R_LAND 7

#define LAND_WIDTH 90
#define START_X 80
#define START_Y 200

class Land : public QLabel
{
public:
    Land(int x, int y, int type, QWidget* parent);

    int _loc_x, _loc_y;
    int _type;
};

#endif // LAND_H
