#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

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
    int ci, cj;
    char c = ' ';
    int cx, cy;
    string background[15];

    bool isStopped = false;
    bool isSelected = false;
    bool isValid = true;
    bool isDeleted = false;

    void drawCell();
    void deleteCell();

    void drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2);
    void deleteArrow(int cx2, int cy2, int i1, int j1, int i2, int j2);
};
