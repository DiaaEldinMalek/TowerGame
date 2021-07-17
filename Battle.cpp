#include "Battle.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
using namespace std;

Battle::Battle() :active_healer(MaxEnemyCount)
{}

Castle* Battle::GetCastle()
{
    return &BCastle;
}

string Battle::CastleFrost()
{
    string msg;
    (BCastle.isFrosted()) ? msg = "frosted" : msg = "not frosted";
    return msg;
}

void Battle::RunSimulation()
{
    pGUI = new GUI;
    PROG_MODE	mode = pGUI->getGUIMode();

    switch (mode)	//Add a function for each mode in next phases
    {
    case MODE_INTR:
        InteractiveMode();
        break;
    case MODE_STEP:
        StepByStepMode();
        break;
    case MODE_SLNT:
        SilentMode();
        break;
    }

    delete pGUI;

}

void Battle::InteractiveMode()
{
    pGUI->PrintMessage("Entered interactive mode. Please type the input file name without quotations.");
    string myfile = pGUI->GetString();
    ExtractInput(myfile);
    string out =  "Out_" + myfile;

    CurrentTimeStep = 0;
    AddAllListsToDrawingList();
    pGUI->UpdateInterface(CurrentTimeStep);
    pGUI->waitForClick();

    while (KilledCount < EnemyCount || BCastle.GetHealth() > 0)
    {
        if (KilledCount == EnemyCount && BCastle.GetHealth() > 0)
        {
            pGUI->PrintMessage("WIN!");
            CreateOutPut(WIN, out);
            Sleep(3000);
            return;
        }

        if (KilledCount < EnemyCount && BCastle.GetHealth() <= 0)
        {
            pGUI->PrintMessage("LOSS!");
            CreateOutPut(LOSE, out);
            Sleep(3000);
            return;
        }

        if (KilledCount < EnemyCount && BCastle.GetHealth() > 0)
        {
            CurrentTimeStep++;
            ActivateEnemies();
            UpdateEnemies();
            pGUI->ResetDrawingList();
            AddAllListsToDrawingList();
            pGUI->UpdateInterface(CurrentTimeStep);
            Printinfo();
            pGUI->waitForClick();
        }
    }
    pGUI->PrintMessage("Drawn!");
    CreateOutPut(DRAW, out);
    Sleep(3000);
}

void Battle::StepByStepMode()
{
    pGUI->PrintMessage("Entered step by step mode. Please type the input file name without quotations.");
    string myfile = pGUI->GetString();
    ExtractInput(myfile);
    string out =  "Out_" + myfile;

    CurrentTimeStep = 0;
    AddAllListsToDrawingList();
    pGUI->UpdateInterface(CurrentTimeStep);
    pGUI->waitForClick();

    while (KilledCount < EnemyCount || BCastle.GetHealth() > 0)
    {
        if (KilledCount == EnemyCount && BCastle.GetHealth() > 0)
        {
            pGUI->PrintMessage("WIN!");
            CreateOutPut(WIN, out);
            Sleep(3000);
            return;
        }

        if (KilledCount < EnemyCount && BCastle.GetHealth() <= 0)
        {
            pGUI->PrintMessage("LOSS!");
            CreateOutPut(LOSE, out);
            Sleep(3000);
            return;
        }

        if (KilledCount < EnemyCount && BCastle.GetHealth() > 0)
        {
            CurrentTimeStep++;
            ActivateEnemies();
            UpdateEnemies();
            pGUI->ResetDrawingList();
            AddAllListsToDrawingList();
            pGUI->UpdateInterface(CurrentTimeStep);
            Printinfo();
            Sleep(250);
        }
    }
    pGUI->PrintMessage("Drawn!");
    CreateOutPut(DRAW, out);
    Sleep(3000);
}

void Battle::SilentMode()
{
    pGUI->PrintMessage("Entered silent mode. Please type the input file name without quotations.");
    string myfile = pGUI->GetString();
    ExtractInput(myfile);
    string out =  "Out_" + myfile;

    CurrentTimeStep = 0;

    while (KilledCount < EnemyCount || BCastle.GetHealth() > 0)
    {
        if (KilledCount == EnemyCount && BCastle.GetHealth() > 0)
        {
            pGUI->PrintMessage("WIN!");
            CreateOutPut(WIN, out);
            Sleep(3000);
            return;
        }

        if (KilledCount < EnemyCount && BCastle.GetHealth() <= 0)
        {
            pGUI->PrintMessage("LOSS!");
            CreateOutPut(LOSE, out);
            Sleep(3000);
            return;
        }

        if (KilledCount < EnemyCount && BCastle.GetHealth() > 0)
        {
            CurrentTimeStep++;
            ActivateEnemies();
            UpdateEnemies();
        }
    }
    pGUI->PrintMessage("Drawn!");
    CreateOutPut(DRAW, out);
    Sleep(3000);
}

void Battle::Printinfo()
{
    string msg1, msg2, msg3, msg4;
    msg1 = "Current time step is " + to_string(CurrentTimeStep) +
        " , Castle is " + CastleFrost() + " with health " + to_string(BCastle.GetHealth());

    msg2 = "Number of active enemies is " + to_string(ActiveCount) +
        " --- Active Fighters: " + to_string(ActiveFighters) +
        " --- Active Healers: " + to_string(ActiveHealers) +
        " --- Active Freezers:  " + to_string(ActiveFreezers) + ")";

    msg3 = "Number of frosted enemies is " + to_string(FrostedCount) +
        " --- Frosted Fighters: " + to_string(FrostedFighters) +
        " --- Frosted Healers: " + to_string(FrostedHealers) +
        " --- Frosted Freezers:  " + to_string(FrostedFreezers) + ")";

    msg4 = "Number of killed enemies is " + to_string(KilledCount) +
        " --- Killed Fighters: " + to_string(KilledFighters) +
        " --- Killed Healers: " + to_string(KilledHealers) +
        " --- Killed Freezers:  " + to_string(KilledFreezers) + ")";
    pGUI->PrintMessage(msg1, msg2, msg3, msg4);
}

void Battle::ExtractInput(const string& filename)
{
    double CastleHP;
    double CastlePW;
    int CastleGuns;
    int EnemyNum;

    ifstream myfile(filename); //File should be in cmake-build-debug
    myfile >> CastleHP >> CastleGuns >> CastlePW;
    myfile >> EnemyNum;
    BCastle.SetPower(CastlePW);
    BCastle.SetHealth(CastleHP);
    BCastle.SetNum(CastleGuns);
    EnemyCount = EnemyNum;
    InactiveCount=EnemyNum;


    Enemy* pE = nullptr;
    int Etype; //0 fighter, 1 healer, 2 freezer
    int ID, AT, RP, SP;
    double HP, PW;

    for (int i = 0; i < EnemyNum; ++i)
    {
        myfile >> ID >> Etype >> AT >> HP >> PW >> RP >> SP;
        switch (Etype)
        {
        case FIGHTER:
            pE = new fighter(ID, AT, HP, PW, RP, SP);
            break;
        case HEALER:
            pE = new healer(ID, AT, HP, PW, RP, SP);
            break;
        case FREEZER:
            pE = new freezer(ID, AT, HP, PW, RP, SP);
            break;
        }
        pE->SetStatus(INAC); //initial all enemies are inactive
        Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
    }
    myfile.close();
}

void Battle::CreateOutPut(GAME_STATE state, const string& filename)
{
    ofstream output;
    output.open(filename);
    int AvgFSD=0, AvgKD=0;
    switch (state)
    {
    case WIN:
        output << "Game is won.\n";
        break;
    case LOSE:
        output << "Game is lost.\n";
        break;
    case DRAW:
        output << "Game is drawn.\n";
        break;
    default:
        return;
    }
    Enemy* pE;
    fighter* fiter;
    healer* hilar;
    freezer* frizar;
    string str;
    while (Dead_enem.dequeue(pE))
    {
        str= pE->GetOPLine(-1);
        output << str;
        AvgFSD += pE->GetFSD();
        AvgKD += pE->GetKD();
    }
    while (active_fighter.dequeue(fiter))
    {
        str= fiter->GetOPLine(CurrentTimeStep);
        output << str;
    }
    while (active_healer.pop(hilar))
    {
        str= hilar->GetOPLine(CurrentTimeStep);
        output << str;
    }
    while (active_freezer.dequeue(frizar))
    {
        str= frizar->GetOPLine(CurrentTimeStep);
        output << str;
    }
    output << "Total damage taken by castle: " << BCastle.TotalDamageTaken() << "\n";
    switch (state)
    {
        case WIN:
            output << "The game is WON." << "\n";
            output << "Total number of enemies: " << EnemyCount << "\n";
            output << "Average First Shot Delay: " << (double) AvgFSD/EnemyCount << "\n" << "Average Killed Delay: " << (double) AvgKD/EnemyCount <<  "\n";
            break;
        case LOSE:
            output << "The game is WON." << "\n";
            output << "Number of killed enemies: " << KilledCount << "\n";
            output << "Active enemies: " << ActiveCount << " -- " << "Inactive enemies: " <<  InactiveCount << "\n";
            output << "Average First Shot Delay: " << (double) AvgFSD/KilledCount << "\n" << "Average Killed Delay: " << (double) AvgKD/KilledCount << "\n";
            break;
        case DRAW:
            output << "The game is DRAW." << "\n";
            output << "Number of killed enemies: " << KilledCount << "\n";
            output << "Active enemies: " << ActiveCount << " -- " << "Inactive enemies: " <<  InactiveCount << "\n";
            output << "Average First Shot Delay: " << (double) AvgFSD/KilledCount << "\n" << "Average Killed Delay: " << (double) AvgKD/KilledCount << "\n";
    }

    output.close();
}

void Battle::AddToEnemyList(Enemy* Ptr, bool unFrosting)
{
    ENMY_TYPE type = Ptr->GetType();
    switch (type)
    {
    case FIGHTER:
        AddFTRtoEnemyList(static_cast<fighter*> (Ptr));
        (unFrosting) ? FrostedFighters-- : false;
        break;
    case HEALER:
        AddHLRtoEnemyList(static_cast<healer*> (Ptr));
        (unFrosting) ? FrostedHealers-- : false;
        break;
    case FREEZER:
        AddFZRtoEnemyList(static_cast<freezer*> (Ptr));
        (unFrosting) ? FrostedFreezers-- : false;
        break;
    }
}

void Battle::AddFTRtoEnemyList(fighter* Ptr) {
    active_fighter.enqueue(Ptr, Ptr->priority());
    ActiveFighters++;
}

void Battle::AddFZRtoEnemyList(freezer* Ptr) {
    active_freezer.enqueue(Ptr);
    ActiveFreezers++;
}

void Battle::AddHLRtoEnemyList(healer* Ptr) {
    active_healer.push(Ptr);
    ActiveHealers++;
}

void Battle::AddAllListsToDrawingList()
{
    //Add inactive queue to drawing list
    int holder;
    Enemy* const* EnemyList = Q_Inactive.toArray(holder);
    for (int i = 0; i < holder; i++)
        pGUI->AddToDrawingList(EnemyList[i]);

    //Add active, frosted, dead enemies to drawing list
    fighter* const* fighterlist = active_fighter.toArray(holder);
    for (int i = 0; i < holder; i++)
        pGUI->AddToDrawingList(fighterlist[i]);

    freezer* const* freezerlist = active_freezer.toArray(holder);
    for (int i = 0; i < holder; i++)
        pGUI->AddToDrawingList(freezerlist[i]);

    healer* const* healerlist = active_healer.CopyArray(ActiveHealers+ FrostedHealers);
    for (int i = 0; i < ActiveHealers; i++)
        pGUI->AddToDrawingList(healerlist[i]);

    Enemy* const* frostlist = FrostedList.toArray(holder);
    for (int i = 0; i < holder; i++)
        pGUI->AddToDrawingList(frostlist[i]);

    Enemy* const* deadList = Dead_enem.toArray(holder);
    for (int i = 0; i < holder; i++)
        pGUI->AddToDrawingList(deadList[i]);

}

void Battle::ActivateEnemies()
{
    Enemy* pE;
    while (Q_Inactive.peekFront(pE))	//as long as there are more inactive enemies
    {
        if (pE->GetArrvTime() > CurrentTimeStep)	//no more arrivals at current time
            return;
        Q_Inactive.dequeue(pE);
        InactiveCount--;
        ActiveCount++;
        pE->SetStatus(ACTV);	//make status active
        AddToEnemyList(pE, false);
    }
}

void Battle::UpdateEnemies()
{
    MyHash* Table = new MyHash();
    int holder;
    Enemy* pE;
    fighter* fiter;
    healer* hilar;
    freezer* frizar;
    BCastle.unFrost();

    fighter** fighterlist = active_fighter.toArray(holder);
    for (int i = 0; i < ActiveFighters +FrostedFighters; i++)
    {
        pE = fighterlist[i];
        if (pE->deFrosted())
            unFrostEnemy(pE);
        pE->Move();
        Table->InsertItem(pE);
        if (pE->CanAct())
            BCastle.AbsorbDamage(pE->Act());
    }

    freezer** freezerlist = active_freezer.toArray(holder);
    for (int i = 0; i < ActiveFreezers+ FrostedFreezers; i++)
    {
        pE = freezerlist[i];
        if (pE->deFrosted())
            unFrostEnemy(pE);
        pE->Move();
        Table->InsertItem(pE);
        if (pE->CanAct() && !BCastle.isFrosted())
            BCastle.AbsorbIce(pE->Act());
    }

    Enemy* injured;
    int diff = 1;
    healer** healerlist = active_healer.CopyArray(ActiveHealers+ FrostedHealers);
    for (int i = 0; i < ActiveHealers + FrostedHealers; i++)
    {
        injured = nullptr;
        pE = healerlist[i];
        if (pE->deFrosted())
            unFrostEnemy(pE);
        pE->Move();
        Table->InsertItem(pE);
        if (pE->CanAct())
        {
            if (Table->InjuredEnemy(pE, injured, diff))
            {
                if (injured != nullptr)
                {
                    double healing = (double)pE->Act() / diff;
                    injured->AbsorbHeal(healing);
                }
            }
        }
    }

    if (BCastle.Emergency())
    {
        int dest= Table->Density();
        SuperSoldier* superSoldier = new SuperSoldier(200,20,4, dest);
        SS.enqueue(superSoldier);
    }


    int count = 0;
    int seed = 0;
    bool enter = !BCastle.isFrosted();
    if (enter)
        while (count < BCastle.GetNum() && ActiveFighters + FrostedFighters > 0)
        {
            active_fighter.peekFront(fiter);
            seed++;
            srand(seed); // Initialize random number generator.
            int ran = (rand() % 10) + 1;
            if (ran <= 8)
            {
                if (!fiter->isShot())
                {
                    fiter->SetFirstShot_Time(CurrentTimeStep);
                }
                double damage = BCastle.GetPower();
                fiter->AbsorbDamage(damage);
                count++;
                if (fiter->GetHealth() == 0)
                {
                    fiter->SetKillTime(CurrentTimeStep);
                    KillFighter(fiter);
                }
            }
            else
            {
                if (!fiter->isFrosted())
                {
                    fiter->AbsorbIce();
                    count++;
                    if (fiter->isFrosted())
                        FrostEnemy(fiter);
                }
            }
        }
    if (enter)
        while (count < BCastle.GetNum() && ActiveHealers +FrostedHealers > 0)
        {
            active_healer.peek(hilar);
            seed++;
            srand(seed); // Initialize random number generator.
            int ran = (rand() % 10) + 1;
            if (ran <= 8)
            {
                if (!hilar->isShot())
                {
                    hilar->SetFirstShot_Time(CurrentTimeStep);
                }
                double damage = BCastle.GetPower();
                hilar->AbsorbDamage(damage);
                count++;
                if (hilar->GetHealth() == 0)
                {
                    hilar->SetKillTime(CurrentTimeStep);
                    KillHealer(hilar);
                }
            }
            else
            {
                if (!hilar->isFrosted())
                {
                    hilar->AbsorbIce();
                    count++;
                    if (hilar->isFrosted())
                        FrostEnemy(hilar);
                }

            }
        }
    if (enter)
        while (count < BCastle.GetNum() && ActiveFreezers + FrostedFreezers > 0)
        {
            active_freezer.peekFront(frizar);
            seed++;
            srand(seed); // Initialize random number generator.
            int ran = (rand() % 10) + 1;
            if (ran <= 8)
            {
                if (!frizar->isShot())
                {
                    frizar->SetFirstShot_Time(CurrentTimeStep);
                }
                double damage = BCastle.GetPower();
                frizar->AbsorbDamage(damage);
                count++;
                if (frizar->GetHealth() == 0)
                {
                    frizar->SetKillTime(CurrentTimeStep);
                    KillFreezer(frizar);
                }
            }
            else
            {
                if (!frizar->isFrosted())
                {
                    frizar->AbsorbIce();
                    count++;
                    if (frizar->isFrosted())
                        FrostEnemy(frizar);
                }
            }
        }
    Table->clearHash();
    delete Table;
}
        

bool Battle::KillFighter(fighter* pE)
{
    if (active_fighter.dequeue(pE))
    {
        if (pE->GetStatus()==FRST)
        {
            FrostedCount--;
            FrostedFighters--;
        }
        else if (pE->GetStatus()==ACTV)
        {
            ActiveFighters--;
            ActiveCount--;
        }
        pE->SetStatus(KILD);
        Dead_enem.enqueue(pE);
        KilledCount++;
        KilledFighters++;
        return true;
    }
    return false;
}

bool Battle::KillHealer(healer* pE)
{

    if (active_healer.pop(pE))
    {
        if (pE->GetStatus()==FRST)
        {
            FrostedCount--;
            FrostedHealers--;
        }
        else if (pE->GetStatus()==ACTV)
        {
            ActiveHealers--;
            ActiveCount--;
        }
        pE->SetStatus(KILD);
        Dead_enem.enqueue(pE);
        KilledCount++;
        KilledHealers++;
        BCastle.HealCastle();
        return true;
    }
    return false;
}

bool Battle::KillFreezer(freezer* pE)
{

    if (active_freezer.dequeue(pE))
    {
        if (pE->GetStatus()==FRST)
        {
            FrostedCount--;
            FrostedFreezers--;
        }
        else if (pE->GetStatus()==ACTV)
        {
            ActiveFreezers--;
            ActiveCount--;
        }
        pE->SetStatus(KILD);
        Dead_enem.enqueue(pE);
        KilledCount++;
        KilledFreezers++;
        return true;
    }
    return false;
}

void Battle::FrostEnemy(Enemy* pE)
{
    FrostedCount++;
    ActiveCount--;
    switch (pE->GetType())
    {
    case FIGHTER:
        ActiveFighters--;
        FrostedFighters++;
        break;
    case HEALER:
        ActiveHealers--;
        FrostedHealers++;
        break;
    case FREEZER:
        ActiveFreezers--;
        FrostedFreezers++;
    }
}

void Battle::unFrostEnemy(Enemy* Ptr)
{
    FrostedCount--;
    ActiveCount++;
    switch (Ptr->GetType())
    {
        case FIGHTER:
            ActiveFighters++;
            FrostedFighters--;
            break;
        case HEALER:
            ActiveHealers++;
            FrostedHealers--;
            break;
        case FREEZER:
            ActiveFreezers++;
            FrostedFreezers--;
    }
}