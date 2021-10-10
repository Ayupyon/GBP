#include "StartScene.h"
#include "Control.h"

#include <QApplication>

Control con;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
