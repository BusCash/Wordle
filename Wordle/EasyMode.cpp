#include "EasyMode.h"

void generateBoard(Board_1** board)
{
    for (int i = 0; i < boardHeight; i++)
    {
        board[i] = new Board_1[boardWidth];
        for (int j = 0; j < boardWidth; j++)
        {
            // Set the position for each cell
            board[i][j].x = j * cellWidth + 17;
            board[i][j].y = i * (cellHeight + 1) + 12;

            // Set the position for the character
            board[i][j].cx = board[i][j].x + 2;
            board[i][j].cy = board[i][j].y + 1;
        }
    }

    // Get random character for each 2 cells
    int charNum = easyHeight * easyWidth / 2;
    while (charNum)
    {
        int time = 2;
        char c = 65 + rand() % 26;
        while (time)
        {
            int row = rand() % easyHeight + 1, col = rand() % easyWidth + 1;
            if (board[row][col].c == ' ')
            {
                board[row][col].c = c;
                time--;
            }
        }
        charNum--;
    }
}

void deleteBoard(Board_1** board)
{
    for (int i = 0; i < boardHeight; i++)
        delete[] board[i];

    delete[] board;
}

void displayBoard(Board_1** board)
{
    for (int i = 1; i < easyHeight + 1; i++)
    {
        for (int j = 1; j < easyWidth + 1; j++)
        {
            board[i][j].drawCell();
            Sleep(5);
        }
    }
}

bool checkRowMatch(Board_1** board, int j1, int j2, int i)
{
    for (int j = min(j1, j2) + 1; j < max(j1, j2); j++)
        if (board[i][j].c != ' ')
            return false;
    return true;
}

bool checkColMatch(Board_1** board, int i1, int i2, int j)
{
    for (int i = min(i1, i2) + 1; i < max(i1, i2); i++)
        if (board[i][j].c != ' ')
            return false;
    return true;
}

bool checkIMatch(Board_1** board, int i1, int j1, int i2, int j2)
{
    if (j1 == j2)
    {
        if (checkColMatch(board, i1, i2, j1))
            return true;
    }
    else if (i1 == i2)
    {
        if (checkRowMatch(board, j1, j2, i1))
            return true;
    }
    return false;
}

bool checkLMatch(Board_1** board, int i1, int j1, int i2, int j2)
{
    if (board[i1][j2].c == ' ')
        if (checkRowMatch(board, j1, j2, i1) && checkColMatch(board, i1, i2, j2))
            return true;

    if (board[i2][j1].c == ' ')
        if (checkRowMatch(board, j1, j2, i2) && checkColMatch(board, i1, i2, j1))
            return true;
    return false;
}

bool checkZMatch(Board_1** board, int i1, int j1, int i2, int j2)
{
    // Check all way in a rectangle created by p1 and p2
    Position jmin, jmax;
    jmin.x = i2;
    jmin.y = j2;
    jmax.x = i1;
    jmax.y = j1;

    if (j1 < j2)
    {
        jmin.x = i1;
        jmin.y = j1;
        jmax.x = i2;
        jmax.y = j2;
    }

    // Check every cols in the rectangle except the rightmost
    for (int j = jmin.y + 1; j < jmax.y; j++)
        if (checkRowMatch(board, jmin.y, j + 1, jmin.x) && checkColMatch(board, jmin.x, jmax.x + 1, j) && checkRowMatch(board, j, jmax.y, jmax.x))
            return true;

    Position imin, imax;
    imin.x = i2;
    imin.y = j2;
    imax.x = i1;
    imax.y = j1;

    if (i1 < i2)
    {
        imin.x = i1;
        imin.y = j1;
        imax.x = i2;
        imax.y = j2;
    }

    // Check every rows in the rectangle except the topmost
    for (int i = imin.x + 1; i < imax.x; i++)
        if (checkColMatch(board, imin.x, i + 1, imin.y) && checkRowMatch(board, imin.y, imax.y + 1, i) && checkColMatch(board, i, imax.x, imax.y))
            return true;

    return false;
}

bool checkUMatch(Board_1** board, int i1, int j1, int i2, int j2)
{
    int downright = 1, upleft = -1;

    // Check horizontal direction ==============================================
    Position jmin, jmax;
    jmin.x = i2;
    jmin.y = j2;
    jmax.x = i1;
    jmax.y = j1;

    if (j1 < j2)
    {
        jmin.x = i1;
        jmin.y = j1;
        jmax.x = i2;
        jmax.y = j2;
    }

    // Check right direction
    if (checkRowMatch(board, jmin.y, jmax.y, jmin.x))
    {
        int jnext = jmax.y + downright;
        while (jnext <= easyWidth + 1 && board[jmin.x][jnext].c != ' ' && board[jmax.x][jnext].c != ' ')
        {
            if (checkColMatch(board, jmin.x, jmax.x, jnext))
                return true;
            jnext += downright;
        }
    }

    // Check the left direction
    if (checkRowMatch(board, jmax.y, jmin.y, jmax.x))
    {
        int jnext = jmin.y + upleft;
        while (jnext >= 0 && board[jmin.x][jnext].c != ' ' && board[jmax.x][jnext].c != ' ')
        {
            if (checkColMatch(board, jmin.x, jmax.x, jnext))
                return true;
            jnext += upleft;
        }
    }

    // Check vertical direction ================================================
    Position imin, imax;
    imin.x = i2;
    imin.y = j2;
    imax.x = i1;
    imax.y = j1;

    if (i1 < i2)
    {
        imin.x = i1;
        imin.y = j1;
        imax.x = i2;
        imax.y = j2;
    }

    // Check down direction
    if (checkColMatch(board, imin.x, imax.x, imin.y))
    {
        int inext = imax.x + downright;
        while (inext <= easyHeight + 1 && board[inext][imin.y].c != ' ' && board[inext][imax.y].c != ' ')
        {
            if (checkRowMatch(board, imin.y, imax.y, inext))
                return true;
            inext += downright;
        }
    }

    // Check up direction
    if (checkColMatch(board, imax.x, imin.x, imax.y))
    {
        int inext = imin.x + upleft;
        while (inext >= 0 && board[inext][imin.y].c != ' ' && board[inext][imax.y].c != ' ')
        {
            if (checkRowMatch(board, imin.y, imax.y, inext))
                return true;
            inext += upleft;
        }
    }

    return false;
}

bool checkMatch(Board_1** board, int i1, int j1, int i2, int j2)
{
    if (board[i1][j1].c == board[i2][j2].c)
    {
        if (checkIMatch(board, i1, j1, i2, j2))
        {
            gotoxy(1, 1);
            cout
                << "I match";
            return true;
        }
        else
        {
            gotoxy(1, 4);
            cout << "no I match";
        }
        if (checkLMatch(board, i1, j1, i2, j2))
        {
            gotoxy(1, 1);
            cout << "L match";
            return true;
        }
        else
        {
            gotoxy(1, 5);
            cout << "no L match";
        }
        if (checkZMatch(board, i1, j1, i2, j2))
        {
            gotoxy(1, 1);
            cout << "Z match";
            return true;
        }

        else
        {
            gotoxy(1, 6);
            cout << "no Z match";
        }
        if (checkUMatch(board, i1, j1, i2, j2))
        {
            gotoxy(1, 1);
            cout << "U match";
            return true;
        }
        else
        {
            gotoxy(1, 7);
            cout << "no U match";
        }
        Sleep(1000);
        gotoxy(1, 4);
        cout << "            \n              \n              \n               \n";
    }
    gotoxy(1, 1);
    cout << "no match";
    return false;
}

void processAction(Board_1** cell)
{
    int i = 1, j = 1;
    int oldi = i, oldj = j;

    int iselected = 0, jselected = 0;
    int selectedCount = 2;

    cell[i][j].isStopped = true;

    while (true)
    {
        if (cell[i][j].isStopped)
        {
            gotoxy(1, 3);
            cout << i << "," << j;
            cell[oldi][oldj].drawCell();
            oldi = i;
            oldj = j;

            cell[i][j].drawCell();
            cell[i][j].isStopped = false;
        }

        if (cell[i][j].isSelected)
        {
            cell[i][j].drawCell();

            if (selectedCount == 2)
            {
                iselected = i;
                jselected = j;
            }

            selectedCount--;

            if (selectedCount == 0)
            {
                cell[iselected][jselected].isSelected = false;
                cell[i][j].isSelected = false;
                selectedCount = 2;
                gotoxy(1, 2);
                cout << cell[iselected][jselected].c << " " << cell[i][j].c;

                if (checkMatch(cell, iselected, jselected, i, j))
                {
                    cell[iselected][jselected].deleteCell();
                    cell[i][j].deleteCell();

                    cell[iselected][jselected].isValid = false;
                    cell[i][j].isValid = false;
                }
                else
                    cell[iselected][jselected].drawCell();
                cell[i][j].isStopped = true;
                cell[i][j].drawCell();
                cell[i][j].isStopped = false;
            }
        }

        switch (getConsoleInput())
        {
        case 1:
        {
            if (i == 1)
                i = easyHeight;
            else
                i -= 1;
            cell[i][j].isStopped = true;
            break;
        }
        case 2:
        {
            if (i == easyHeight)
                i = 1;
            else
                i += 1;
            cell[i][j].isStopped = true;
            break;
        }
        case 3:
        {
            if (j == 1)
                j = easyWidth;
            else
                j -= 1;
            cell[i][j].isStopped = true;
            break;
        }
        case 4:
        {
            if (j == easyWidth)
                j = 1;
            else
                j += 1;
            cell[i][j].isStopped = true;
            break;
        }
        case 5:
        {
            if (cell[i][j].isSelected == false && cell[i][j].isValid == true)
                cell[i][j].isSelected = true;
            break;
        }
        default:
            cout << "END";
            return;
        }
    }
}

void easyMode(Player& p)
{
    srand(time(0));
    Board_1** board = new Board_1 * [gameHeight];
    generateBoard(board);
    displayBoard(board);
    gotoxy(1, 1);
    processAction(board);
    deleteBoard(board);
}
