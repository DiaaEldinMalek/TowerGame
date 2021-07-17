#include "Enemy.h"



Enemy::Enemy(int id, int arrTime, double hp, double pw, int rp, int sp, int d)
        :ID(id),ArrivalTime(arrTime), Health(hp),Power(pw), RP(rp), SP(sp)
{
    curHP=Health;
}


Enemy::~Enemy()
{
}

int Enemy::GetID() const
{
	return ID;
}

void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}

ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}

int Enemy::GetSpeed() const
{
    if(curHP < Health/2)
        return round((SP/2) * (5-ice)/5);
    else
        return SP;
}

void Enemy::DecrementDist()
{
    if (Distance > MinDistance)
    {
        Distance -= GetSpeed();
    }
    if (Distance <MinDistance)
        Distance = 2;
}

void Enemy::Reload()
{
    curRP > 0 ? curRP-- : false;
}

bool Enemy::isFrosted()
{
    return status == FRST;
}

bool Enemy::deFrosted()
{
    return FrostTime ==1 ? true: false;
}

void Enemy::GradualDefrost()
{
    if (FrostTime>0)
        FrostTime--;
    if (FrostTime == 0 && status == FRST)
        status = ACTV;
    if (ice>0)
        ice = floor(ice - ice/2);
    else
        ice=0;
}
void Enemy::Move()
{
    if (GetStatus()==ACTV)
    {
        DecrementDist();
        Reload();
    }
    GradualDefrost();
}

int Enemy::GetDistance() const
{
	return Distance;
}

int Enemy::GetArrvTime() const
{
	return ArrivalTime;
}

double Enemy::GetPower() const
{
    if (curHP *2< Health)
        return Power*0.5;
    else return Power;
}

double Enemy::GetMaxHealth() const
{
    return Health;
}

double Enemy::GetHealth() const
{
    return curHP;
}

double Enemy::GetHealthLost() const
{
    return Health- curHP;
}

int Enemy::GetDirection() const
{
    return dir;
}

bool Enemy::CanAct() const
{
    return (status == ACTV && !curRP);
}

bool Enemy::isShot() const
{
    if (FirstShotTime==-1)
        return false;
    else return true;
}

void Enemy::SetFirstShot_Time(int timestep)
{
    FirstShotTime= timestep;
}

void Enemy::SetKillTime(int timestep)
{
    KilledTime=timestep;
}

double Enemy::Act()
{
    curRP = RP;
    return GetPower();
}

void Enemy::AbsorbHeal(double healing)
{
    curHP += healing*(GetHealthLost()/GetMaxHealth());
    if (curHP > Health)
        curHP = Health;
}

void Enemy::AbsorbDamage(double damage)
{
    curHP -= (double) damage/Distance;
    if (curHP < 0)
        curHP = 0;
}

void Enemy::AbsorbIce()
{
    if (status == FRST)
        return;
    ice = ice+ 1;
    if (ice >= 5)
    {
        ice =5;
        status = FRST;
        FrostTime = Distance%4 + 3;
    }
}


int Enemy::GetFSD() const
{
    return FirstShotTime-ArrivalTime;
}

int Enemy::GetKD() const
{
    return KilledTime-FirstShotTime;
}

int Enemy::GetLT() const
{
    return KilledTime-ArrivalTime;
}

string Enemy::GetOPLine(int timestep)
{
    string f;
    if (timestep ==-1)
        f= to_string(KilledTime) + "     " + to_string(ID) + "     " + to_string(GetFSD()) + "     " + to_string(GetKD()) + "     " + to_string(GetLT()) + "\n";
        else if (isShot())
            f =  "--     " + to_string(ID) + "     " + to_string(GetFSD()) + "     -- " + "     " + to_string(timestep-ArrivalTime) + "\n";
        else
        f =  "--     " + to_string(ID) + "     " + to_string(timestep-ArrivalTime) + "     -- " + "     " + to_string(timestep-ArrivalTime) + "\n";
    return f;
}

Enemy::Enemy(double HP, double Power, int RP, int SP, int dir, int distance) : ID(88), ArrivalTime(66)
{
    Health=HP;
    this->Power = Power;
}
