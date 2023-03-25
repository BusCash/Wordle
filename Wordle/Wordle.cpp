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
        easyMode(p);
        break;
    }
    case 2:
        break;
    case 3:
        break;
    }
    cout << "hello";
    cout << "hello";
    _getch();
    return 0;
}
