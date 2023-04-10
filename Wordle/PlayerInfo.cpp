#include "PlayerInfo.h"

void addPlayer(Player*& list, Player* p)
{
	if (list == NULL)
		list = p;
	else
	{
		Player* curnode = list;
		while (curnode->next != NULL)
			curnode = curnode->next;
		curnode->next = p;
	}
}

void deleteList(Player*& list)
{
	for (Player* curnode = list; list != NULL; curnode = list)
	{
		list = list->next;
		delete curnode;
		curnode = NULL;
	}
}

void readPlayerFile(Player*& list)
{
	ifstream file("player\\playerinfo.bin", ios::binary | ios::in);
	if (file.is_open())
	{
		char name[NAMESIZE];
		while (file.read((char*)&name, NAMESIZE))
		{
			Player* p = new Player;
			strcpy(p->name, name);
			file.read((char*)&p->id, PASSSIZE);
			file.read((char*)&p->easy.maxpoint, 4);
			file.read((char*)&p->hard.maxpoint, 4);
			addPlayer(list, p);
		}
	}
	file.close();
}

void updatePlayerFile(Player*& list)
{
	ofstream file("player\\playerinfo.bin", ios::binary | ios::out | ios::trunc);
	Player* curnode = list;
	while (curnode != NULL)
	{
		file.write((char*)&curnode->name, NAMESIZE);
		file.write((char*)&curnode->id, PASSSIZE);
		file.write((char*)&curnode->easy.maxpoint, 4);
		file.write((char*)&curnode->hard.maxpoint, 4);
		curnode = curnode->next;
	}
	file.close();
}

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
		case 0: // I DONT WANT TO PLAY -> go back
			clearConsole();
			setColor(4);
			gotoxy(midWidth - 11, midHeight + 2);
			cout << "PLAY AT LEAST 1 OR DIE";
			Sleep(1000);
			break;
		case 1: // YES -> return true
			clearConsole();
			return true;
		case 3: // NO -> return false
			clearConsole();
			return false;
		}
	}
}

Player* signIn(Player*& list)
{
	Player* p = NULL;
	while (true)
	{
		// Check if player is new or not
		bool isNew = checkNewPlayer();
		if (!isNew) // If not new -> ask for id
		{
			string id = "";
			setColor(11);
			gotoxy(midWidth - 8, midHeight + 2);
			cout << "WHAT IS YOUR ID:";

			gotoxy(midWidth - 4, midHeight + 3);
			setCursor(1);
			cin >> id;
			setCursor(0);

			clearConsole();
			isNew = true;

			// Find the given id in the list
			if (list != NULL)
			{
				Player* curnode = list;
				while (curnode != NULL)
				{
					if (id == string(curnode->id))
					{
						p = curnode;
						isNew = false;
						break;
					}
					curnode = curnode->next;
				}
			}

			if (isNew) // If not found -> go back
			{
				setColor(4);
				gotoxy(midWidth - 10, midHeight + 2);
				cout << "YOU ARE NOT A MASTER";
				Sleep(1000);
			}
			else	   // If found -> play
			{
				setColor(4);
				gotoxy(midWidth - 11, midHeight + 2);
				Sleep(1000);
				showWordDisplayEffect("WELCOME BACK, " + string(p->name));
				Sleep(1000);
				clearConsole();
				break;
			}
		}
		else		   // If new -> register new
		{
			p = new Player;
			bool exist = true;
			while (exist)
			{
				exist = false;
				setColor(11);
				gotoxy(midWidth - 15, midHeight + 2);
				cout << "WHAT DO YOU WANT TO BE CALLED:";

				gotoxy(midWidth - 4, midHeight + 3);
				setCursor(1);
				cin >> p->name;
				setCursor(0);

				gotoxy(midWidth - 11, midHeight + 5);
				cout << "AN ID TO REGCONIZE YOU:";

				gotoxy(midWidth - 4, midHeight + 6);
				setCursor(1);
				cin >> p->id;
				setCursor(0);

				if (list != NULL)
				{
					Player* curnode = list;
					while (curnode != NULL)
					{
						if (string(p->id) == string(curnode->id))
						{
							clearConsole();
							setColor(12);
							gotoxy(midWidth - 10, midHeight + 2);
							cout << "THIS ID HAD BEEN USED";
							gotoxy(midWidth - 7, midHeight + 3);
							cout << "ENTER A NEW ONE";
							Sleep(1000);
							clearConsole();
							exist = true;
							break;
						}
						curnode = curnode->next;
					}
				}
			}

			clearConsole();
			setColor(11);
			gotoxy(midWidth - 7, midHeight + 2);
			Sleep(1000);
			showWordDisplayEffect("HELLO " + string(p->name));

			clearConsole();
			setColor(11);
			gotoxy(midWidth - 5, midHeight + 2);
			Sleep(1000);
			showWordDisplayEffect("LETS PLAY!");
			clearConsole();
			drawTitle(0);

			setColor(7);

			addPlayer(list, p);
			break;
		}
	}
	return p;
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

Player* sortRank(Player* list, string mode)
{
	// Sort the list of players based on mode and score
	// Sort using Bubble Sort
	Player* end, * prevnode, * curnode, * nextnode, * temp;
	if (mode == "easy")
	{
		for (end = NULL; end != list->next; end = curnode)
		{
			for (prevnode = curnode = list; curnode->next != end; prevnode = curnode, curnode = curnode->next)
			{
				nextnode = curnode->next;
				if (curnode->easy.maxpoint < nextnode->easy.maxpoint)
				{
					curnode->next = nextnode->next;
					nextnode->next = curnode;
					if (curnode != list)
						prevnode->next = nextnode;
					else
						list = nextnode;
					temp = curnode;
					curnode = nextnode;
					nextnode = curnode;
				}
			}
		}
	}
	else if (mode == "hard")
	{
		for (end = NULL; end != list->next; end = curnode)
		{
			for (prevnode = curnode = list; curnode->next != end; prevnode = curnode, curnode = curnode->next)
			{
				nextnode = curnode->next;
				if (curnode->hard.maxpoint < nextnode->hard.maxpoint)
				{
					curnode->next = nextnode->next;
					nextnode->next = curnode;
					if (curnode != list)
						prevnode->next = nextnode;
					else
						list = nextnode;
					temp = curnode;
					curnode = nextnode;
					nextnode = curnode;
				}
			}
		}
	}
	return list;
}

void showRank(Player* list, string mode)
{
	if (mode == "easy")
	{
		if (list != NULL)
		{
			int max = 20;
			int top3 = 3;
			int i = 1;
			for (Player* curnode = list; curnode != NULL && max > 0; curnode = curnode->next)
			{
				if (top3 == 3)
					setColor(6);
				else if (top3 == 2)
					setColor(4);
				else if (top3 == 1)
					setColor(15);
				else setColor(8);
				gotoxy(7, 5 + i);
				cout << curnode->name;
				gotoxy(midWidth / 2 + 10, 5 + i);
				cout << curnode->easy.maxpoint;
				top3--;
				i++;
				max--;
			}
		}
	}
	else if (mode == "hard")
	{
		if (list != NULL)
		{
			int max = 20;
			int top3 = 3;
			int i = 1;
			for (Player* curnode = list; curnode != NULL && max > 0; curnode = curnode->next)
			{
				if (top3 == 3)
					setColor(6);
				else if (top3 == 2)
					setColor(4);
				else if (top3 == 1)
					setColor(15);
				else setColor(8);
				gotoxy(midWidth + 8, 5 + i);
				cout << curnode->name;
				gotoxy(midWidth + midWidth / 2 + 10, 5 + i);
				cout << curnode->hard.maxpoint;
				top3--;
				i++;
				max--;
			}
		}
	}

}

void showLeaderboard(Player* list)
{
	gotoxy(midWidth / 2 - 1, 3);
	setColor(11);
	cout << "EASY";
	gotoxy(midWidth + midWidth / 2 - 3, 3);
	setColor(12);
	cout << "HARDCORE";

	setColor(14);
	for (int i = 2; i <= gameWidth - 3; i++)
	{
		gotoxy(i, 5);
		cout << char(205);
		gotoxy(i, gameHeight - 8);
		cout << char(205);
	}
	for (int i = 2; i <= gameHeight - 8; i++)
	{
		gotoxy(midWidth, i);
		cout << char(206);
	}

	showRank(sortRank(list, "easy"), "easy");
	showRank(sortRank(list, "hard"), "hard");

	setColor(109);
	gotoxy(midWidth - 12, midHeight + 15);
	cout << "          BACK          ";
	setColor(7);
}
