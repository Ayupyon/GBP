#ifndef MYBTN_H
#define MYBTN_H

#include <QPushButton>

class MyBtn : public QPushButton
{
    Q_OBJECT
public:
    MyBtn(QString InitPic);
    void JumpDown();
    void JumpUp();
    //int index;

signals:

};

#endif // MYBTN_H
