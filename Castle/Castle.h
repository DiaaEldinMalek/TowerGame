#pragma once
#include "..\Defs.h"
#include "Queue.h"
#include "SuperSoldier.h"
class Castle
{
#define MaxFrostLevel 300

    double Health;
    double currentHealth;
    int Num; //number of enemies castle can attack at once
    double CP; //castle power
    bool Frosted = false;
    int frostlevel=0;
    double DamageTakenTotal=0;
    int waitbeforeSS;
public:
    void SetHealth(double h);
    double GetHealth() const;
    double GetMaxHealth() const;
    void SetNum(int n);
    int GetNum() const;
    void SetPower(double cp);
    double GetPower() const;
    bool isFrosted() const;
    void unFrost();
    void AbsorbDamage(double damage);
    void HealCastle();
    double TotalDamageTaken();
    void AbsorbIce(double damage);
    bool Emergency();

};

