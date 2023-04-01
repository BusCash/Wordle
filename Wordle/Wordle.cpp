#include "Console.h"
#include "EasyMode.h"
#include "PlayerInfo.h"

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
