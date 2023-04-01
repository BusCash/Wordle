#pragma once
#include "Console.h"

void generateBoard(Board_1** board);
void deleteBoard(Board_1** board);
void displayBoard(Board_1** board, int delaytime);
bool checkRowMatch(Board_1** board, int j1, int j2, int i);
bool checkColMatch(Board_1** board, int i1, int i2, int j);
bool checkIMatch(Board_1** board, int i1, int j1, int i2, int j2, int type);
bool checkLMatch(Board_1** board, int i1, int j1, int i2, int j2, int type);
bool checkZMatch(Board_1** board, int i1, int j1, int i2, int j2, int type);
bool checkUMatch(Board_1** board, int i1, int j1, int i2, int j2, int type);
bool checkMatch(Board_1** board, int i1, int j1, int i2, int j2, int type);
bool checkValidBoard(Board_1** board);
void showMoveSuggestion(Board_1** cell, int i, int j);
void resetPlayingBoard(Board_1** board, int deletedCount);
bool processSelectedCell(Board_1** cell, int i, int j, int iselected, int jselected, int& deletedCount);
bool processAction(Board_1** cell, Player& p);
void easyMode(Player& p);