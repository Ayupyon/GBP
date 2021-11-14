#ifndef RAN_H
#define RAN_H

#include "basegirls.h"
#include "starboard.h"
#include "battlescene.h"

/*
 * 兰：
 * 功能：发射boostbullet，对遇到的第一个敌人造成较高伤害
 *      在该行没有敌人时会蓄力，蓄力一段时间后下次攻击可以发出多个子弹
 */

class Ran : public BaseGirls
{
public:
    Ran(int _X, int _Y, StarBoard*);
    void ProduceBullet(BattleScene* scene);
    bool FindMarinais();
    int _bullet_counter;
    int _prepare_counter;
};

#endif // RAN_H
