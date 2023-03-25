#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define easyHeight 5
#define easyWidth 6
#define cellHeight 3
#define cellWidth 8

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

    bool isSelected = false;
    bool isValid = true;

    void drawCell();
    void deleteCell();
};
