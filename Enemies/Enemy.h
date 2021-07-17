#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
using namespace std;
class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	const int ID;           //Each enemy has a unique ID (sequence number)
	const int ArrivalTime;	   //arrival time (time it starts to join battle)
	int FirstShotTime = -1;    //The time of the first castle shot at enemy
	int KilledTime = 0;      //the time of death of enemy
	ENMY_STATUS status;	//status of the enemy (inactive, inactive, frosted, killed)
	int Distance = 60;	   //Horizontal distance between enemy & the tower of its region
	double Health;	  //Enemy health
	double curHP;   //current heath
	double Power;    //power of attack
	int RP;      //Reload period (in ms)
	int curRP = 1; //time left till full reload
	int SP;     //maximum movement speed (grid steps per time step)
	int dir = 1; //movemenet direction (1 by default, -1 if healer in reverse)
	int LifeTime;
    unsigned int ice;
    int FrostTime;

public:
	Enemy(int id, int arrTime, int d = MaxDistance);
	Enemy(double HP, double Power, int RP, int SP=3, int dir=-1, int distance =MinDistance);

	Enemy(int id, int arrTime, double hp, double pw, int rp, int sp, int d = MaxDistance);
	int GetID() const; //unused
	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS);
    virtual void Move();
	virtual void DecrementDist();
	bool isFrosted();
	bool deFrosted();
	void GradualDefrost();
	void Reload();
	int GetDistance() const;
	int GetSpeed() const; //get speed calculated according to power and frost level
	int GetArrvTime() const;
	double GetHealth() const;
	double GetMaxHealth() const;
	double GetHealthLost() const; //maxhealth - currenthealth
	int GetDirection() const;
	bool CanAct() const; //is reload period zero?
	bool isShot() const; //did he get shot before?
	void SetFirstShot_Time(int timestep);
	void AbsorbHeal(double healing);
	void AbsorbDamage(double damage);
    void AbsorbIce();
	double GetPower() const; //calculates power based on health
	void SetKillTime(int timestep);
	int GetFSD() const;
	int GetKD() const;
	int GetLT() const;
	string GetOPLine(int timestep);


	// Virtual Functions: ----------------

    virtual ~Enemy();
    virtual ENMY_TYPE GetType() const = 0;
	virtual double Act();

};
