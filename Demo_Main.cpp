
#include "Battle.h"
#include "GUI\GUI.h"
#include <fstream>
int main()
{

    Battle* pGameBattle = new Battle;
    pGameBattle->RunSimulation();

    delete pGameBattle;

    return 0;
//ofstream myfile("henn.txt");

}