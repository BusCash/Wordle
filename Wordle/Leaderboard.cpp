#pragma once
#include "generateConsole.h"
#include "Leaderboard.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

bool compareScore(Player a, Player b)
{
	if (a.point < b.point)
		return true;
	return false;
}

void getInfoPlayer(Player player[], int &n)
{
	n = 0;
	int y = midHeight;
	int lines = 5;
	fstream fs("leaderboard.txt", ios::in);

	while (!fs.eof()) 
	{
		getline(fs, player[n].name);
		getline(fs, player[n].id);
		fs >> player[n].point;
		fs.ignore();
		n++;
	}
	fs.close();
}

void saveRecord(Player player[], int n)
{
	ofstream ofs ("leaderboard.txt", ios::app);
	for (int i = 0; i < n; ++i)
	{
		ofs << player[i].name << " " << player[i].id << " " << player[i].point << endl;
	}
	ofs.close();
}

void printLeaderboard()
{
	int n = 0;
	int y = midHeight;
	Player player[100];
	getInfoPlayer(player, n);
	int lines = 5;
	for (int i = 0; i < n; i++) 
	{
		for (int j = i + 1; j < n; j++) 
		{
			if (compareScore(player[i], player[j]))
			{
				swap(player[i], player[j]);
			}
		}
	}
	for (int i = 1; i < lines; i++) 
	{
		gotoxy(midWidth - 10, y);
		cout << player[i - 1].name;
		gotoxy(midWidth, y);
		cout << player[i - 1].id;
		gotoxy(midWidth + 10, y);
		cout << player[i - 1].point;
		y += 2;
	}
	saveRecord(player, n);
}

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

//de tam ben day

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