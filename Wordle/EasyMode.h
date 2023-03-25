#pragma once
#include "generateConsole.h"

void generateBoard(Board_1** board);
void deleteBoard(Board_1** board);
void displayBoard(Board_1** board);
bool checkRowMatch(Board_1** board, int x1, int x2, int y);
bool checkColMatch(Board_1** board, int y1, int y2, int x);
bool checkIMatch(Board_1** board, int x1, int y1, int x2, int y2);
bool checkLAndZMatch(Board_1** board, int x1, int y1, int x2, int y2);
bool checkUMatch(Board_1** board, int x1, int y1, int x2, int y2);
bool checkMatch(Board_1** board, int x1, int y1, int x2, int y2);
void easyMode(Player& p);