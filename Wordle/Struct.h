#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

// Header guard to prevent multiple inclusions of the same header file
#ifndef STRUCT_H
#define STRUCT_H

// Declaration of external global variables
extern int
easyHeight,
easyWidth,
hardHeight,
hardWidth;
extern int
boardEasyHeight,
boardEasyWidth,
boardHardHeight,
boardHardWidth;

#endif // !STRUCT_H

#define cellHeight 3
#define cellWidth 6
#define NAMESIZE 50
#define PASSSIZE 50

using namespace std;

// A struct of X and Y coordiates 
struct Position
{
	int x, y;
};

// A struct of the easy board
struct Board_1
{
	Position cell;				// Coord of the topleft corner of the cell
	Position character;			// Coord of the char
	char c = ' ';				// The character of a cell

	bool isStopped = false;		// |
	bool isSelected = false;	// |-> Status of a cell in board
	bool isValid = true;		// |
	bool isHint = false;		// |

	// Draw background when a cell is deleted
	void drawBackgroundCell(char bg[][65]);

	// Adjust a cell status
	void drawCell();

	// Delete cell and arrow
	void deleteCell(int color);

	// Draw arrow when match
	void drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2);
};

// A struct of the hard board
struct Board_2
{
	Position cell;				// Coord of the topleft corner of the cell
	Position character;			// Coord of the char
	char c = ' ';				// The character of a cell

	bool isStopped = false;		// |
	bool isSelected = false;	// |-> Status of a cell in board
	bool isValid = true;		// |
	bool isHint = false;		// |

	// Draw background when a cell is deleted
	void drawBackgroundCell(char bg[][65]);

	// Adjust a cell status
	void drawCell();

	// Delete cell and arrow
	void deleteCell(int color);

	// Draw arrow when match
	void drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2);

	Board_2* next; // Next cell
};

// A struct of game parameters
struct Parameter
{
	int point = 0;				// The current point
	int maxpoint = 0;			// The highest point
	int hint = 0;				// The number of hints left
	int streak = 0;				// The streak

	bool isPlaying = false;		// |-> Status of the board
	bool isFinised = false;		// | 
};

// A struct for holding player information
struct Player
{
	char name[NAMESIZE] = "";	// Player name
	char id[PASSSIZE] = "";		// Player id

	// The information and status of a specific mode board of a player
	Parameter easy;
	Parameter hard;
	Board_1** eboard = NULL;
	Board_2** hboard = NULL;

	Player* next = NULL;		// Next player
};
