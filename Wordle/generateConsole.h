#pragma once
#include "Cell.h"

#define windowHeight 780
#define windowWidth 900
#define gameHeight 35
#define gameWidth 87
#define midHeight 15
#define midWidth 40
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13

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