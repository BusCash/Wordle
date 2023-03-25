#include "EasyMode.h"

void generateBoard(Board_1** board)
{
    for (int i = 0; i < easyHeight; i++)
    {
        board[i] = new Board_1[easyWidth];
        for (int j = 0; j < easyWidth; j++)
        {
            // Set the position for each cell
            board[i][j].x = j * cellWidth + 16;
            board[i][j].y = i * (cellHeight + 1) + 10;
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
            int row = rand() % easyHeight, col = rand() % easyWidth;
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
    for (int i = 0; i < easyHeight; i++)
        delete[] board[i];

    delete[] board;
}

void displayBoard(Board_1** board)
{
    for (int i = 0; i < easyHeight; i++)
    {
        for (int j = 0; j < easyWidth; j++)
        {
            board[i][j].drawCell();
            Sleep(5);
        }
    }
}

bool checkRowMatch(Board_1** board, int x1, int x2, int y)
{
    for (int x = min(x1, x2) + 1; x < max(x1, x2); x++)
        if (board[y][x].c != ' ')
            return false;
    return true;
}

bool checkColMatch(Board_1** board, int y1, int y2, int x)
{
    for (int y = min(y1, y2) + 1; y < max(y1, y2); y++)
        if (board[y][x].c != ' ')
            return false;
    return true;
}

bool checkIMatch(Board_1** board, int x1, int y1, int x2, int y2)
{
    if (x1 == x2)
        checkColMatch(board, y1, y2, x1);
    else if (y1 == y2)
        checkRowMatch(board, x1, x2, y1);
    else
        return false;
}

bool checkLAndZMatch(Board_1** board, int x1, int y1, int x2, int y2)
{
    // Check all way in a rectangle created by p1 and p2
    int xmin = min(x1, x2), xmax = max(x1, x2);
    int ymin = min(y1, y2), ymax = max(y1, y2);

    // Check every cols in the rectangle except the rightmost
    for (int x = xmin + 1; x <= xmax; x++)
        if (checkRowMatch(board, xmin, x, ymin) && checkColMatch(board, ymin, ymax, x) && checkRowMatch(board, x, xmax, ymax))
            return true;

    // Check every rows in the rectangle except the topmost
    for (int y = ymin + 1; y <= ymax; y++)
        if (checkColMatch(board, ymin, y, xmin) && checkRowMatch(board, xmin, xmax, y) && checkColMatch(board, y, ymax, xmax))
            return true;

    return false;
}

bool checkUMatch(Board_1** board, int x1, int y1, int x2, int y2)
{
    int downright = 1, upleft = -1;

    // Check horizontal direction ==============================================
    Position xmin, xmax;
    xmin.x = x2;
    xmin.y = y2;
    xmax.x = x1;
    xmax.y = y1;

    if (x1 < x2)
    {
        xmin.x = x1;
        xmin.y = y1;
        xmax.x = x2;
        xmax.y = y2;
    }

    // Check right direction
    if (checkRowMatch(board, xmin.x, xmax.x, xmin.y))
    {
        int xnext = xmax.x + downright;
        while (board[xmin.y][xnext].c != ' ' && board[xmax.y][xnext].c != ' ')
        {
            if (checkColMatch(board, xmin.y, xmax.y, xnext))
                return true;
            xnext += downright;
        }
    }

    // Check the left direction
    if (checkRowMatch(board, xmin.x, xmax.x, xmax.y))
    {
        int xnext = xmin.x + upleft;
        while (board[xmin.y][xnext].c != ' ' && board[xmax.y][xnext].c != ' ')
        {
            if (checkColMatch(board, xmin.y, xmax.y, xnext))
                return true;
            xnext += upleft;
        }
    }

    // Check vertical direction ================================================
    Position ymin, ymax;
    ymin.y = y2;
    ymin.x = x2;
    ymax.y = y1;
    ymax.x = x1;

    if (y1 < y2)
    {
        ymin.y = y1;
        ymin.x = x1;
        ymax.y = y2;
        ymax.x = x2;
    }

    // Check down direction
    if (checkColMatch(board, ymin.y, ymax.y, ymin.x))
    {
        int ynext = ymax.y + downright;
        while (board[ynext][ymin.x].c != ' ' && board[ynext][ymax.x].c != ' ')
        {
            if (checkRowMatch(board, ymin.x, ymax.x, ynext))
                return true;
            ynext += downright;
        }
    }

    // Check up direction
    if (checkColMatch(board, ymin.y, ymax.y, ymax.x))
    {
        int ynext = ymin.y + upleft;
        while (board[ynext][ymin.x].c != ' ' && board[ynext][ymax.x].c != ' ')
        {
            if (checkRowMatch(board, ymin.x, ymax.x, ynext))
                return true;
            ynext += upleft;
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
        else if (checkLAndZMatch(board, x1, y1, x2, y2))
            return true;
        else if (checkUMatch(board, x1, y1, x2, y2))
            return true;
    }
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
            if (i == easyHeight - 1)
                i = 0;
            else
                i += 1;
            cell[i][j].isSelected = true;
            break;
        }
        case 3:
        {
            if (j == 0)
                j = easyWidth - 1;
            else
                j -= 1;
            cell[i][j].isSelected = true;
            break;
        }
        case 4:
        {
            if (j == easyHeight - 1)
                j = 0;
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
    move(board);
    deleteBoard(board);
}
