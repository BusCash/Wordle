#include "PlayerInfo.h"

bool checkNewPlayer()
{
	while (true)
	{
		clearConsole();
		setColor(11);
		gotoxy(midWidth - 10, midHeight + 2);
		cout << "ARE YOU NEW PLAYER ?";
		switch (generateMenu(midWidth - 12, midHeight + 7, "22,24,26", "YES,NO I'M MASTER,I DON'T WANT TO PLAY ANYMORE", 3))
		{
		case 0:
			clearConsole();
			setColor(4);
			gotoxy(midWidth - 11, midHeight + 2);
			cout << "PLAY AT LEAST 1 OR DIE";
			Sleep(1000);
			break;
		case 1:
			clearConsole();
			return true;
		case 3:
			clearConsole();
			return false;
		}
	}
}

void showWordDisplayEffect(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		cout << s[i];
		playSound(2);
		Sleep(100);
	}
}

//void readPlayerInfo(Player player[], int& n)
//{
//	n = -1;
//	int y = midHeight;
//	int lines = 5;
//	fstream fs("playerinfo.txt", ios::in);
//
//	while (fs.peek() != fs.eof())
//	{
//		n++;
//		getline(fs, player[n].name);
//		getline(fs, player[n].id);
//		fs >> player[n].point;
//		fs.ignore();
//	}
//	fs.close();
//}

Player getPlayerInfo(bool newbie)
{
	Player p;

	if (!newbie)
	{
		setColor(11);
		gotoxy(midWidth - 8, midHeight + 2);
		cout << "WHAT IS YOUR ID:";

		gotoxy(midWidth - 4, midHeight + 3);
		setCursor(1);
		cin >> p.id;
		setCursor(0);

		clearConsole();
	}
	else
	{
		setColor(11);
		gotoxy(midWidth - 15, midHeight + 2);
		cout << "WHAT DO YOU WANT TO BE CALLED:";

		gotoxy(midWidth - 4, midHeight + 3);
		setCursor(1);
		cin >> p.name;
		setCursor(0);

		gotoxy(midWidth - 11, midHeight + 5);
		cout << "AN ID TO REGCONIZE YOU:";

		gotoxy(midWidth - 4, midHeight + 6);
		setCursor(1);
		cin >> p.id;
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
		drawTitle();
	}
	setColor(7);
	return p;
}

void processPlayerInfo(Player& p, Player player[], int n)
{
	bool newbie = checkNewPlayer();
	if (!newbie)
		while (!newbie)
		{
			p = getPlayerInfo(newbie);

			bool check = true;
			for (int i = 0; i < n + 1; i++)
			{
				if (p.name == player[i].name && p.id == player[i].id)
				{
					p = player[i];
					check = false;
				}
			}

			newbie = check;

			if (newbie)
			{
				setColor(4);
				gotoxy(midWidth - 10, midHeight + 2);
				cout << "YOU ARE NOT A MASTER";
				Sleep(1000);
				newbie = checkNewPlayer();
			}
			else
			{
				setColor(4);
				gotoxy(midWidth - 11, midHeight + 2);
				cout << "WELCOME BACK, " << p.name;
				Sleep(1000);
				break;
			}
		}
	else
		p = getPlayerInfo(newbie);
}

Player signIn()
{
	Player p;
	Player list[100];
	int playercount = 0;
	//readPlayerInfo(list, playercount);
	processPlayerInfo(p, list, playercount);
	return p;
}

bool compareScore(Player a, Player b, string mode)
{
	int apoint, bpoint;
	if (mode == "easy")
	{
		apoint = a.easy.point;
		bpoint = b.easy.point;
	}
	else
	{
		apoint = a.hard.point;
		bpoint = b.hard.point;
	}

	if (apoint < bpoint)
		return true;
	return false;
}

//void saveRecord(Player player[], int n)
//{
//	ofstream ofs("playerinfo.txt", ios::app);
//	for (int i = 0; i < n; ++i)
//	{
//		ofs << player[i].name << " " << player[i].id << " " << player[i].point << endl;
//	}
//	ofs.close();
//}

//void printLeaderboard()
//{
//	int n = 0;
//	int y = midHeight;
//	Player player[100];
//	readPlayerInfo(player, n);
//	int lines = 5;
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = i + 1; j < n; j++)
//		{
//			if (compareScore(player[i], player[j]))
//			{
//				swap(player[i], player[j]);
//			}
//		}
//	}
//	for (int i = 1; i < lines; i++)
//	{
//		gotoxy(midWidth - 10, y);
//		cout << player[i - 1].name;
//		gotoxy(midWidth, y);
//		cout << player[i - 1].id;
//		gotoxy(midWidth + 10, y);
//		cout << player[i - 1].point;
//		y += 2;
//	}
//	saveRecord(player, n);
//}

void showLeaderboard()
{
	gotoxy(midWidth - 11, midHeight - 11);
	cout << "       LEADERBOARD       ";
	setColor(109);
	gotoxy(midWidth - 9, midHeight + 15);
	cout << "          BACK          ";
	while (true)
	{
		switch (getConsoleInput())
		{
		case 5:
			return;
		default:
			break;
		}
	}
}

// de tam ben day

void Background1()
{
	string s;
	ifstream ifs;
	ifs.open("bulbasaur.txt");
	while (!ifs.eof())
	{
		getline(ifs, s);
	}
	cout << s;
}

void Background2()
{
	string s;
	ifstream ifs;
	ifs.open("squirle.txt");
	while (!ifs.eof())
	{
		getline(ifs, s);
	}
	cout << s;
}