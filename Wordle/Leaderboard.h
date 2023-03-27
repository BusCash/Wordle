#pragma once
#include "generateConsole.h"

struct Record {
	string playerName;
	string level;
	int score;
};
void getInfoPlayer(Record player[], int &n);
bool compareScore(Record a, Record b);
void showLeaderboard();
void printLeaderboard();
