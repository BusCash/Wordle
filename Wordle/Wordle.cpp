#include "generateConsole.h"
#include "EasyMode.h"
#include "PlayerInfo.h"
#include "Leaderboard.h"

int main()
{
    generateWindow();
    generateGraphic();

    Player p;
    bool quit = false;
    while (!quit)
    {
        switch (generateMenu())
        {
        case 0:
            quit = true;
            break;
        case 1:
        {
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
    }
    return 0;
}
