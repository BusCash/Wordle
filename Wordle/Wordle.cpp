#include "generateConsole.h"
#include "EasyMode.h"
#include "PlayerInfo.h"
#include "Leaderboard.h"

int main()
{
    generateWindow();
    generateGraphic();

    switch (generateMenu())
    {
    case 0:
        break;
    case 1:
    {
        clearConsole();
        Player p;
        switch (showPlayMenu())
        {
        case 0:
            break;
        case 1:
            clearConsole();                       
            p = getPlayerInfoEffect();
            easyMode(p);
        case 2: 
            break;
        }
        break;
    }
    case 2:
    {
        Record player[100];
        clearConsole();
        showLeaderboard();
        //printLeaderboard();
        break;
    }
    case 3:
        clearConsole();
        showCredit();
        int key = _getch();
        if (key == ENTER)
        break;
    }
    //cout << "hello0";
    _getch();
    return 0;
}
