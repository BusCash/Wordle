﻿#include "EasyMode.h"

void generateBoard(Board_1** board)
{
    for (int i = 0; i < boardHeight; i++)
    {
        board[i] = new Board_1[boardWidth];
        for (int j = 0; j < boardWidth; j++)
        {
            // Set the position for the cell
            board[i][j].x = j * cellWidth + 17;
            board[i][j].y = i * (cellHeight + 1) + 11;

            // Set the order for the cell
            board[i][j].ci = i;
            board[i][j].cj = j;

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

bool checkIMatch(Board_1** board, int i1, int j1, int i2, int j2, int type)
{
    if (j1 == j2)
    {
        if (checkColMatch(board, i1, i2, j1))
        {
            if (type == 0)
            {
                board[i1][j1].drawArrow(board[i2][j1].cx, board[i2][j1].cy, i1, j1, i2, j2);
                Sleep(200);

                for (int i = min(i1, i2) + 1; i < max(i1, i2); i++)
                    board[i][j1].deleteCell(7);
            }

            return true;
        }
    }
    else if (i1 == i2)
    {
        if (checkRowMatch(board, j1, j2, i1))
        {
            if (type == 0)
            {
                board[i1][j1].drawArrow(board[i1][j2].cx, board[i1][j2].cy, i1, j1, i2, j2);
                Sleep(200);

                for (int j = min(j1, j2) + 1; j < max(j1, j2); j++)
                    board[i1][j].deleteCell(7);
            }

            return true;
        }
    }
    return false;
}

bool checkLMatch(Board_1** board, int i1, int j1, int i2, int j2, int type)
{
    if (board[i1][j2].c == ' ')
        if (checkRowMatch(board, j1, j2, i1) && checkColMatch(board, i1, i2, j2))
        {
            if (type == 0)
            {
                board[i1][j1].drawArrow(board[i1][j2].cx, board[i1][j2].cy, i1, j1, i2, j2);
                board[i1][j2].drawArrow(board[i2][j2].cx, board[i2][j2].cy, i1, j1, i2, j2);
                Sleep(200);

                for (int j = min(j1, j2); j <= max(j1, j2); j++)
                    board[i1][j].deleteCell(7);
                for (int i = min(i1, i2); i <= max(i1, i2); i++)
                    board[i][j2].deleteCell(7);
            }

            return true;
        }

    if (board[i2][j1].c == ' ')
        if (checkRowMatch(board, j1, j2, i2) && checkColMatch(board, i1, i2, j1))
        {
            if (type == 0)
            {
                board[i2][j2].drawArrow(board[i2][j1].cx, board[i2][j1].cy, i1, j1, i2, j2);
                board[i2][j1].drawArrow(board[i1][j1].cx, board[i1][j1].cy, i1, j1, i2, j2);
                Sleep(200);

                for (int j = min(j2, j1); j <= max(j2, j1); j++)
                    board[i2][j].deleteCell(7);
                for (int i = min(i2, i1); i <= max(i2, i1); i++)
                    board[i][j1].deleteCell(7);
            }

            return true;
        }
    return false;
}

bool checkZMatch(Board_1** board, int i1, int j1, int i2, int j2, int type)
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
        if (checkRowMatch(board, jmin.y, j + 1, jmin.x))
        {
            int jmax_x;
            if (jmax.x > jmin.x)
                jmax_x = jmax.x + 1;
            else
                jmax_x = jmax.x - 1;
            if (checkColMatch(board, jmin.x, jmax_x, j) && checkRowMatch(board, j, jmax.y, jmax.x))
            {
                if (type == 0)
                {
                    board[jmin.x][jmin.y].drawArrow(board[jmin.x][j].cx, board[jmin.x][j].cy, i1, j1, i2, j2);
                    board[jmin.x][j].drawArrow(board[jmax.x][j].cx, board[jmax.x][j].cy, i1, j1, i2, j2);
                    board[jmax.x][j].drawArrow(board[jmax.x][jmax.y].cx, board[jmax.x][jmax.y].cy, i1, j1, i2, j2);
                    Sleep(200);

                    for (int jd = jmin.y + 1; jd < j; jd++)
                        board[jmin.x][jd].deleteCell(7);
                    for (int id = min(jmin.x, jmax.x); id <= max(jmin.x, jmax.x); id++)
                        board[id][j].deleteCell(7);
                    for (int jd = j; jd < jmax.y; jd++)
                        board[jmax.x][jd].deleteCell(7);
                }

                return true;
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

    // Check every rows in the rectangle except the topmost
    for (int i = imin.x + 1; i < imax.x; i++)
        if (checkColMatch(board, imin.x, i + 1, imin.y))
        {
            int imax_y;
            if (imax.y > imin.y)
                imax_y = imax.y + 1;
            else
                imax_y = imax.y - 1;
            if (checkRowMatch(board, imin.y, imax_y, i) && checkColMatch(board, i, imax.x, imax.y))
            {
                if (type == 0)
                {
                    board[imin.x][imin.y].drawArrow(board[i][imin.y].cx, board[i][imin.y].cy, i1, j1, i2, j2);
                    board[i][imin.y].drawArrow(board[i][imax.y].cx, board[i][imax.y].cy, i1, j1, i2, j2);
                    board[imax.x][imax.y].drawArrow(board[i][imax.y].cx, board[i][imax.y].cy, i1, j1, i2, j2);
                    Sleep(200);

                    for (int id = imin.x + 1; id < i; id++)
                        board[id][imin.y].deleteCell(7);
                    for (int jd = min(imin.y, imax.y); jd <= max(imin.y, imax.y); jd++)
                        board[i][jd].deleteCell(7);
                    for (int id = i + 1; id < imax.x; id++)
                        board[id][imax.y].deleteCell(7);
                }

                return true;
            }
        }

    return false;
}

bool checkUMatch(Board_1** board, int i1, int j1, int i2, int j2, int type)
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
            {
                if (type == 0)
                {
                    board[jmin.x][jnext].drawArrow(board[jmax.x][jnext].cx, board[jmax.x][jnext].cy, i1, j1, i2, j2);
                    board[jmin.x][jmin.y].drawArrow(board[jmin.x][jnext].cx, board[jmin.x][jnext].cy, i1, j1, i2, j2);
                    board[jmax.x][jmax.y].drawArrow(board[jmax.x][jnext].cx, board[jmax.x][jnext].cy, i1, j1, i2, j2);
                    Sleep(200);

                    for (int i = min(jmin.x, jmax.x); i <= max(jmin.x, jmax.x); i++)
                        board[i][jnext].deleteCell(7);
                    for (int j = jmin.y + 1; j < jnext; j++)
                        board[jmin.x][j].deleteCell(7);
                    for (int j = jmax.y + 1; j < jnext; j++)
                        board[jmax.x][j].deleteCell(7);
                }

                return true;
            }
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
            {
                if (type == 0)
                {
                    board[jmin.x][jnext].drawArrow(board[jmax.x][jnext].cx, board[jmax.x][jnext].cy, i1, j1, i2, j2);
                    board[jmin.x][jmin.y].drawArrow(board[jmin.x][jnext].cx, board[jmin.x][jnext].cy, i1, j1, i2, j2);
                    board[jmax.x][jmax.y].drawArrow(board[jmax.x][jnext].cx, board[jmax.x][jnext].cy, i1, j1, i2, j2);
                    Sleep(200);

                    for (int i = min(jmin.x, jmax.x); i <= max(jmin.x, jmax.x); i++)
                        board[i][jnext].deleteCell(7);
                    for (int j = jnext + 1; j < jmin.y; j++)
                        board[jmin.x][j].deleteCell(7);
                    for (int j = jnext + 1; j < jmax.y; j++)
                        board[jmax.x][j].deleteCell(7);
                }

                return true;
            }
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
            {
                if (type == 0)
                {
                    board[imin.x][imin.y].drawArrow(board[inext][imin.y].cx, board[inext][imin.y].cy, i1, j1, i2, j2);
                    board[imax.x][imax.y].drawArrow(board[inext][imax.y].cx, board[inext][imax.y].cy, i1, j1, i2, j2);
                    board[inext][imin.y].drawArrow(board[inext][imax.y].cx, board[inext][imax.y].cy, i1, j1, i2, j2);
                    Sleep(200);

                    for (int i = imin.x + 1; i < inext; i++)
                        board[i][imin.y].deleteCell(7);
                    for (int i = imax.x + 1; i < inext; i++)
                        board[i][imax.y].deleteCell(7);
                    for (int j = min(imin.y, imax.y); j <= max(imin.y, imax.y); j++)
                        board[inext][j].deleteCell(7);
                }

                return true;
            }
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
            {
                if (type == 0)
                {
                    board[imin.x][imin.y].drawArrow(board[inext][imin.y].cx, board[inext][imin.y].cy, i1, j1, i2, j2);
                    board[imax.x][imax.y].drawArrow(board[inext][imax.y].cx, board[inext][imax.y].cy, i1, j1, i2, j2);
                    board[inext][imin.y].drawArrow(board[inext][imax.y].cx, board[inext][imax.y].cy, i1, j1, i2, j2);
                    Sleep(200);

                    for (int i = inext + 1; i < imin.x; i++)
                        board[i][imin.y].deleteCell(7);
                    for (int i = inext + 1; i < imax.x; i++)
                        board[i][imax.y].deleteCell(7);
                    for (int j = min(imin.y, imax.y); j <= max(imin.y, imax.y); j++)
                        board[inext][j].deleteCell(7);
                }

                return true;
            }
            inext += upleft;
        }
    }

    return false;
}

bool checkMatch(Board_1** board, int i1, int j1, int i2, int j2, int type) // type 0: check player choice, 1: check valid board
{
    if (board[i1][j1].c == board[i2][j2].c)
    {
        if (checkIMatch(board, i1, j1, i2, j2, type))
            return true;

        else if (checkLMatch(board, i1, j1, i2, j2, type))
            return true;

        else if (checkZMatch(board, i1, j1, i2, j2, type))
            return true;

        else if (checkUMatch(board, i1, j1, i2, j2, type))
            return true;
    }
    return false;
}

bool checkValidBoard(Board_1** board)
{
    char check = 'A';
    while (check >= 'A' && check <= 'Z')
    {
        int cnt = 0;
        int* pos = new int[easyHeight * easyWidth];
        for (int i = 1; i < easyHeight + 1; i++)
        {
            for (int j = 1; j < easyWidth + 1; j++)
            {
                if (board[i][j].c == check && board[i][j].isValid)
                {
                    pos[cnt++] = i;
                    pos[cnt++] = j;
                }
            }
        }
        for (int i = 0; i < cnt - 2; i += 2)
        {
            for (int j = i + 2; j < cnt; j += 2)
            {
                if (checkMatch(board, pos[i], pos[i + 1], pos[j], pos[j + 1], 1)) // Check if there are any ways left
                {
                    delete[] pos;
                    return true;
                }
            }
        }
        check++;
        delete[] pos;
    }
    return false;
}

void resetPlayingBoard(Board_1** board, int deletedCount)
{
    int restCount = (easyHeight * easyWidth - deletedCount) / 2;
    while (restCount)
    {
        int time = 2;
        char c = 65 + rand() % 26;
        while (time)
        {
            int i = rand() % easyHeight + 1, j = rand() % easyWidth + 1;
            if (board[i][j].isValid)
            {
                board[i][j].c == c;
                time--;
            }
        }
        restCount--;
    }
}

void showMoveSuggestion(Board_1** cell)
{
    char check = 'A';
    while (check >= 'A' && check <= 'Z')
    {
        int cnt = 0;
        int* pos = new int[easyHeight * easyWidth];

        for (int i = 1; i < easyHeight + 1; i++)
        {
            for (int j = 1; j < easyWidth + 1; j++)
            {
                if (cell[i][j].c == check && cell[i][j].isValid)
                {
                    pos[cnt++] = i;
                    pos[cnt++] = j;
                }
            }
        }

        for (int i = 0; i < cnt - 2; i += 2)
        {
            for (int j = i + 2; j < cnt; j += 2)
            {
                if (checkMatch(cell, pos[i], pos[i + 1], pos[j], pos[j + 1], 1)) // Check if there are any ways left
                {
                    cell[pos[i]][pos[i + 1]].isHint = true;
                    cell[pos[j]][pos[j + 1]].isHint = true;
                    cell[pos[i]][pos[i + 1]].drawCell();
                    cell[pos[j]][pos[j + 1]].drawCell();
                    Sleep(200);

                    cell[pos[i]][pos[i + 1]].isHint = false;
                    cell[pos[j]][pos[j + 1]].isHint = false;
                    cell[pos[i]][pos[i + 1]].drawCell();
                    cell[pos[j]][pos[j + 1]].drawCell();

                    delete[] pos;
                    return;
                }
            }
        }
        check++;
        delete[] pos;
    }
}

void processSelectedCell(Board_1** cell, int i, int j, int iselected, int jselected, int& deletedCount)
{
    cell[i][j].drawCell(); // Set the selected cell;
    Sleep(200);

    cell[iselected][jselected].isSelected = false;
    cell[i][j].isSelected = false;

    if (checkMatch(cell, iselected, jselected, i, j, 0))
    {
        cell[iselected][jselected].deleteCell(7);
        cell[i][j].deleteCell(7);

        cell[iselected][jselected].c = ' ';
        cell[i][j].c = ' ';

        cell[iselected][jselected].isDeleted = true;
        cell[i][j].isDeleted = true;

        deletedCount += 2;

        if (!checkValidBoard(cell))
        {
            do
            {
                resetPlayingBoard(cell, deletedCount);
            } while (!checkValidBoard(cell));
            displayBoard(cell);
        }
    }
    else
    {
        if (!cell[iselected][jselected].isDeleted)
            cell[iselected][jselected].isValid = true;
        if (!cell[i][j].isDeleted)
            cell[i][j].isValid = true;

        // Set the old selected cell back to default
        cell[iselected][jselected].drawCell();
    }

    // When done process set the current standing cell
    cell[i][j].isStopped = true;
    cell[i][j].drawCell();
    cell[i][j].isStopped = false;
}

void processAction(Board_1** cell)
{
    int i = 1, j = 1;
    int oldi = i, oldj = j;

    int iselected = 0, jselected = 0;
    int selectedCount = 2;
    int deletedCount = 0;

    cell[i][j].isStopped = true;

    while (true)
    {
        if (cell[i][j].isStopped)
        {
            gotoxy(1, 1);
            cout << cell[i][j].cx << "," << cell[i][j].cy;
            cell[oldi][oldj].drawCell(); // Set the previous standing cell back to default
            oldi = i;
            oldj = j;

            cell[i][j].drawCell(); // Set the current standing cell
            cell[i][j].isStopped = false;
        }

        switch (getConsoleInput())
        {
        case 1:
        {
            if (i == 1)
                i = easyHeight;
            else
                i--;
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
            // If a cell is valid and not selected
            if (!cell[i][j].isSelected && cell[i][j].isValid)
            {
                cell[i][j].isSelected = true;
                cell[i][j].isValid = false;
                cell[i][j].isStopped = true;

                if (selectedCount == 2) // Save the location of the first selected
                {
                    iselected = i;
                    jselected = j;
                }
                selectedCount--;
                if (selectedCount == 0)
                {
                    processSelectedCell(cell, i, j, iselected, jselected, deletedCount);
                    if (deletedCount == 28)
                        break; // return;
                    selectedCount = 2;
                }
            }
            else if (cell[i][j].isSelected && !cell[i][j].isValid) // If a selected cell is selected again --> unselected
            {
                cell[i][j].isSelected = false;
                cell[i][j].isValid = true;
                cell[i][j].isStopped = true;
                selectedCount = 2;
            }
            break;
        }
        case 6:
        {
            showMoveSuggestion(cell);
            break;
        }
        case 7:
            return;
        default:
            break;
        }
    }
}

void easyMode(Player& p)
{
    srand(time(0));
    Board_1** board = new Board_1 * [gameHeight];
    do
    {
        generateBoard(board);
    } while (!checkValidBoard(board));
    displayBoard(board);
    processAction(board);
    deleteBoard(board);
}
