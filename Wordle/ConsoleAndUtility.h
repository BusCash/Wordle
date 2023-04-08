#pragma once
#include "Struct.h"

// Define constants for the dimensions of the console window and game board
#define windowHeight 750
#define windowWidth 890
#define gameHeight 35
#define gameWidth 87
#define midHeight 15
#define midWidth 43

// Define constants for keyboard input codes
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define SPACEBAR 32
#define ESC 27

// Set the position of the cursor to the X and Y coordinates
void gotoxy(int x, int y);

// Set the position and size of the console window
void setWindowSizeAndPos();

// Set the visibility of the console cursor
void setCursor(int mode);

// Generate the window frame
void generateWindow();

// Set the text color for the console output
void setColor(int textColor);

// Draw a graph animation
void drawGraph(int delayTime);

// Draw the game title animation
void drawTitle(int delayTime);

// Change the status of a status bar on the game screen
void changeBarStatus(int barX, string barY, int moveY, string s, int bColor, int tColor);

// Get user input from the console keyboard
int getConsoleInput();

// Generate a menu with a moving selection bar
int generateMenu(int barX, int barY, string sbarY, string barName, int barNum);

// Clear the console screen 
void clearConsole();

// Display the credits
void showCredits();

// Read a background image from text file
void getBackground(char[][65], int m, int n, string filein);

// Display the game parameters
void showParameter(Player* p, string mode);

// Play sound effect
void playSound(int i);

// Display the intro animation
void intro();