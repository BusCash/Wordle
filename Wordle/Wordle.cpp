#include "ConsoleAndUtility.h"
#include "PlayerInfo.h"
#include "EasyMode.h"
#include "HardMode.h"
#include "Hack.h"

int main()
{
	generateWindow();
	drawGraph(5);

	Player* list = NULL;
	readPlayerFile(list);
	Player* p = signIn(list);
	int easyHeight = 0,
		easyWidth = 0;
	int hardHeight = 0,
		hardWidth = 0;

	bool quit = false;
	while (!quit)
	{
		drawTitle();
		switch (generateMenu(midWidth - 12, midHeight + 6, "21,23,25,27", "PLAY,LEADERBOARD,CREDITS,QUIT", 4))
		{
		case 0: // QUIT
		{
			if (p->easy.isPlaying || p->hard.isPlaying)
			{
				setColor(12);
				gotoxy(midWidth - 25, midHeight + 2);
				cout << "YOU STILL HAVE NOT COMPLETED THE CURRENT STAGE GAME";
				gotoxy(midWidth - 17, midHeight + 3);
				cout << "QUIT GAME WILL NOT SAVE YOUR STAGE";
				switch (generateMenu(midWidth - 12, midHeight + 6, "21,23", "BACK,QUIT", 2))
				{
				case 0:
					quit = true;
					if (p->easy.isPlaying)
					{
						p->easy.isPlaying = false;
						deleteBoard(p->eboard, easyHeight);
					}
					if (p->hard.isPlaying)
					{
						p->hard.isPlaying = false;
						deleteBoard(p->hboard, hardHeight);
					}
					break;
				case 1:
					clearConsole();
					break;
				}
			}
			else
				quit = true;
			break;
		}
		case 1: // PLAY
		{
			switch (generateMenu(midWidth - 12, midHeight + 7, "22,24,26", "EASY,HARDCORE,BACK", 3))
			{
			case 0:
				break;
			case 1:
				clearConsole();
				easyMode(p, easyHeight, easyWidth);
				break;
			case 3:
				clearConsole();
				hardMode(p, hardHeight, hardWidth);
				break;
			}
			break;
		}
		case 2: // LEADERBOARD
		{
			Player* easy = sortRank(list, "easy");
			Player* hard = sortRank(list, "hard");
			clearConsole();
			bool ldboard = true;

			while (ldboard)
			{
				showLeaderboard(easy, hard);
				switch (getConsoleInput())
				{
				case 5:
					ldboard = false;
					clearConsole();
					break;
				default:
					break;
				}
			}
			break;
		}
		case 3: // CREDITS
		{
			clearConsole();
			bool credits = true;
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
			break;
		}
		}
	}
	updatePlayerFile(list);
	return 0;
}
