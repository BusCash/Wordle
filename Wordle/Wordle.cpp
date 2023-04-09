#include "PlayerInfo.h"
#include "EasyMode.h"
#include "HardMode.h"

int main()
{
	// Setup window and intro
	generateWindow();
	drawGraph(10);
	intro();

	// Setup player information
	Player* list = NULL;
	readPlayerFile(list);
	Player* p = signIn(list);
	Player* temp = new Player;

	// Process the game
	bool quit = false;
	while (!quit)
	{
		drawTitle(0);
		updatePlayerFile(list);
		switch (generateMenu(midWidth - 12, midHeight + 6, "21,23,25,27", "PLAY,LEADERBOARD,CREDITS,QUIT", 4))
		{
		case 0: // QUIT -> check if there is any board not completed
		{
			if (p->easy.isPlaying || p->hard.isPlaying || temp->easy.isPlaying || temp->hard.isPlaying) // If yes -> ask for certainty
			{
				setColor(12);
				gotoxy(midWidth - 25, midHeight + 2);
				cout << "YOU STILL HAVE NOT COMPLETED THE CURRENT STAGE GAME";
				gotoxy(midWidth - 17, midHeight + 3);
				cout << "QUIT GAME WILL NOT SAVE YOUR STAGE";
				switch (generateMenu(midWidth - 12, midHeight + 6, "21,23", "BACK,QUIT", 2))
				{
				case 0: // QUIT -> delete board
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
				case 1: // BACK
					clearConsole();
					break;
				}
			}
			else // If no -> just quit
				quit = true;
			break;
		}
		case 1: // PLAY
		{
			switch (generateMenu(midWidth - 12, midHeight + 6, "21,23,25,27", "EASY,HARDCORE,CUSTOM,BACK", 4))
			{
			case 0: // BACK
				break;
			case 1: // EASY -> go to easymode
				clearConsole();
				easyMode(p, 4, 7);
				break;
			case 2: // HARDCORE -> go to hardmode
				clearConsole();
				hardMode(p, 6, 11);
				break;
			case 3: // CUSTOM -> depend on player choice
				clearConsole();
				int height, width;
				while (true)
				{
					clearConsole();
					if (temp->easy.isPlaying || temp->hard.isPlaying) // Check if there is any custom board not completed
					{
						// If yes -> ask to create new or continue
						bool check = false;
						setColor(11);
						gotoxy(midWidth - 15, midHeight - 3);
						cout << "DO YOU WANT TO CREATE NEW BOARD";
						switch (generateMenu(midWidth - 12, midHeight + 6, "21,23", "YES,NO", 2))
						{
						case 0: // NO
							check = true;
							break;
						case 1: // YES -> delete board
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

					// If there is no board not completed -> Choose size
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

				// After chose size -> check if there is any board not completed
				if (!temp->easy.isPlaying && !temp->hard.isPlaying) // If no -> choose mode
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
				else // If yes -> go straight to the current board
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
			clearConsole();
			bool ldboard = true;
			while (ldboard)
			{
				showLeaderboard(list);
				switch (getConsoleInput())
				{
				case 5: // BACK -> go back to main menu
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
				case 5: // BACK -> go back to main menu
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

	// Delete and free memory
	delete temp;
	deleteList(list);
	return 0;
}
