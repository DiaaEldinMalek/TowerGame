#include "Castle.h"




void Castle::SetHealth(double h)
{
    Health = h;
    currentHealth = h;
}

double Castle::GetHealth() const
{
    return currentHealth;
}
void Castle::SetNum(int n)
{
    Num = n;
}
int Castle::GetNum() const
{
    return Num;
}
void Castle::SetPower(double cp)
{
    if (cp > 0)
        CP = cp;
    else
        CP = 0;
}
double Castle::GetPower() const
{
    return CP;
}
bool Castle::isFrosted() const
{
    return Frosted;
}

void Castle::unFrost()
{
    Frosted = false;
}

void Castle::HealCastle()
{
    currentHealth += 0.03 * Health;
    if (currentHealth > Health)
        currentHealth = Health;
}

void Castle::AbsorbDamage(double damage)
{
    currentHealth -= damage;
    DamageTakenTotal += damage;
    if (currentHealth < 0)
        currentHealth = 0;
}

double Castle::GetMaxHealth() const
{
    return Health;
}

double Castle::TotalDamageTaken()
{
    return DamageTakenTotal;
}

void Castle::AbsorbIce(double damage)
{
    if (!Frosted)
        frostlevel += damage;
    if (frostlevel >= MaxFrostLevel)
    {
        Frosted=true;
        frostlevel=0;
    }
}

bool Castle::Emergency()
{
    if (waitbeforeSS >0)
    {
        waitbeforeSS--;
        return false;
    }
    else if (currentHealth < 0.3*Health)
    {
        waitbeforeSS =5;
        return true;
    }
    else return false;
}
