#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define boardHeight 6
#define boardWidth 9
#define easyHeight 4
#define easyWidth 7
#define cellHeight 3
#define cellWidth 6

using namespace std;

struct Player
{
    string name;
    string id;
    int point = 0;
};

struct Position
{
    int x, y;
};

struct Board_1
{
    int x, y;
    char c = ' ';
    int cx, cy;

    bool isStopped = false;
    bool isSelected = false;
    bool isValid = true;
    bool isDeleted = false;

    void drawCell();
    void drawArrow(int cx2, int cy2);
    void deleteCell();
};
