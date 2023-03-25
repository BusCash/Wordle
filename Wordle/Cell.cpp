#include "Cell.h"
#include "generateConsole.h"

char cell[cellHeight][cellWidth] = {
    {"       "},
    {"       "},
    {"       "},
};

void Board_1::drawCell()
{
    if (isSelected == true)
    {
        setColor(3 * 16 + 15);
        for (int i = 0; i < cellHeight; i++)
        {
            gotoxy(x, y + i);
            cout << cell[i];
        }
        gotoxy(x + 3, y + 1);
        cout << c;
    }
    else
    {
        setColor(14 * 16);
        for (int i = 0; i < cellHeight; i++)
        {
            gotoxy(x, y + i);
            cout << cell[i];
        }
        gotoxy(x + 3, y + 1);
        cout << c;
    }
    setColor(7);
}

void Board_1::deleteCell()
{
    setColor(7);
    for (int i = 0; i < 3; i++)
    {
        gotoxy(x * cellWidth + 16, y * (cellHeight + 1) + 10 + i);
        cout << cell[i];
    }
}
