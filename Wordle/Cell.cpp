#include "Cell.h"
#include "generateConsole.h"

char cell[cellHeight][cellWidth] = {
    {"     "},
    {"     "},
    {"     "},
};

void Board_1::drawCell()
{
    if (isStopped)
    {
        if (isValid)
        {
            if (isSelected)
            {
                // Change the selected cell to GREEN
                setColor(2 * 16 + 15);
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
                // Change the current standing cell to BLUE
                setColor(3 * 16 + 15);
                for (int i = 0; i < cellHeight; i++)
                {
                    gotoxy(x, y + i);
                    cout << cell[i];
                }
                gotoxy(cx, cy);
                cout << c;
            }
        }
        else
        {
            if (isSelected)
            {
                // Change the selected cell to GREEN
                setColor(2 * 16 + 15);
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
                // If the cell is matched
                setColor(3 * 16);
                for (int i = 0; i < cellHeight; i++)
                {
                    gotoxy(x, y + i);
                    cout << cell[i];
                }
            }
            // deleteCell();
            setColor(7);
            return;
        }
    }
    else
    {
        if (isValid)
        {
            if (isSelected)
                return;
            else
            {
                // Default cell is YELLOW
                setColor(14 * 16);
                for (int i = 0; i < cellHeight; i++)
                {
                    gotoxy(x, y + i);
                    cout << cell[i];
                }
                gotoxy(cx, cy);
                cout << c;
            }
        }
        else
        {
            if (!isSelected)
                deleteCell();
        }
    }
    setColor(7);
}

void Board_1::drawArrow(int cx2, int cy2)
{
    setColor(14);
    gotoxy(cx, cy + 1);
    cout << "<";
    for (int i = cy + 2; i < cy2 - 2; i++)
        cout << "=";
    cout << ">";
}

void Board_1::deleteCell()
{
    setColor(7);
    for (int i = 0; i < cellHeight; i++)
    {
        gotoxy(x, y + i);
        cout << cell[i];
    }
}
