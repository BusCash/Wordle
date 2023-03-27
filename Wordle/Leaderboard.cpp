#pragma once
#include "generateConsole.h"
#include "Leaderboard.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

bool compareScore(Record a, Record b)
{
	if (a.score < b.score)
		return true;
	return false;
}

void getInfoPlayer(Record player[], int &n)
{
	n = 0;
	int y = midHeight;
	int lines = 5;
	fstream fs("leaderboard.txt", ios::in);

	while (!fs.eof()) {
		getline(fs, player[n].playerName);
		getline(fs, player[n].level);
		fs >> player[n].score;
		fs.ignore();
		n++;
	}
	fs.close();
}

void printLeaderboard()
{
	int n = 0;
	int y = midHeight;
	Record player[100];
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
		cout << player[i - 1].playerName;
		gotoxy(midWidth, y);
		cout << player[i - 1].level;
		gotoxy(midWidth + 10, y);
		cout << player[i - 1].score;
		y += 2;
	}
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