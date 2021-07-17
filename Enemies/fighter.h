#pragma once
#include "Enemy.h"
class fighter :
    public Enemy
{
public:
    fighter(int id, int arrTime, double hp, double pw, int rp, int sp, int d= MaxDistance): Enemy(id, arrTime, hp, pw, rp, sp, d)
 {}

    ENMY_TYPE GetType() const override
    {
     return FIGHTER;
    }

    double Act()
    {
        curRP = RP;
        return GetPower()/ Distance;
    }

//    double priority()
//    {
//        return (double) Power*GetHealth()/GetDistance();
//    }

        int priority()
    {
        return (Power*Health*SP)/RP;
    }
};

