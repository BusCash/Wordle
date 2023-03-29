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

void Board_1::deleteCell()
{
    setColor(7);
    for (int i = 0; i < cellHeight; i++)
    {
        gotoxy(x, y + i);
        cout << cell[i];
    }
}

void Board_1::drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2)
{
    int ci2 = (cy2 - 1 - 11) / (cellHeight + 1),
        cj2 = (cx2 - 2 - 17) / (cellWidth);

    setColor(14 * 16);
    if ((ci == i1 && cj == j1 && ci2 == i2 && cj2 == j2) || (ci == i2 && cj == j2 && ci2 == i1 && cj2 == j1)) // If both are the selected
    {
        if (cy == cy2)
        {
            gotoxy(min(cx, cx2) + 1, cy);
            putchar(17);
            for (int i = min(cx, cx2) + 2; i < max(cx, cx2) - 1; i++)
            {
                gotoxy(i, cy);
                putchar(45);
            }
            putchar(16);
        }
        if (cx == cx2)
        {
            gotoxy(cx, min(cy, cy2) + 1);
            putchar(30);
            for (int i = min(cy, cy2) + 2; i < max(cy, cy2) - 1; i++)
            {
                gotoxy(cx, i);
                putchar(124);
            }
            gotoxy(cx, max(cy, cy2) - 1);
            putchar(31);
        }
    }
    else if ((ci == i1 && cj == j1 && (ci2 != i2 || cj2 != j2)) || (ci == i2 && cj == j2 && (ci2 != i1 || cj2 != j1))) // If the first is the selected
    {
        if (cy == cy2)
        {
            if (cx < cx2)
            {
                gotoxy(cx + 1, cy);
                putchar(17);
                for (int i = cx + 2; i < cx2 + 1; i++)
                {
                    gotoxy(i, cy);
                    putchar(45);
                }
            }
            else
            {
                for (int i = cx2; i < cx - 1; i++)
                {
                    gotoxy(i, cy);
                    putchar(45);
                }
                gotoxy(cx - 1, cy);
                putchar(16);
            }
        }
        if (cx == cx2)
        {
            if (cy < cy2)
            {
                gotoxy(cx, cy + 1);
                putchar(30);
                for (int i = cy + 2; i < cy2; i++)
                {
                    gotoxy(cx, i);
                    putchar(124);
                }
            }
            else
            {
                for (int i = cy2 + 1; i < cy - 1; i++)
                {
                    gotoxy(cx, i);
                    putchar(124);
                }
                gotoxy(cx, cy - 1);
                putchar(31);
            }
        }
    }
    else if (((ci != i1 || cj != j1) && ci2 == i2 && cj2 == j2) || ((ci != i2 || cj != j2) && ci2 == i1 && cj2 == j1)) // If the second is the selected
    {
        if (cy == cy2)
        {
            if (cx2 < cx)
            {
                gotoxy(cx2 + 1, cy2);
                putchar(17);
                for (int i = cx2 + 2; i < cx + 1; i++)
                {
                    gotoxy(i, cy2);
                    putchar(45);
                }
            }
            else
            {
                for (int i = cx; i < cx2 - 1; i++)
                {
                    gotoxy(i, cy2);
                    putchar(45);
                }
                gotoxy(cx2 - 1, cy2);
                putchar(16);
            }
        }
        if (cx == cx2)
        {
            if (cy2 < cy)
            {
                gotoxy(cx2, cy2 + 1);
                putchar(30);
                for (int i = cy2 + 2; i < cy; i++)
                {
                    gotoxy(cx2, i);
                    putchar(124);
                }
            }
            else
            {
                for (int i = cy + 1; i < cy2 - 1; i++)
                {
                    gotoxy(cx2, i);
                    putchar(124);
                }
                gotoxy(cx2, cy2 - 1);
                putchar(31);
            }
        }
    }
    else if ((ci != i1 || cj != j1 && ci2 != i2 || cj2 != j2) && (ci != i2 || cj != j2 || ci2 != i1 || cj2 != j1)) // If none is the selected
    {
        if (cy == cy2)
        {
            for (int i = min(cx, cx2); i < max(cx, cx2) + 1; i++)
            {
                gotoxy(i, cy);
                putchar(45);
            }
        }
        if (cx == cx2)
        {
            for (int i = min(cy, cy2) + 1; i < max(cy, cy2); i++)
            {
                gotoxy(cx, i);
                putchar(124);
            }
        }
    }
}

void Board_1::deleteArrow(int cx2, int cy2, int i1, int j1, int i2, int j2)
{
    int ci2 = (cy2 - 1 - 11) / (cellHeight + 1),
        cj2 = (cx2 - 2 - 17) / (cellWidth);

    setColor(7);
    if ((ci == i1 && cj == j1 && ci2 == i2 && cj2 == j2) || (ci == i2 && cj == j2 && ci2 == i1 && cj2 == j1)) // If both are the selected
    {
        if (cy == cy2)
        {
            for (int i = min(cx, cx2) + 2; i < max(cx, cx2) - 1; i++)
            {
                gotoxy(i, cy);
                putchar(32);
            }
        }
        if (cx == cx2)
        {
            for (int i = min(cy, cy2) + 2; i < max(cy, cy2) - 1; i++)
            {
                gotoxy(cx, i);
                putchar(32);
            }
        }
    }
    else if ((ci == i1 && cj == j1 && (ci2 != i2 || cj2 != j2)) || (ci == i2 && cj == j2 && (ci2 != i1 || cj2 != j1))) // If the first is the selected
    {
        if (cy == cy2)
        {
            if (cx < cx2)
            {
                for (int i = cx + 2; i < cx2 + 1; i++)
                {
                    gotoxy(i, cy);
                    putchar(32);
                }
            }
            else
            {
                for (int i = cx2; i < cx - 1; i++)
                {
                    gotoxy(i, cy);
                    putchar(32);
                }
            }
        }
        if (cx == cx2)
        {
            if (cy < cy2)
            {
                for (int i = cy + 2; i < cy2; i++)
                {
                    gotoxy(cx, i);
                    putchar(32);
                }
            }
            else
            {
                for (int i = cy2 + 1; i < cy - 1; i++)
                {
                    gotoxy(cx, i);
                    putchar(32);
                }
            }
        }
    }
    else if (((ci != i1 || cj != j1) && ci2 == i2 && cj2 == j2) || ((ci != i2 || cj != j2) && ci2 == i1 && cj2 == j1)) // If the second is the selected
    {
        if (cy == cy2)
        {
            if (cx2 < cx)
            {
                for (int i = cx2 + 2; i < cx + 1; i++)
                {
                    gotoxy(i, cy2);
                    putchar(32);
                }
            }
            else
            {
                for (int i = cx; i < cx2 - 1; i++)
                {
                    gotoxy(i, cy2);
                    putchar(32);
                }
            }
        }
        if (cx == cx2)
        {
            if (cy2 < cy)
            {
                for (int i = cy2 + 2; i < cy; i++)
                {
                    gotoxy(cx2, i);
                    putchar(32);
                }
            }
            else
            {
                for (int i = cy + 1; i < cy2 - 1; i++)
                {
                    gotoxy(cx2, i);
                    putchar(32);
                }
            }
        }
    }
    else if ((ci != i1 || cj != j1 && ci2 != i2 || cj2 != j2) && (ci != i2 || cj != j2 || ci2 != i1 || cj2 != j1)) // If none is the selected
    {
        if (cy == cy2)
        {
            for (int i = min(cx, cx2); i < max(cx, cx2) + 1; i++)
            {
                gotoxy(i, cy);
                putchar(32);
            }
        }
        if (cx == cx2)
        {
            for (int i = min(cy, cy2) + 1; i < max(cy, cy2); i++)
            {
                gotoxy(cx, i);
                putchar(32);
            }
        }
    }
}
