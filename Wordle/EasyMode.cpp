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

    // Set the edge unavailable
    for (int i = 0; i < boardHeight; i++)
    {
        board[i][0].isValid = false;
        board[i][boardWidth - 1].isValid = false;
    }
    for (int j = 0; j < boardWidth; j++)
    {
        board[0][j].isValid = false;
        board[boardHeight - 1][j].isValid = false;
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
    if (j1 < j2)
    {
        jmin.x = i1;
        jmin.y = j1;
        jmax.x = i2;
        jmax.y = j2;
    }
    else
    {
        jmin.x = i2;
        jmin.y = j2;
        jmax.x = i1;
        jmax.y = j1;
    }

    // Check every cols in the rectangle except the rightmost
    for (int j = jmin.y + 1; j < jmax.y; j++)
        if (checkRowMatch(board, jmin.y, j + 1, jmin.x) && checkColMatch(board, jmin.x, jmax.x + (jmax.x > jmin.x) ? 1 : -1, j) && checkRowMatch(board, j, jmax.y, jmax.x))
            return true;

    Position imin, imax;
    if (i1 < i2)
    {
        imin.x = i1;
        imin.y = j1;
        imax.x = i2;
        imax.y = j2;
    }
    else
    {
        imin.x = i2;
        imin.y = j2;
        imax.x = i1;
        imax.y = j1;
    }

    // Check every rows in the rectangle except the topmost
    for (int i = imin.x + 1; i < imax.x; i++)
        if (checkColMatch(board, imin.x, i + 1, imin.y) && checkRowMatch(board, imin.y, imax.y + (imax.y > imin.y) ? 1 : -1, i) && checkColMatch(board, i, imax.x, imax.y))
            return true;

    return false;
}

bool checkUMatch(Board_1** board, int i1, int j1, int i2, int j2)
{
    int downright = 1, upleft = -1;

    Position jmin, jmax;
    if (j1 < j2)
    {
        jmin.x = i1;
        jmin.y = j1;
        jmax.x = i2;
        jmax.y = j2;
    }
    else
    {
        jmin.x = i2;
        jmin.y = j2;
        jmax.x = i1;
        jmax.y = j1;
    }

    // Check right direction
    if (checkRowMatch(board, jmin.y, jmax.y + 1, jmin.x))
    {
        int jnext = jmax.y + downright;
        while (jnext <= easyWidth + 1 && board[jmin.x][jnext].c == ' ' && board[jmax.x][jnext].c == ' ')
        {
            if (checkColMatch(board, jmin.x, jmax.x, jnext))
                return true;
            jnext += downright;
        }
    }

    // Check the left direction
    if (checkRowMatch(board, jmax.y, jmin.y - 1, jmax.x))
    {
        int jnext = jmin.y + upleft;
        while (jnext >= 0 && board[jmin.x][jnext].c == ' ' && board[jmax.x][jnext].c == ' ')
        {
            if (checkColMatch(board, jmin.x, jmax.x, jnext))
                return true;
            jnext += upleft;
        }
    }

    Position imin, imax;
    if (i1 < i2)
    {
        imin.x = i1;
        imin.y = j1;
        imax.x = i2;
        imax.y = j2;
    }
    else
    {
        imin.x = i2;
        imin.y = j2;
        imax.x = i1;
        imax.y = j1;
    }

    // Check down direction
    if (checkColMatch(board, imin.x, imax.x + 1, imin.y))
    {
        int inext = imax.x + downright;
        while (inext <= easyHeight + 1 && board[inext][imin.y].c == ' ' && board[inext][imax.y].c == ' ')
        {
            if (checkRowMatch(board, imin.y, imax.y, inext))
                return true;
            inext += downright;
        }
    }

    // Check up direction
    if (checkColMatch(board, imax.x, imin.x - 1, imax.y))
    {
        int inext = imin.x + upleft;
        while (inext >= 0 && board[inext][imin.y].c == ' ' && board[inext][imax.y].c == ' ')
        {
            if (checkRowMatch(board, imin.y, imax.y, inext))
                return true;
            inext += upleft;
        }
    }

    return false;
}

bool checkMatch(Board_1** board, int x1, int y1, int x2, int y2)
{
    if (board[x1][y1].c == board[x2][y2].c)
    {
        if (checkIMatch(board, x1, y1, x2, y2))
            return true;
        else if (checkLMatch(board, x1, y1, x2, y2))
            return true;

        else if (checkUMatch(board, x1, y1, x2, y2))
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

void move(Board_1** cell)
{
    // int topmost = 10;
    // int leftmost = 16;
    // int bottommost = topmost + (cellHeight + 1) * (easyHeight - 1);
    // int rightmost = leftmost + cellWidth * (easyWidth - 1);

    // int x = 16, y = 10;
    // int oldx = x, oldy = y;
    int i = 0, j = 0;
    int oldi = i, oldj = j;

    cell[i][j].isSelected = true;

    cell[i][j].isStopped = true;
    // lỗi chọn 1 ô 2 lần, chọn 1 ô đi vào lại thì mất
    while (true)
    {
        if (cell[i][j].isSelected == true)
        {
            cell[oldi][oldj].drawCell();
            oldi = i;
            oldj = j;

            cell[i][j].drawCell();
            cell[i][j].isSelected = false;
        }

        switch (getConsoleInput())
        {
        case 1:
        {
            if (i == 0)
                i = easyHeight - 1;
            else
                i -= 1;
            cout << i << "," << j << " ";
            cell[i][j].isSelected = true;
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
            cell[i][j].isSelected = true;
            break;
        }
        case 5:
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
    processAction(board);
    deleteBoard(board);
}
