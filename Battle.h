#pragma once

#include "Enemies\Enemy.h"
#include "Enemies\fighter.h"
#include "Enemies\healer.h"
#include "Enemies\freezer.h"
#include "Castle\Castle.h"
#include "Generic_DS\Queue.h"
#include "Generic_DS/Priority_Queue.h"
#include "Generic_DS/ArrayStack.h"
#include "GUI\GUI.h"
#include <fstream>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include "MyHash.h"
#include "SuperSoldier.h"

// it is the controller of the project
class Battle
{
private:
	GUI* pGUI =nullptr;
	Castle BCastle;
	int EnemyCount=0;	//the actual number of enemies in the game
	int KilledFighters=0, KilledHealers=0, KilledFreezers=0;
	int FrostedFighters=0, FrostedHealers=0, FrostedFreezers=0;
	int ActiveFighters=0, ActiveHealers=0, ActiveFreezers=0;
	int InactiveCount=0, ActiveCount=0, FrostedCount=0, KilledCount=0;
	int CurrentTimeStep=0;
	int k=0;


	Queue<Enemy*> Q_Inactive;		//Queue of inactive enemies
	Priority_Queue<fighter*> active_fighter;   // Priority Queue of active fighter
	ArrayStack<healer*> active_healer;       //stack of active healer
	Queue<freezer*> active_freezer;     //Queue of active freezer
	Queue<Enemy*> Dead_enem;            //Queue of dead enemies
	Priority_Queue<Enemy*> FrostedList;
	Queue<SuperSoldier*> SS;


public:
	
	Battle();
    Castle * GetCastle();
    string CastleFrost();

    void AddAllListsToDrawingList();

	void RunSimulation();
    void InteractiveMode();
    void StepByStepMode();
    void SilentMode();
    void Printinfo();
    void ExtractInput(const string& filename);
    void CreateOutPut(GAME_STATE state, const string& filename);

    void ActivateEnemies();
	void AddToEnemyList(Enemy* Ptr, bool unFrosting);
    void AddFTRtoEnemyList(fighter* Ptr);
    void AddFZRtoEnemyList(freezer* Ptr);
    void AddHLRtoEnemyList(healer* Ptr);

    void UpdateEnemies();
    void FrostEnemy(Enemy* Ptr);
    void unFrostEnemy(Enemy* Ptr);
    bool KillFighter(fighter* pE);
    bool KillHealer(healer* pE);
    bool KillFreezer(freezer* pE);
    bool KillFrosted();


};

