#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <fstream>

#define boardEasyHeight 6
#define boardEasyWidth 9
#define easyHeight 4
#define easyWidth 7
#define boardHardHeight 8
#define boardHardWidth 13
#define hardHeight 6
#define hardWidth 11
#define cellHeight 3
#define cellWidth 6

#define PADDING 500
#define NAMESIZE 50
#define PASSSIZE 50
#define BOARDSIZE 999
#define URLSIZE 100

using namespace std;

struct Time
{
	int min, sec;
	bool isFinish = false;
};

struct Board_1
{
	int x = 0, y = 0;   // Coord of the topleft corner of the cell
	int ci = 0, cj = 0; // Order of the cell
	int cx = 0, cy = 0; // Coord of the char
	char c = ' ';

	bool isStopped = false;
	bool isSelected = false;
	bool isValid = true;
	bool isHint = false;

	// Draw background when a cell is deleted
	void drawBackgroundCell(char bg[][65]);

	// Adjust a cell status
	void drawCell();

	// Delete cell and arrow
	void deleteCell(int color);

	// Draw arrow when match
	void drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2);
};

struct Board_2
{
	int x = 0, y = 0;   // Coord of the topleft corner of the cell
	int ci = 0, cj = 0; // Order of the cell
	int cx = 0, cy = 0; // Coord of the char
	char c = ' ';

	bool isStopped = false;
	bool isSelected = false;
	bool isValid = true;
	bool isHint = false;

	void drawBackgroundCell(char bg[][65]);

	void drawCell();
	void deleteCell(int color);

	void drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2);

	Board_2* next;
};

struct Parameter
{
	int point = 0;
	int maxpoint = 0;
	int hint = 0;
	int streak = 0;

	bool isPlaying = false;
	bool isFinised = false;
};

struct Player
{
	char name[NAMESIZE] = "";
	char id[PASSSIZE] = "";

	Parameter easy;
	Parameter hard;

	Board_1** eboard = NULL;
	Board_2** hboard = NULL;

	Player* next = NULL;
};

struct Position
{
	int x, y;
};