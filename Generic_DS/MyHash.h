//
// Created by dia2s on 6/11/2021.
//
#include "Enemy.h"

struct Cell
{
private:
    Enemy* Enem=nullptr;
    Cell* next=nullptr;
public:
    Cell(){}

    int ChainSize()
    {
        if (next==nullptr)
            return 1;
        return 1+next->ChainSize();
    }
    Cell(Enemy*& enem)
    {
        Enem= enem;
    }
    void Append(Cell* ptrToNext)
    {
        if (next == nullptr)
        {
            next = ptrToNext;
            return;
        }
        else next->Append(ptrToNext);
    }
    bool FindInjured(Enemy* healer, Enemy* &injured)
    {
        if (Enem->GetHealthLost()>0 && healer != Enem)
        {
            injured = Enem;
            return true;
        }
        else if (next==nullptr)
            return false;
        else
            return next->FindInjured(healer, injured);
    }
    void Destruct()
    {
        if (next)
            next->Destruct();
        delete this;
        return;
    }
    void PrintCells()
    {
        cout << Enem->GetDistance() << endl;
        if (next)
            next->PrintCells();
    }
};

#ifndef DEMO_MAIN_CPP_MYHASH_H
#define DEMO_MAIN_CPP_MYHASH_H


class MyHash {
private:
    Cell** MyTable;
    int size=59;
public:
    MyHash()
    {
        MyTable = new Cell*[size];
        for (int i = 0; i < size; ++i)
        {
            MyTable[i]=nullptr;
        }
    }

    void InsertItem(Enemy*& enem)
    {
        if (enem->GetStatus() != ACTV)
            return;
        int key = enem->GetDistance()-2;
        Cell* newCell = new Cell(enem);
        if (MyTable[key] == nullptr)
            MyTable[key]=newCell;
        else MyTable[key]->Append(newCell);
    }

    bool InjuredEnemy(Enemy* healer, Enemy* &injured, int distdiff) //This function gives the first injured enemy
    {
        int key = healer->GetDistance()-2;
        int dir = healer->GetDirection();
        if (MyTable[key]->FindInjured(healer, injured))
        {
            distdiff= 1;
            return true;
        }
        ;
        if (key-dir >=0 && key-dir < size && MyTable[key-dir]!= nullptr)
        {
            if(MyTable[key-dir]->FindInjured(healer, injured))
            {
                distdiff= 2;
                return true;
            }
        }
        if (key- 2*dir >=0 && key- 2*dir <size && MyTable[key- 2*dir] !=nullptr)
        {
            if(MyTable[key- 2*dir]->FindInjured(healer, injured))
            {
                distdiff= 3;
                return true;
            }
        }
        return false;
    }

    void clearHash()
    {
        for (int i = 0; i < size; ++i)
        {
            if (MyTable[i]!= nullptr)
            {
                MyTable[i]->Destruct();
                MyTable[i]=nullptr;
            }
        }
    }
    void PrintHash()
    {
        for (int i = 0; i < size; ++i)
        {
            if (MyTable[i]!=nullptr)
            {
                cout << "Index:" << i << endl;
                MyTable[i]->PrintCells();
            }
        }
        cout << "End of Hash" << endl;
    }
    int Density()
    {
        int max=0;
        int index=2;
        for (int i = 0; i < size; ++i)
        {
            if (MyTable[i]!=nullptr)
                if(MyTable[i]->ChainSize()>max)
                {
                    max = MyTable[i]->ChainSize();
                    index = i+2;
                }
        }
        return index;
    }
    ~MyHash()
    {
        clearHash();
        delete [] MyTable;
    }
};


#endif //DEMO_MAIN_CPP_MYHASH_H
