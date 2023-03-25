#include "PlayerInfo.h"

void showWordDisplayEffect(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        cout << s[i];
        Sleep(100);
    }
}

Player getPlayerInfoEffect()
{
    Player p;

    setColor(11);
    gotoxy(midWidth - 15, midHeight + 2);
    cout << "WHAT DO YOU WANT TO BE CALLED:";

    gotoxy(midWidth - 4, midHeight + 3);
    setCursor(1);
    cin >> p.name;
    setCursor(0);
    
    clearConsole();
    setColor(11);
    gotoxy(midWidth - 7, midHeight + 2);
    Sleep(1000);
    showWordDisplayEffect("HELLO " + p.name);

    clearConsole();
    setColor(11);
    Sleep(1000);
    gotoxy(midWidth - 5, midHeight + 2);
    showWordDisplayEffect("LETS PLAY!");
    clearConsole();

    return p;
}