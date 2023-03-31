#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <thread>

#define boardHeight 6
#define boardWidth 9
#define easyHeight 4
#define easyWidth 7
#define cellHeight 3
#define cellWidth 6

using namespace std;

struct Time
{
	int min, sec;
	bool isFinish = false;
};

struct Player
{
	string name;
	string id;
	Time easyplaytime = { 1, 30 };
	Time hardplaytime = { 1, 30 };
};

struct Position
{
	int x, y;
};

struct Board_1
{
	int x, y;
	int ci, cj;
	char c = ' ';
	int cx, cy;

	bool isStopped = false;
	bool isSelected = false;
	bool isValid = true;
	bool isDeleted = false;
	bool isHint = false;

	void drawBackgroundCell(char bg[][41]);

	void drawCell();
	void deleteCell(int color);

	void drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2);
};