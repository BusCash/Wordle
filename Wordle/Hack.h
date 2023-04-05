#pragma once
#include "PlayerInfo.h"

struct State
{
	int p, q;
	int p_, q_;
	char board[BOARDSIZE];
	char file_background[URLSIZE];
};

struct Date
{
	int dd, mm, yy;
};

struct Record
{
	Date date;
	int points;
};

struct savefile
{
	char mask;
	char name[NAMESIZE];
	char password[PASSSIZE];
	Record record[5];
	State state[5];
};

void loadFileHacking(string fileName, savefile& hack);
void test(savefile hack);