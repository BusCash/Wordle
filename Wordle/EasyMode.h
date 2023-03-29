#pragma once
#include "generateConsole.h"

void generateBoard(Board_1** board);
void deleteBoard(Board_1** board);
void displayBoard(Board_1** board);
bool checkRowMatch(Board_1** board, int j1, int j2, int i);
bool checkColMatch(Board_1** board, int i1, int i2, int j);
bool checkIMatch(Board_1** board, int i1, int j1, int i2, int j2);
bool checkLMatch(Board_1** board, int i1, int j1, int i2, int j2);
bool checkZMatch(Board_1** board, int i1, int j1, int i2, int j2);
bool checkUMatch(Board_1** board, int i1, int j1, int i2, int j2);
bool checkMatch(Board_1** board, int i1, int j1, int i2, int j2);
void processSelectedCell(Board_1** cell, int i, int j, int iselected, int jselected, int& selectedCount);
void processAction(Board_1** cell);
void easyMode(Player& p);