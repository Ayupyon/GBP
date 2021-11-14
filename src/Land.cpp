#include "Land.h"

QVector<QString> land_src = {":/land_pic.png", "", "", ":/ppp_label.png", ":/ag_label.png", ":/pp_label.png", ":/hhw_label.png", ":/r_label.png"};
Land::Land(int x, int y, int type, QWidget* parent):_loc_x(x), _loc_y(y), _type(type)
{
    this->setParent(parent);
    setPixmap(QPixmap(land_src[_type]));
    setFixedSize(LAND_WIDTH, LAND_WIDTH);
    setScaledContents(true);
    move(START_X + _loc_x * LAND_WIDTH, START_Y + _loc_y * LAND_WIDTH);
    this->show();
}
