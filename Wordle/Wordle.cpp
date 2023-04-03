#include "ConsoleAndUtility.h"
#include "PlayerInfo.h"
#include "EasyMode.h"
#include "HardMode.h"
#include "Hack.h"

int main()
{
	generateWindow();
	drawGraph(5);
	Player p = signIn();
	bool quit = false;
	while (!quit)
	{
		drawTitle();
		switch (generateMenu(midWidth - 12, midHeight + 6, "21,23,25,27", "PLAY,LEADERBOARD,CREDITS,QUIT", 4))
		{
		case 0:
			if (p.easy.isPlaying || p.hard.isPlaying)
			{
				setColor(12);
				gotoxy(midWidth - 25, midHeight + 2);
				cout << "YOU STILL HAVE NOT COMPLETED THE CURRENT STAGE GAME";
				gotoxy(midWidth - 17, midHeight + 3);
				cout << "QUIT GAME WILL NOT SAVE YOUR STAGE";
				switch (generateMenu(midWidth - 12, midHeight + 6, "21,23", "QUIT,BACK", 2))
				{
				case 0:
					quit = true;
					deleteBoard(p.eboard);
					break;
				case 1:
					break;
				}
			}
			else
				quit = true;
			break;
		case 1:
		{
			switch (generateMenu(midWidth - 12, midHeight + 7, "22,24,26", "EASY,HARDCORE,BACK", 3))
			{
			case 0:
				break;
			case 1:
				clearConsole();
				easyMode(p);
				break;
			case 3:
				clearConsole();
				hardMode(p);
				break;
			}
			break;
		}
		case 2:
			break;
		case 3:
			bool credits = true;
			clearConsole();
			while (credits)
			{
				showCredits();
				switch (getConsoleInput())
				{
				case 5:
					credits = false;
					clearConsole();
					break;
				default:
					break;
				}
			}
		}
	}
	return 0;
}
