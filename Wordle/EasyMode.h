#pragma once
#include "ConsoleAndUtility.h"

// Create board
void generateBoard(Board_1** board);

// Delete board
void deleteBoard(Board_1** board);

// Show the board on screen
void displayBoard(Board_1** board, int delaytime);

bool checkRowMatch(Board_1** board, int j1, int j2, int i);						// |
bool checkColMatch(Board_1** board, int i1, int i2, int j);						// |
bool checkIMatch(Board_1** board, int i1, int j1, int i2, int j2, int type);	// |
bool checkLMatch(Board_1** board, int i1, int j1, int i2, int j2, int type);	// |-> Check 2 points matching
bool checkZMatch(Board_1** board, int i1, int j1, int i2, int j2, int type);	// |
bool checkUMatch(Board_1** board, int i1, int j1, int i2, int j2, int type);	// |
bool checkMatch(Board_1** board, int i1, int j1, int i2, int j2, int type);		// |

// Check if board is completable
bool checkValidBoard(Board_1** board);

// Hint
void showMoveSuggestion(Board_1** cell, int i, int j);

// Reset if board is uncompletable
void resetPlayingBoard(Board_1** board, int deletedCount);

// Handle the 2 selected cells
bool processSelectedCell(Player* p, int i, int j, int iselected, int jselected, int& deletedCount);

// Calculate point and streak
void processPoint(Player* p);

// Handle the action of player
bool processAction(Board_1** cell, Player* p);

// Generate all functions in easymode
void easyMode(Player* p, int height, int width);