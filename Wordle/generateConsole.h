#pragma once
#include "Cell.h"

#define windowHeight 750
#define windowWidth 870
#define gameHeight 35
#define gameWidth 85
#define midHeight 15
#define midWidth 43
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define SPACEBAR 32

void gotoxy(int x, int y);
void setWindowSizeAndPos();
void setCursor(int mode);
void generateWindow();
void setColor(int textColor);
void drawGraph(int delayTime);
void drawTitle();
void generateGraphic();
void changeBarStatus(int barX, int barY, int bColor, int tColor);
int getConsoleInput();
int generateMenu();
void clearConsole();
void changePlayBarStatus(int barX, int barY, int bColor, int tColor);
int showPlayMenu();
void showCredit();