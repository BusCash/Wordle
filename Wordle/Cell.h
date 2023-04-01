#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <fstream>

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

struct Board_1
{
	int x, y;   // Coord of the topleft corner of the cell
	int ci, cj; // Order of the cell
	int cx, cy; // Coord of the char
	char c = ' ';

	bool isStopped = false;
	bool isSelected = false;
	bool isValid = true;
	bool isHint = false;

	void drawBackgroundCell(char bg[][41]);

	void drawCell();
	void deleteCell(int color);

	void drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2);
};

struct Player
{
	string name;
	string id;

	int point = 0;
	int hint = 0;
	int streak = 0;

	bool isNew = true;
	bool isPlaying = false;

	Board_1** board;
};

struct Position
{
	int x, y;
};

void getBackground(char bg[][41], string filein);