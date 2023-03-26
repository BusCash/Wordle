#include "generateConsole.h"
#include "EasyMode.h"
#include "PlayerInfo.h"

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
        Player p = getPlayerInfoEffect();
        clearConsole();
        switch (showPlayMenu())
        {
        case 0:
            break;
        case 1:
            clearConsole();
            easyMode(p);
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
