#include "generateConsole.h"
#include "EasyMode.h"
#include "PlayerInfo.h"

int main()
{
    generateWindow();
    generateGraphic();
    Player p;

    switch (generateMenu())
    {
    case 0:
        break;
    case 1:
    {
        clearConsole();
        switch (showPlayMenu())
        {
        case 0:
            break;
        case 1:
            clearConsole(); 
            p = getPlayerInfoEffect();
            easyMode(p);
            break;
        case 2: 
            break;
        }
        break;
    }
    case 2:
        break;
    case 3:
        break;
    }
    _getch();
    return 0;
}
