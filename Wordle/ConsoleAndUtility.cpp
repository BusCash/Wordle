#include "ConsoleAndUtility.h"

void gotoxy(int x, int y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	cursorPos.X = x;
	cursorPos.Y = y;

	// Set position of cursor
	SetConsoleCursorPosition(console, cursorPos);
}

void setWindowSizeAndPos()
{
	HWND console = GetForegroundWindow();
	RECT rectWindow, rectClient;

	// Get the center position
	GetClientRect(console, &rectClient);
	GetWindowRect(console, &rectWindow);

	int xPos = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
	int yPos = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

	// Set the position and size for the window
	MoveWindow(console, xPos, yPos, windowWidth, windowHeight, TRUE);
}

void setCursor(int mode)
{
	// Set cursor invisible 0: on, 1: off
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = mode;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void generateWindow()
{
	setWindowSizeAndPos();
	SetConsoleTitleW(L"Wordle");
	setCursor(0);
}

void setColor(int color)
{
	// Set the color for the place: background_color * 16 + text_color
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, color);
}

void drawGraph(int delayTime)
{
	system("cls");
	setColor(14);

	// Draw the top, bottom edge
	for (int i = 0; i < gameWidth; i++)
	{
		gotoxy(i, 0);
		cout << char(219);
		gotoxy(gameWidth - i - 1, gameHeight - 1);
		cout << char(219);
		Sleep(delayTime);
	}

	// Draw the left, right edge
	for (int i = 1; i < gameHeight; i++)
	{
		gotoxy(gameWidth - 1, i);
		cout << char(219);
		gotoxy(0, gameHeight - i);
		cout << char(219);
		Sleep(delayTime);
	}
}

void drawTitle(int delaytime)
{
	// Print the title
	setColor(14);
	int x = gameWidth / 4 - 15;
	int y = gameHeight / 4;
	Sleep(delaytime);
	gotoxy(x, y);
	cout << "~77:   .77!   :7777777.  :77777777!   ~7777777     !77.        :777777777?^";
	Sleep(delaytime);
	gotoxy(x, y + 1);
	cout << "P@@! . .&@&..5#@?!7!Y@G? 7@@B!7!!B@P~ 5@@5!!5&G7. .#@@^        ~@@#";
	Sleep(delaytime);
	gotoxy(x, y + 2);
	cout << "P@@J7&Y7&@#..&@&.   !@@P 7@@P   ~G@@7 5@@7   :&@#: #@&^        ~@@B!!!!!~~~";
	Sleep(delaytime);
	gotoxy(x, y + 3);
	cout << "P@@@@&@@@@#..&@&.   !@@P 7@@#Y5G@577: 5@@7   :&@&: #@&:        ~@@B77777!!!";
	Sleep(delaytime);
	gotoxy(x, y + 4);
	cout << "P@@B5:?B@@&..5#@7~!~J@BJ 7@@G:5#@&G~. 5@@5~~5&G?. .#@@?~!!!!!~ ~@@B";
	Sleep(delaytime);
	gotoxy(x, y + 5);
	cout << "!??:   .??7.  ^???????.  ^?!!  .???J^ ~???????     7?????????7 :?????????J^";
	Sleep(delaytime);
}

int getConsoleInput()
{
	int key = _getch();
	if (key == 0 || key == 224) // If arrows keyboard hit
	{
		key = _getch();
		if (key == UP)
		{
			playSound(0);
			return 1;
		}
		else if (key == DOWN)
		{
			playSound(0);
			return 2;
		}
		else if (key == LEFT)
		{
			playSound(0);
			return 3;
		}
		else if (key == RIGHT)
		{
			playSound(0);
			return 4;
		}

	}
	else
	{
		if (key == ENTER || key == SPACEBAR)
		{
			playSound(1);
			return 5;
		}
		else if (key == 104) // H key
			return 6;
		else if (key == ESC)
			return 7;
	}
	return -1;
}

void changeBarStatus(int barX, string barY, int moveY, string s, int bColor, int tColor)
{
	int numY;
	int numPos = 0;
	string name;
	int namePos;

	// Set the color of the bar
	setColor(bColor * 16 + tColor);

	// Loop through each y-position in the barY string
	while (numPos != -1)
	{
		// Get the next y-position in the barY string
		numPos = barY.find(',');
		numY = stoi(barY.substr(0, (numPos == -1) ? barY.length() : numPos));

		// Get the next string in the s string
		namePos = s.find(',');
		name = s.substr(0, (namePos == -1) ? s.length() : namePos);

		// If the current y-position is the one to move, update the content of the bar
		if (moveY == numY)
		{
			gotoxy(barX, numY);
			cout << "                        ";
			gotoxy(barX + 12 - name.length() / 2, numY);
			cout << name;
		}

		// If there are more y-positions or strings, remove the processed part from the input strings
		if (numPos > 0)
			barY.erase(0, numPos + 1);
		if (namePos > 0)
			s.erase(0, namePos + 1);
	}

	setColor(7);
}

int generateMenu(int barX, int barY, string sbarY, string barName, int barNum)
{
	int moveY = barY, oldY = barY;

	for (int i = barY; i <= barY + 2 * (barNum - 1); i += 2)
		changeBarStatus(barX, sbarY, i, barName, 0, 15);

	bool check = true;
	while (true)
	{
		if (check == true)
		{
			// Set the old selected bar to default
			changeBarStatus(barX, sbarY, oldY, barName, 0, 15);
			oldY = moveY;

			// Highlight the selected bar
			changeBarStatus(barX, sbarY, moveY, barName, 6, 13);
			check = false;
		}

		switch (getConsoleInput())
		{
		case 1: // UP
		{
			check = true;
			if (moveY != barY)
				moveY -= 2;
			else
				moveY = barY + 2 * (barNum - 1);
			break;
		}
		case 2: // DOWN
		{
			check = true;
			if (moveY != barY + 2 * (barNum - 1))
				moveY += 2;
			else
				moveY = barY;
			break;
		}
		case 5: // SPACEBAR or ENTER
		{
			for (int i = barY; i <= barY + 2 * (barNum - 1); i += 2)
				changeBarStatus(barX, sbarY, i, "", 0, 0);

			if (moveY == barY + 2 * (barNum - 1)) // If the last is selected
				return 0;
			else if (moveY == barY) // If the first is selected
				return 1;
			else if (barNum > 3 && moveY == barY + 2 * (barNum - 3)) // If the second is selected
				return 2;
			else if (barNum > 2 && moveY == barY + 2 * (barNum - 2)) // If the third (if exist) is selected
				return 3;
		}
		default:
			break;
		}
	}
}

void clearConsole()
{
	setColor(7);
	for (int i = 1; i < gameHeight - 1; i++)
	{
		for (int j = 1; j < gameWidth - 1; j++)
		{
			gotoxy(j, i);
			cout << " ";
		}
	}
}

void showCredits()
{
	string logo[]{

	" /$$      /$$  /$$$$$$  /$$$$$$$  /$$$$$$$  /$$       /$$$$$$$$",
	"| $$  /$ | $$ /$$__  $$| $$__  $$| $$__  $$| $$      | $$_____/ ",
	"| $$ /$$$| $$| $$  ` $$| $$  ` $$| $$  ` $$| $$      | $$",
	"| $$/$$ $$ $$| $$  | $$| $$$$$$$/| $$  | $$| $$      | $$$$$",
	"| $$$$_  $$$$| $$  | $$| $$__  $$| $$  | $$| $$      | $$__/",
	"| $$$/ `  $$$| $$  | $$| $$  ` $$| $$  | $$| $$      | $$",
	"| $$/   `  $$|  $$$$$$/| $$  | $$| $$$$$$$/| $$$$$$$$| $$$$$$$$",
	"|__/     `__/ `______/ |__/  |__/|_______/ |________/|________/",

	};
	for (int i = 0; i < 8; i++)
	{
		gotoxy(midWidth - 31, midHeight - 10 + i);
		cout << logo[i];
	}
	gotoxy(midWidth - 9, midHeight + 1);
	cout << "THANKS FOR PLAYING";
	gotoxy(midWidth - 13, midHeight + 6);
	cout << "22127126 - Nguyen Duy Hoang";
	gotoxy(midWidth - 12, midHeight + 7);
	cout << "22127405 - Tran Minh Thu";
	gotoxy(midWidth - 7, midHeight + 8);
	cout << "Class: 22CLC08";
	gotoxy(midWidth - 23, midHeight + 9);
	cout << "Instructors: Bui Huy Thong - Tran Thi Thao Nhi";
	setColor(109);
	gotoxy(midWidth - 12, midHeight + 15);
	cout << "          BACK          ";
	setColor(7);
}

void getBackground(char bg[][65], int m, int n, string filein)
{
	ifstream file;
	file.open(filein, ios::in);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			bg[i][j] = file.get();
		file.ignore();
	}
	file.close();
}

void showParameter(Player* p, string mode)
{
	int point, streak, hint;
	if (mode == "easy")
	{
		point = p->easy.point;
		streak = p->easy.streak;
		hint = p->easy.hint;
	}
	else
	{
		point = p->hard.point;
		streak = p->hard.streak;
		hint = p->hard.hint;
	}

	// Show current score
	setColor(10);
	gotoxy(3, 2);
	cout << "SCORE: ";
	cout << point;

	// Show streak -> change color depend on streak series
	gotoxy(midWidth - 5, 2);
	if (streak < 5)
		setColor(7);
	else if (streak < 8)
		setColor(14);
	else if (streak < 10)
		setColor(6);
	else if (streak < 13)
		setColor(12);
	else
		setColor(4);

	if (streak == 0)
		cout << "          ";
	else
	{
		cout << "STREAK: ";
		cout << streak;
	}

	// Show number of hints left
	setColor(13);
	gotoxy(gameWidth - 12 - 3, 2);
	cout << "HINT(H): ";
	cout << hint;

	setColor(7);
}

void playSound(int i)
{
	const wchar_t* soundfile[10] = { L"sound\\move.wav", L"sound\\enter.wav", L"sound\\hint.wav", L"sound\\error.wav", L"sound\\wrong.wav", L"sound\\streak1.wav", L"sound\\streak2.wav", L"sound\\streak3.wav", L"sound\\streak4.wav", L"sound\\streak5.wav" };
	PlaySoundW(soundfile[i], NULL, SND_FILENAME | SND_ASYNC);
}


void intro()
{
	// Define the animation frames
	string frames[] = {
		"_,------, ",
		"_|  /``_/`",
		"~|_( o .o)" ,
		" '~'~'~'~'"
	};

	// Define the logo
	string logo[] = {
	 " _      __  ____    ___    ___    __    ____",
	 "| | /| / / / __ |  / _ |  / _ |  / /   / __/",
	 "| |/ |/ / / /_/ / / , _/ / // / / /__ / _/  ",
	 "|__/|__/  |____/ /_/|_| /____/ /____//___/  "
	};
	PlaySoundW(L"sound\\intro.wav", NULL, SND_FILENAME | SND_ASYNC);

	// Loop over the animation frames
	for (int i = 0; i < gameWidth - 11 + 34; i++)
	{
		// Output the frame
		if (i < gameWidth - 11 + 9)
			for (int j = 0; j < 4; j++)
			{
				if (j == 0)
					setColor(12 * 16);
				else if (j == 1)
					setColor(14 * 16);
				else if (j == 2)
					setColor(10 * 16);
				else
					setColor(9 * 16);
				if (i < 10)
					for (int k = i; k >= 0; k--)
					{
						gotoxy(1 + k, midHeight + j);
						cout << frames[j][9 - (i - k)];
					}
				else
				{
					gotoxy(1 + i - 9, midHeight + j);
					cout << frames[j];
				}
			}

		// Effect
		if (i > midWidth - 17)
		{
			int r;
			for (int j = 0; j < 4; j++)
			{
				setColor(7);
				r = rand() % 3;
				gotoxy(1 + i - midWidth + 16 + r, midHeight + j);
				cout << " ";
			}
		}

		// Delete frame
		if (i > midWidth - 11)
		{
			for (int j = 0; j < 4; j++)
			{
				setColor(7);
				gotoxy(1 + i - midWidth + 10, midHeight + j);
				cout << " ";
			}
		}
		Sleep(100);
	}
	clearConsole();

	// Display logo at the end
	setColor(14);
	for (int j = 0; j < 4; j++)
	{
		gotoxy(midWidth - 22, midHeight + j);
		cout << logo[j];
	}
	Sleep(5000);
}