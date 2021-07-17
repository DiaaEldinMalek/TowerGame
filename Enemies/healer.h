#pragma once
#include "Enemy.h"
class healer :
        public Enemy
        {
        public:
            healer(int id, int arrTime, double hp, double pw, int rp, int sp, int d= MaxDistance): Enemy(id, arrTime, hp, pw, rp, sp, d)
            {}
            ENMY_TYPE GetType() const override
            {
                return HEALER;
            }
            void DecrementDist() override
            {
                if (GetStatus()==ACTV)
                {
                    Distance -= GetSpeed()*dir;
                }
                if (Distance <MinDistance)
                {
                    Distance = 2;
                    dir =-1;
                }
                if (Distance > MaxDistance)
                {
                    Distance = MaxDistance;
                    dir =1;
                }
            }


            void AbsorbDamage(double damage)
            {
                curHP -= (double) damage/(Distance*2);
                if (curHP < 0)
                    curHP = 0;
            }
        };

