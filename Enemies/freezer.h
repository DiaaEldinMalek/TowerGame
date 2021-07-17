#pragma once
#include "Enemy.h"
class freezer :
    public Enemy
{
public:
    freezer(int id, int arrTime, double hp, double pw, int rp, int sp, int d= MaxDistance): Enemy(id, arrTime, hp, pw, rp, sp, d)
    {}

    ENMY_TYPE GetType() const override
    {
        return FREEZER;
    }


};

