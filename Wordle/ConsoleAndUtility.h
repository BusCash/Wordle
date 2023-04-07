#pragma once
#include "Struct.h"

#define windowHeight 750
#define windowWidth 890
#define gameHeight 35
#define gameWidth 87
#define midHeight 15
#define midWidth 43
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define SPACEBAR 32
#define ESC 27

void gotoxy(int x, int y);
void setWindowSizeAndPos();
void setCursor(int mode);
void generateWindow();
void setColor(int textColor);
void drawGraph(int delayTime);
void drawTitle(int delayTime);
void changeBarStatus(int barX, string barY, int moveY, string s, int bColor, int tColor);
int getConsoleInput();
int generateMenu(int barX, int barY, string sbarY, string barName, int barNum);
void clearConsole();
void showCredits();
void getBackground(char[][65], int m, int n, string filein);
void showParameter(Player* p, string mode);
void playSound(int i);
void playTrack();
void animation();