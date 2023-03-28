#include "Cell.h"
#include "generateConsole.h"

char cell[cellHeight][cellWidth] = {
    {"     "},
    {"     "},
    {"     "},
};

void Board_1::drawCell()
{
    if (!isValid)
    {
        if (isStopped)
        {
            setColor(3 * 16 + 15);
            for (int i = 0; i < cellHeight; i++)
            {
                gotoxy(x, y + i);
                cout << cell[i];
            }
        }
        else
            deleteCell();
        setColor(7);
        return;
    }

    if (isStopped)
    {
        setColor(3 * 16 + 15);
        for (int i = 0; i < cellHeight; i++)
        {
            gotoxy(x, y + i);
            cout << cell[i];
        }
        gotoxy(cx, cy);
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
        gotoxy(cx, cy);
        cout << c;
    }

    if (isSelected)
    {
        setColor(2 * 16 + 15);
        for (int i = 0; i < cellHeight; i++)
        {
            gotoxy(x, y + i);
            cout << cell[i];
        }
        gotoxy(cx, cy);
        cout << c;
    }
    setColor(7);
}

void Board_1::deleteCell()
{
    setColor(7);
    c = ' ';
    for (int i = 0; i < cellHeight; i++)
    {
        gotoxy(x, y + i);
        cout << cell[i];
    }
}
