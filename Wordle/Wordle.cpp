#include "ConsoleAndUtility.h"
#include "PlayerInfo.h"
#include "EasyMode.h"
#include "HardMode.h"

int main()
{
	generateWindow();
	drawGraph(5);

	Player* list = NULL;
	readPlayerFile(list);
	Player* p = signIn(list);
	Player* temp = new Player;
	bool quit = false;

	while (!quit)
	{
		drawTitle();
		updatePlayerFile(list);
		switch (generateMenu(midWidth - 12, midHeight + 6, "21,23,25,27", "PLAY,LEADERBOARD,CREDITS,QUIT", 4))
		{
		case 0: // QUIT
		{
			if (p->easy.isPlaying || p->hard.isPlaying || temp->easy.isPlaying || temp->hard.isPlaying)
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
						deleteBoard(p->eboard);
					}
					if (p->hard.isPlaying)
					{
						p->hard.isPlaying = false;
						deleteBoard(p->hboard);
					}
					if (temp->easy.isPlaying)
					{
						temp->easy.isPlaying = false;
						deleteBoard(temp->eboard);
					}
					if (temp->hard.isPlaying)
					{
						temp->hard.isPlaying = false;
						deleteBoard(temp->hboard);
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
			switch (generateMenu(midWidth - 12, midHeight + 6, "21,23,25,27", "EASY,HARDCORE,CUSTOM,BACK", 4))
			{
			case 0:
				break;
			case 1:
				clearConsole();
				easyMode(p, 4, 7);
				break;
			case 2:
				clearConsole();
				hardMode(p, 6, 11);
				break;
			case 3:
				clearConsole();
				int height, width;
				while (true)
				{
					clearConsole();
					if (temp->easy.isPlaying || temp->hard.isPlaying)
					{
						bool check = false;
						setColor(11);
						gotoxy(midWidth - 15, midHeight - 3);
						cout << "DO YOU WANT TO CREATE NEW BOARD";
						switch (generateMenu(midWidth - 12, midHeight + 6, "21,23", "YES,NO", 2))
						{
						case 0:
							check = true;
							break;
						case 1:
							if (temp->easy.isPlaying)
							{
								temp->easy.isPlaying = false;
								deleteBoard(p->eboard);
							}
							else
							{
								temp->hard.isPlaying = false;
								deleteBoard(p->hboard);
							}
							break;
						}
						if (check)
							break;
					}
					setColor(11);
					gotoxy(midWidth - 8, midHeight - 3);
					cout << "CHOOSE BOARD SIZE";
					setColor(12);
					gotoxy(midWidth - 12, midHeight + 5);
					cout << "TOTAL CELLS MUST BE EVEN";
					gotoxy(midWidth - 13, midHeight + 6);
					cout << "ROWS MUST BE SMALLER THAN 7";
					gotoxy(midWidth - 15, midHeight + 7);
					cout << "COLUMNS MUST BE SMALLER THAN 12";
					setColor(14);
					gotoxy(midWidth - 3, midHeight);
					cout << "ROWS: ";
					cin >> height;
					gotoxy(midWidth - 5, midHeight + 1);
					cout << "COLUMNS: ";
					cin >> width;
					if (height * width % 2 == 0)
						if (height < 7 && width < 12 && height > 0 && width > 0)
							break;
				}

				if (!temp->easy.isPlaying && !temp->hard.isPlaying)
				{
					clearConsole();
					switch (generateMenu(midWidth - 12, midHeight + 6, "21,23", "EASY,HARDCORE", 2))
					{
					case 0:
						clearConsole();
						hardMode(temp, height, width);
						break;
					case 1:
						clearConsole();
						easyMode(temp, height, width);
						break;
					}
				}
				else
				{
					if (temp->easy.isPlaying)
					{
						clearConsole();
						easyMode(temp, height, width);
					}
					else
					{
						clearConsole();
						hardMode(temp, height, width);
					}
				}
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

	delete temp;
	deleteList(list);
	return 0;
}
