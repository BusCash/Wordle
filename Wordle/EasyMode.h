#pragma once
#include "ConsoleAndUtility.h"

// Create board
void generateBoard(Board_1** board, int easyHeight, int easyWidth);

// Delete board
void deleteBoard(Board_1** board, int easyHeight);

// Show the board on screen
void displayBoard(Board_1** board, int delaytime, int easyHeight, int easyWidth);

bool checkRowMatch(Board_1** board, int j1, int j2, int i);													// |
bool checkColMatch(Board_1** board, int i1, int i2, int j);													// |
bool checkIMatch(Board_1** board, int i1, int j1, int i2, int j2, int type, int easyHeight, int easyWidth);	// |
bool checkLMatch(Board_1** board, int i1, int j1, int i2, int j2, int type, int easyHeight, int easyWidth);	// |-> Check 2 points matching
bool checkZMatch(Board_1** board, int i1, int j1, int i2, int j2, int type, int easyHeight, int easyWidth);	// |
bool checkUMatch(Board_1** board, int i1, int j1, int i2, int j2, int type, int easyHeight, int easyWidth);	// |
bool checkMatch(Board_1** board, int i1, int j1, int i2, int j2, int type, int easyHeight, int easyWidth);	// |

// Check if board is completable
bool checkValidBoard(Board_1** board, int easyHeight, int easyWidth);

// Reset if board is uncompletable
void resetPlayingBoard(Board_1** board, int deletedCount, int easyHeight, int easyWidth);

// Hint
void showMoveSuggestion(Board_1** cell, int i, int j, int easyHeight, int easyWidth);

// Handle the 2 selected cells
bool processSelectedCell(Player* p, int i, int j, int iselected, int jselected, int& deletedCount, int easyHeight, int easyWidth);

// Calculate point and streak
void processPoint(Player* p);

// Handle the action of player
bool processAction(Board_1** cell, Player* p, int easyHeight, int easyWidth);

// Generate all functions in easymode
void easyMode(Player* p, int &easyHeight, int &easyWidth);