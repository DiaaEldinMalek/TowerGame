//
// Created by dia2s on 6/16/2021.
//
#include "Enemy.h"
#ifndef DEMO_MAIN_CPP_SUPERSOLDIER_H
#define DEMO_MAIN_CPP_SUPERSOLDIER_H


class SuperSoldier :
        public Enemy
        {
        private:
            int destination;
        public:
            SuperSoldier(double HP, double Power, int RP, int destination):
            Enemy(HP, Power, RP, SP=3, Distance=MinDistance)
            {
                this->destination=destination;
            }

            ENMY_TYPE GetType() const override
            {
                return SS;
            }


    void DecrementDist()
    {
        if (Distance < destination)
        {
            Distance += SP;
        }
        if (Distance >destination)
            Distance = destination;
    }

    void Reload()
    {
        curRP > 0 ? curRP-- : false;
    }
        };


#endif //DEMO_MAIN_CPP_SUPERSOLDIER_H
