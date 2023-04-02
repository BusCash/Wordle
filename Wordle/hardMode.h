#pragma once
#include "Console.h"
#include "Easymode.h"

void addTail(Board_2*& head, Board_2* newnode);

// Find the node in pos [i][j]
Board_2* findNode(Board_2** board, int i, int j);

// Create board
void generateBoard(Board_2** board);

// Delete board
void deleteBoard(Board_2** board);

// Show the board on screen
void displayBoard(Board_2** board, int delaytime);

bool checkRowMatch(Board_2** board, int j1, int j2, int i);						// |
bool checkColMatch(Board_2** board, int i1, int i2, int j);						// |
bool checkIMatch(Board_2** board, int i1, int j1, int i2, int j2, int type);	// |
bool checkLMatch(Board_2** board, int i1, int j1, int i2, int j2, int type);	// |-> Check 2 points matching
bool checkZMatch(Board_2** board, int i1, int j1, int i2, int j2, int type);	// |
bool checkUMatch(Board_2** board, int i1, int j1, int i2, int j2, int type);	// |
bool checkMatch(Board_2** board, int i1, int j1, int i2, int j2, int type);		// |

// Move the cell to the deleted pos
void moveCell(Board_2** board, int i, int j);

// Check if board is completable
bool checkValidBoard(Board_2** board);

// Hint
void showMoveSuggestion(Board_2** cell, int i, int j);

// Reset if board is uncompletable
void resetPlayingBoard(Board_2** board);

// Handle the 2 selected cells
int processSelectedHardCell(Player p, int i, int j, int iselected, int jselected, int& deletedCount);

// Handle the action of player
bool processAction(Board_2** cell, Player& p);

// Generate all functions in hardmode
void hardMode(Player& p);