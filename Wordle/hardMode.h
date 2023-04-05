#pragma once
#include "ConsoleAndUtility.h"

// Add node to the back of line
void addTail(Board_2*& head, Board_2* newnode);

// Find the node in pos [i][j]
Board_2* findNode(Board_2** board, int i, int j, int hardHeight, int hardWidth);

// Create board
void generateBoard(Board_2** board, int hardHeight, int hardWidth);

// Delete board
void deleteBoard(Board_2** board, int hardHeight);

// Show the board on screen
void displayBoard(Board_2** board, int delaytime, int hardHeight, int hardWidth);

bool checkRowMatch(Board_2** board, int j1, int j2, int i, int hardHeight, int hardWidth);					// |
bool checkColMatch(Board_2** board, int i1, int i2, int j, int hardHeight, int hardWidth);					// |
bool checkIMatch(Board_2** board, int i1, int j1, int i2, int j2, int type, int hardHeight, int hardWidth);	// |
bool checkLMatch(Board_2** board, int i1, int j1, int i2, int j2, int type, int hardHeight, int hardWidth);	// |-> Check 2 points matching
bool checkZMatch(Board_2** board, int i1, int j1, int i2, int j2, int type, int hardHeight, int hardWidth);	// |
bool checkUMatch(Board_2** board, int i1, int j1, int i2, int j2, int type, int hardHeight, int hardWidth);	// |
bool checkMatch(Board_2** board, int i1, int j1, int i2, int j2, int type, int hardHeight, int hardWidth);	// |

// Move the cell to the deleted pos
void moveCell(Board_2** board, int i, int j, int hardWidth);

// Check if board is completable
bool checkValidBoard(Board_2** board, int hardHeight, int hardWidth);

// Hint
void showMoveSuggestion(Board_2** cell, int i, int j, int hardHeight, int hardWidth);

// Reset if board is uncompletable
void resetPlayingBoard(Board_2** board, int hardHeight, int hardWidth);

// Handle the 2 selected cells
int processSelectedHardCell(Player* p, int i, int j, int iselected, int jselected, int& deletedCount, int hardHeight, int hardWidth);

// Calculate point and streak
void processHardPoint(Player* p);

// Handle the action of player
bool processAction(Board_2** cell, Player* p, int hardHeight, int hardWidth);

// Generate all functions in hardmode
void hardMode(Player* p, int& hardHeight, int& hardWidth);