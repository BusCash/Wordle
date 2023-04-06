#include "HardMode.h"

void addTail(Board_2*& head, Board_2* newnode)
{
	if (head == NULL)
	{
		head = newnode;
	}
	else
	{
		Board_2* curnode = head;
		while (curnode->next != NULL)
			curnode = curnode->next;
		curnode->next = newnode;
	}
}

Board_2* findNode(Board_2** board, int i, int j, int hardHeight, int hardWidth)
{
	int boardHardHeight = hardHeight + 2,
		boardHardWidth = hardWidth + 2;

	if (i >= 0 && i < boardHardHeight && j >= 0 && j < boardHardWidth)
	{
		Board_2* curnode = board[i];
		while (curnode != NULL)
		{
			if (curnode->cj == j)
				return curnode;
			curnode = curnode->next;
		}
	}
	return NULL;
}

void generateBoard(Board_2** board, int hardHeight, int hardWidth)
{
	int boardHardHeight = hardHeight + 2,
		boardHardWidth = hardWidth + 2;

	for (int i = 0; i < boardHardHeight; i++)
	{
		board[i] = NULL;
		for (int j = 0; j < boardHardWidth; j++)
		{
			Board_2* newnode = new Board_2;
			newnode->next = NULL;

			// Set the position for the cell
			newnode->x = j * cellWidth + midWidth - (boardHardWidth * cellWidth - 1) / 2;
			newnode->y = i * (cellHeight + 1) + midHeight + 2 - (boardHardHeight * (cellHeight + 1) - 1) / 2;

			// Set the order for the cell
			newnode->ci = i;
			newnode->cj = j;

			// Set the position for the character
			newnode->cx = newnode->x + 2;
			newnode->cy = newnode->y + 1;

			addTail(board[i], newnode);
		}
	}

	// Set the edge unavailable
	for (int i = 0; i < boardHardHeight; i++)
	{
		findNode(board, i, 0, hardHeight, hardWidth)->isValid = false;
		findNode(board, i, boardHardWidth - 1, hardHeight, hardWidth)->isValid = false;
	}
	for (int j = 1; j < boardHardWidth - 1; j++)
	{
		findNode(board, 0, j, hardHeight, hardWidth)->isValid = false;
		findNode(board, boardHardHeight - 1, j, hardHeight, hardWidth)->isValid = false;
	}

	// Get random character for each 2 cells
	int charNum = hardHeight * hardWidth / 2;
	while (charNum)
	{
		int time = 2;
		char c = 65 + rand() % 26;
		while (time)
		{
			int row = rand() % hardHeight + 1, col = rand() % hardWidth + 1;
			if (findNode(board, row, col, hardHeight, hardWidth)->c == ' ')
			{
				findNode(board, row, col, hardHeight, hardWidth)->c = c;
				time--;
			}
		}
		charNum--;
	}
}

void deleteBoard(Board_2** board, int hardHeight)
{
	int boardHardHeight = hardHeight + 2;
	if (board != NULL)
	{
		for (int i = 0; i < boardHardHeight; i++)
		{
			Board_2* nextnode = board[i];
			while (board[i] != NULL)
			{
				nextnode = board[i]->next;
				delete board[i];
				board[i] = nextnode;
			}
		}
		delete[] board;
	}
}

void displayBoard(Board_2** board, int delaytime, int hardHeight, int hardWidth)
{

	for (int i = 1; i < hardHeight + 1; i++)
	{
		Board_2* curnode = board[i];
		while (curnode->next != NULL)
		{
			curnode->drawCell(hardHeight, hardWidth);
			Sleep(delaytime);

			curnode = curnode->next;
		}
	}
}

bool checkRowMatch(Board_2** board, int j1, int j2, int i, int hardHeight, int hardWidth)
{
	for (int j = min(j1, j2) + 1; j < max(j1, j2); j++)
		if (findNode(board, i, j, hardHeight, hardWidth)->c != ' ')
			return false;
	return true;
}

bool checkColMatch(Board_2** board, int i1, int i2, int j, int hardHeight, int hardWidth)
{
	for (int i = min(i1, i2) + 1; i < max(i1, i2); i++)
		if (findNode(board, i, j, hardHeight, hardWidth)->c != ' ')
			return false;
	return true;
}

bool checkIMatch(Board_2** board, int i1, int j1, int i2, int j2, int type, int hardHeight, int hardWidth)
{
	int boardHardHeight = hardHeight + 2,
		boardHardWidth = hardWidth + 2;
	if (j1 == j2)
	{
		if (checkColMatch(board, i1, i2, j1, hardHeight, hardWidth))
		{
			if (type == 0)
			{
				findNode(board, i1, j1, hardHeight, hardWidth)->drawArrow(findNode(board, i2, j1, hardHeight, hardWidth)->cx, findNode(board, i2, j1, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
				Sleep(200);

				for (int i = min(i1, i2) + 1; i < max(i1, i2); i++)
					findNode(board, i, j1, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
			}

			return true;
		}
	}
	else if (i1 == i2)
	{
		if (checkRowMatch(board, j1, j2, i1, hardHeight, hardWidth))
		{
			if (type == 0)
			{
				findNode(board, i1, j1, hardHeight, hardWidth)->drawArrow(findNode(board, i1, j2, hardHeight, hardWidth)->cx, findNode(board, i1, j2, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
				Sleep(200);

				for (int j = min(j1, j2) + 1; j < max(j1, j2); j++)
					findNode(board, i1, j, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
			}

			return true;
		}
	}
	return false;
}

bool checkLMatch(Board_2** board, int i1, int j1, int i2, int j2, int type, int hardHeight, int hardWidth)
{
	int boardHardHeight = hardHeight + 2,
		boardHardWidth = hardWidth + 2;

	// Check 2 corners created by those points 
	//	-> If through
	//	-> Check the 2 lines created by that corner to those points

	if (findNode(board, i1, j2, hardHeight, hardWidth)->c == ' ')
		if (checkRowMatch(board, j1, j2, i1, hardHeight, hardWidth) && checkColMatch(board, i1, i2, j2, hardHeight, hardWidth))
		{
			if (type == 0)
			{
				findNode(board, i1, j1, hardHeight, hardWidth)->drawArrow(findNode(board, i1, j2, hardHeight, hardWidth)->cx, findNode(board, i1, j2, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
				findNode(board, i1, j2, hardHeight, hardWidth)->drawArrow(findNode(board, i2, j2, hardHeight, hardWidth)->cx, findNode(board, i2, j2, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
				Sleep(200);

				for (int j = min(j1, j2); j <= max(j1, j2); j++)
					findNode(board, i1, j, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
				for (int i = min(i1, i2); i <= max(i1, i2); i++)
					findNode(board, i, j2, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
			}

			return true;
		}

	if (findNode(board, i2, j1, hardHeight, hardWidth)->c == ' ')
		if (checkRowMatch(board, j1, j2, i2, hardHeight, hardWidth) && checkColMatch(board, i1, i2, j1, hardHeight, hardWidth))
		{
			if (type == 0)
			{
				findNode(board, i2, j2, hardHeight, hardWidth)->drawArrow(findNode(board, i2, j1, hardHeight, hardWidth)->cx, findNode(board, i2, j1, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
				findNode(board, i2, j1, hardHeight, hardWidth)->drawArrow(findNode(board, i1, j1, hardHeight, hardWidth)->cx, findNode(board, i1, j1, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
				Sleep(200);

				for (int j = min(j2, j1); j <= max(j2, j1); j++)
					findNode(board, i2, j, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
				for (int i = min(i2, i1); i <= max(i2, i1); i++)
					findNode(board, i, j1, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
			}

			return true;
		}
	return false;
}

bool checkZMatch(Board_2** board, int i1, int j1, int i2, int j2, int type, int hardHeight, int hardWidth)
{
	int boardHardHeight = hardHeight + 2,
		boardHardWidth = hardWidth + 2;

	// Check all way in a rectangle created by p1 and p2
	// Find the point has min j and the point has min i

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
		if (checkRowMatch(board, jmin.y, j + 1, jmin.x, hardHeight, hardWidth))
		{
			int jmax_x;
			if (jmax.x > jmin.x)
				jmax_x = jmax.x + 1;
			else
				jmax_x = jmax.x - 1;
			if (checkColMatch(board, jmin.x, jmax_x, j, hardHeight, hardWidth) && checkRowMatch(board, j, jmax.y, jmax.x, hardHeight, hardWidth))
			{
				if (type == 0)
				{
					findNode(board, jmin.x, jmin.y, hardHeight, hardWidth)->drawArrow(findNode(board, jmin.x, j, hardHeight, hardWidth)->cx, findNode(board, jmin.x, j, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					findNode(board, jmin.x, j, hardHeight, hardWidth)->drawArrow(findNode(board, jmax.x, j, hardHeight, hardWidth)->cx, findNode(board, jmax.x, j, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					findNode(board, jmax.x, j, hardHeight, hardWidth)->drawArrow(findNode(board, jmax.x, jmax.y, hardHeight, hardWidth)->cx, findNode(board, jmax.x, jmax.y, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					Sleep(200);

					for (int jd = jmin.y + 1; jd < j; jd++)
						findNode(board, jmin.x, jd, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
					for (int id = min(jmin.x, jmax.x); id <= max(jmin.x, jmax.x); id++)
						findNode(board, id, j, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
					for (int jd = j; jd < jmax.y; jd++)
						findNode(board, jmax.x, jd, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
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
		if (checkColMatch(board, imin.x, i + 1, imin.y, hardHeight, hardWidth))
		{
			int imax_y;
			if (imax.y > imin.y)
				imax_y = imax.y + 1;
			else
				imax_y = imax.y - 1;
			if (checkRowMatch(board, imin.y, imax_y, i, hardHeight, hardWidth) && checkColMatch(board, i, imax.x, imax.y, hardHeight, hardWidth))
			{
				if (type == 0)
				{
					findNode(board, imin.x, imin.y, hardHeight, hardWidth)->drawArrow(findNode(board, i, imin.y, hardHeight, hardWidth)->cx, findNode(board, i, imin.y, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					findNode(board, i, imin.y, hardHeight, hardWidth)->drawArrow(findNode(board, i, imax.y, hardHeight, hardWidth)->cx, findNode(board, i, imax.y, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					findNode(board, imax.x, imax.y, hardHeight, hardWidth)->drawArrow(findNode(board, i, imax.y, hardHeight, hardWidth)->cx, findNode(board, i, imax.y, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					Sleep(200);

					for (int id = imin.x + 1; id < i; id++)
						findNode(board, id, imin.y, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
					for (int jd = min(imin.y, imax.y); jd <= max(imin.y, imax.y); jd++)
						findNode(board, i, jd, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
					for (int id = i + 1; id < imax.x; id++)
						findNode(board, id, imax.y, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
				}

				return true;
			}
		}

	return false;
}

bool checkUMatch(Board_2** board, int i1, int j1, int i2, int j2, int type, int hardHeight, int hardWidth)
{
	int boardHardHeight = hardHeight + 2,
		boardHardWidth = hardWidth + 2;

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
	if (checkRowMatch(board, jmin.y, jmax.y + 1, jmin.x, hardHeight, hardWidth))
	{
		int jnext = jmax.y + downright;
		while (jnext <= hardWidth + 1 && findNode(board, jmin.x, jnext, hardHeight, hardWidth)->c == ' ' && findNode(board, jmax.x, jnext, hardHeight, hardWidth)->c == ' ')
		{
			if (checkColMatch(board, jmin.x, jmax.x, jnext, hardHeight, hardWidth))
			{
				if (type == 0)
				{
					findNode(board, jmin.x, jnext, hardHeight, hardWidth)->drawArrow(findNode(board, jmax.x, jnext, hardHeight, hardWidth)->cx, findNode(board, jmax.x, jnext, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					findNode(board, jmin.x, jmin.y, hardHeight, hardWidth)->drawArrow(findNode(board, jmin.x, jnext, hardHeight, hardWidth)->cx, findNode(board, jmin.x, jnext, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					findNode(board, jmax.x, jmax.y, hardHeight, hardWidth)->drawArrow(findNode(board, jmax.x, jnext, hardHeight, hardWidth)->cx, findNode(board, jmax.x, jnext, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					Sleep(200);

					for (int i = min(jmin.x, jmax.x); i <= max(jmin.x, jmax.x); i++)
						findNode(board, i, jnext, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
					for (int j = jmin.y + 1; j < jnext; j++)
						findNode(board, jmin.x, j, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
					for (int j = jmax.y + 1; j < jnext; j++)
						findNode(board, jmax.x, j, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
				}

				return true;
			}
			jnext += downright;
		}
	}

	// Check left direction
	if (checkRowMatch(board, jmax.y, jmin.y - 1, jmax.x, hardHeight, hardWidth))
	{
		int jnext = jmin.y + upleft;
		while (jnext >= 0 && findNode(board, jmin.x, jnext, hardHeight, hardWidth)->c == ' ' && findNode(board, jmax.x, jnext, hardHeight, hardWidth)->c == ' ')
		{
			if (checkColMatch(board, jmin.x, jmax.x, jnext, hardHeight, hardWidth))
			{
				if (type == 0)
				{
					findNode(board, jmin.x, jnext, hardHeight, hardWidth)->drawArrow(findNode(board, jmax.x, jnext, hardHeight, hardWidth)->cx, findNode(board, jmax.x, jnext, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					findNode(board, jmin.x, jmin.y, hardHeight, hardWidth)->drawArrow(findNode(board, jmin.x, jnext, hardHeight, hardWidth)->cx, findNode(board, jmin.x, jnext, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					findNode(board, jmax.x, jmax.y, hardHeight, hardWidth)->drawArrow(findNode(board, jmax.x, jnext, hardHeight, hardWidth)->cx, findNode(board, jmax.x, jnext, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					Sleep(200);

					for (int i = min(jmin.x, jmax.x); i <= max(jmin.x, jmax.x); i++)
						findNode(board, i, jnext, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
					for (int j = jnext + 1; j < jmin.y; j++)
						findNode(board, jmin.x, j, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
					for (int j = jnext + 1; j < jmax.y; j++)
						findNode(board, jmax.x, j, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
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
	if (checkColMatch(board, imin.x, imax.x + 1, imin.y, hardHeight, hardWidth))
	{
		int inext = imax.x + downright;
		while (inext <= hardHeight + 1 && findNode(board, inext, imin.y, hardHeight, hardWidth)->c == ' ' && findNode(board, inext, imax.y, hardHeight, hardWidth)->c == ' ')
		{
			if (checkRowMatch(board, imin.y, imax.y, inext, hardHeight, hardWidth))
			{
				if (type == 0)
				{
					findNode(board, imin.x, imin.y, hardHeight, hardWidth)->drawArrow(findNode(board, inext, imin.y, hardHeight, hardWidth)->cx, findNode(board, inext, imin.y, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					findNode(board, imax.x, imax.y, hardHeight, hardWidth)->drawArrow(findNode(board, inext, imax.y, hardHeight, hardWidth)->cx, findNode(board, inext, imax.y, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					findNode(board, inext, imin.y, hardHeight, hardWidth)->drawArrow(findNode(board, inext, imax.y, hardHeight, hardWidth)->cx, findNode(board, inext, imax.y, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					Sleep(200);

					for (int i = imin.x + 1; i < inext; i++)
						findNode(board, i, imin.y, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
					for (int i = imax.x + 1; i < inext; i++)
						findNode(board, i, imax.y, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
					for (int j = min(imin.y, imax.y); j <= max(imin.y, imax.y); j++)
						findNode(board, inext, j, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
				}

				return true;
			}
			inext += downright;
		}
	}

	// Check up direction
	if (checkColMatch(board, imax.x, imin.x - 1, imax.y, hardHeight, hardWidth))
	{
		int inext = imin.x + upleft;
		while (inext >= 0 && findNode(board, inext, imin.y, hardHeight, hardWidth)->c == ' ' && findNode(board, inext, imax.y, hardHeight, hardWidth)->c == ' ')
		{
			if (checkRowMatch(board, imin.y, imax.y, inext, hardHeight, hardWidth))
			{
				if (type == 0)
				{
					findNode(board, imin.x, imin.y, hardHeight, hardWidth)->drawArrow(findNode(board, inext, imin.y, hardHeight, hardWidth)->cx, findNode(board, inext, imin.y, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					findNode(board, imax.x, imax.y, hardHeight, hardWidth)->drawArrow(findNode(board, inext, imax.y, hardHeight, hardWidth)->cx, findNode(board, inext, imax.y, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					findNode(board, inext, imin.y, hardHeight, hardWidth)->drawArrow(findNode(board, inext, imax.y, hardHeight, hardWidth)->cx, findNode(board, inext, imax.y, hardHeight, hardWidth)->cy, i1, j1, i2, j2, boardHardHeight, boardHardWidth);
					Sleep(200);

					for (int i = inext + 1; i < imin.x; i++)
						findNode(board, i, imin.y, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
					for (int i = inext + 1; i < imax.x; i++)
						findNode(board, i, imax.y, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
					for (int j = min(imin.y, imax.y); j <= max(imin.y, imax.y); j++)
						findNode(board, inext, j, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
				}

				return true;
			}
			inext += upleft;
		}
	}

	return false;
}

bool checkMatch(Board_2** board, int i1, int j1, int i2, int j2, int type, int hardHeight, int hardWidth) // type 0: check player choice, 1: check valid board
{
	if (findNode(board, i1, j1, hardHeight, hardWidth)->c == findNode(board, i2, j2, hardHeight, hardWidth)->c)
	{
		if (checkIMatch(board, i1, j1, i2, j2, type, hardHeight, hardWidth))
			return true;

		else if (checkLMatch(board, i1, j1, i2, j2, type, hardHeight, hardWidth))
			return true;

		else if (checkZMatch(board, i1, j1, i2, j2, type, hardHeight, hardWidth))
			return true;

		else if (checkUMatch(board, i1, j1, i2, j2, type, hardHeight, hardWidth))
			return true;
	}
	return false;
}

void moveCell(Board_2** board, int i, int j, int hardWidth)
{
	if (j == 11)
		return;

	Board_2* curnode = board[i]->next;
	while (curnode->c != ' ')
		curnode = curnode->next;

	Board_2* nextnode = curnode->next;
	while (nextnode->cj != hardWidth + 1)
	{
		while (nextnode->c == ' ')
		{
			nextnode = nextnode->next;
			if (nextnode->cj == hardWidth + 1)
			{
				while (curnode->cj != hardWidth + 1)
				{
					curnode->isValid = false;
					curnode = curnode->next;
				}
				return;
			}
		}

		if (!curnode->isValid)
			curnode->isValid = true;
		swap(curnode->c, nextnode->c);

		curnode = curnode->next;
		curnode->isValid = false;

		nextnode = nextnode->next;
	}
}

bool checkValidBoard(Board_2** board, int hardHeight, int hardWidth)
{
	char check = 'A';
	while (check >= 'A' && check <= 'Z')
	{
		int cnt = 0;
		int pos[66];
		for (int i = 1; i < hardHeight + 1; i++)
		{
			for (int j = 1; j < hardWidth + 1; j++)
			{
				if (findNode(board, i, j, hardHeight, hardWidth)->c == check && findNode(board, i, j, hardHeight, hardWidth)->isValid) // Save all the check character positions in pos arr
				{
					pos[cnt++] = i;
					pos[cnt++] = j;
				}
			}
		}
		for (int i = 0; i < cnt - 2; i += 2) // Pos arr stores the pos of 1 char in i and i+1;
		{
			for (int j = i + 2; j < cnt; j += 2)
				if (checkMatch(board, pos[i], pos[i + 1], pos[j], pos[j + 1], 1, hardHeight, hardWidth)) // Check if there are any ways lefts
					return true;
		}
		check++;
	}
	return false;
}

void resetPlayingBoard(Board_2** board, int hardHeight, int hardWidth)
{
	for (int i = 1; i < hardHeight + 1; i++)
		for (int j = 1; j < hardWidth + 1; j++)
			findNode(board, i, j, hardHeight, hardWidth)->isValid = true;

	int restCount = (hardHeight * hardWidth) / 2;
	while (restCount)
	{
		int time = 2;
		char c = 65 + rand() % 26;
		while (time)
		{
			int i = rand() % hardHeight + 1, j = rand() % hardWidth + 1;
			if (findNode(board, i, j, hardHeight, hardWidth)->c == ' ')
			{
				findNode(board, i, j, hardHeight, hardWidth)->c = c;
				time--;
			}
		}
		restCount--;
	}
}

void showMoveSuggestion(Board_2** cell, int inow, int jnow, int hardHeight, int hardWidth)
{
	char check = 'A';
	while (check >= 'A' && check <= 'Z')
	{
		int cnt = 0;
		int pos[66];

		for (int i = 1; i < hardHeight + 1; i++)
		{
			for (int j = 1; j < hardWidth + 1; j++)
			{
				if (findNode(cell, i, j, hardHeight, hardWidth)->c == check && findNode(cell, i, j, hardHeight, hardWidth)->isValid)
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
				if (checkMatch(cell, pos[i], pos[i + 1], pos[j], pos[j + 1], 1, hardHeight, hardWidth)) // Find 2 match cell -> show it 0,2s
				{
					findNode(cell, pos[i], pos[i + 1], hardHeight, hardWidth)->isHint = true;
					findNode(cell, pos[j], pos[j + 1], hardHeight, hardWidth)->isHint = true;
					findNode(cell, pos[i], pos[i + 1], hardHeight, hardWidth)->drawCell(hardHeight, hardWidth);
					findNode(cell, pos[j], pos[j + 1], hardHeight, hardWidth)->drawCell(hardHeight, hardWidth);

					playSound(2);
					Sleep(200);

					findNode(cell, pos[i], pos[i + 1], hardHeight, hardWidth)->isHint = false;
					findNode(cell, pos[j], pos[j + 1], hardHeight, hardWidth)->isHint = false;
					findNode(cell, pos[i], pos[i + 1], hardHeight, hardWidth)->drawCell(hardHeight, hardWidth);
					findNode(cell, pos[j], pos[j + 1], hardHeight, hardWidth)->drawCell(hardHeight, hardWidth);

					if (pos[i] == inow && pos[i + 1] == jnow)
						findNode(cell, pos[i], pos[i + 1], hardHeight, hardWidth)->isStopped = true;
					else if (pos[j] == inow && pos[j + 1] == jnow)
						findNode(cell, pos[j], pos[j + 1], hardHeight, hardWidth)->isStopped = true;

					return;
				}
			}
		}
		check++;
	}
}

int processSelectedHardCell(Player* p, int i, int j, int iselected, int jselected, int& deletedCount, int hardHeight, int hardWidth)
{
	findNode(p->hboard, i, j, hardHeight, hardWidth)->drawCell(hardHeight, hardWidth); // Set the selected cell;
	Sleep(200);

	findNode(p->hboard, iselected, jselected, hardHeight, hardWidth)->isSelected = false;
	findNode(p->hboard, i, j, hardHeight, hardWidth)->isSelected = false;

	int check = 0;

	if (checkMatch(p->hboard, iselected, jselected, i, j, 0, hardHeight, hardWidth)) // If match -> delete cell
	{
		if (p->hard.streak < 5)
			playSound(5);
		else if (p->hard.streak < 8)
			playSound(6);
		else if (p->hard.streak < 10)
			playSound(7);
		else if (p->hard.streak < 13)
			playSound(8);
		else
			playSound(9);

		findNode(p->hboard, iselected, jselected, hardHeight, hardWidth)->c = ' ';
		findNode(p->hboard, i, j, hardHeight, hardWidth)->c = ' ';

		findNode(p->hboard, iselected, jselected, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);
		findNode(p->hboard, i, j, hardHeight, hardWidth)->deleteCell(7, hardHeight, hardWidth);

		moveCell(p->hboard, iselected, jselected, hardWidth);
		moveCell(p->hboard, i, j, hardWidth);

		displayBoard(p->hboard, 0, hardHeight, hardWidth);

		deletedCount += 2;

		if (!checkValidBoard(p->hboard, hardHeight, hardWidth) && deletedCount != hardHeight * hardWidth)
			return -1;

		check = 1;
	}
	else
	{
		playSound(4);
		findNode(p->hboard, iselected, jselected, hardHeight, hardWidth)->isValid = true;
		findNode(p->hboard, i, j, hardHeight, hardWidth)->isValid = true;

		// Set the old selected cell back to default
		findNode(p->hboard, iselected, jselected, hardHeight, hardWidth)->drawCell(hardHeight, hardWidth);
	}

	// When done process -> set the current standing cell
	findNode(p->hboard, i, j, hardHeight, hardWidth)->isStopped = true;
	findNode(p->hboard, i, j, hardHeight, hardWidth)->drawCell(hardHeight, hardWidth);
	findNode(p->hboard, i, j, hardHeight, hardWidth)->isStopped = false;

	return check;
}

void processHardPoint(Player* p)
{
	if (p->hard.streak == 0)
		return;
	if (p->hard.streak < 5)
		p->hard.point += 5;
	else if (p->hard.streak < 8)
		p->hard.point += 5 * p->hard.streak;
	else if (p->hard.streak < 10)
		p->hard.point += 15 * p->hard.streak;
	else if (p->hard.streak == 10)
		p->hard.point += 15 * p->hard.streak + 500;
	else if (p->hard.streak < 14)
		p->hard.point += (5 + p->hard.streak) * p->hard.streak + (p->hard.streak - 5) * 100;
	else
		p->hard.point += (5 + p->hard.streak) * p->hard.streak + 1005;
}

bool processAction(Board_2** cell, Player* p, int hardHeight, int hardWidth)
{
	int i = 1, j = 1;
	int oldi = i, oldj = j;

	int iselected = 0, jselected = 0;
	int selectedCount = 2;
	int deletedCount = 0;
	bool win = true;

	findNode(cell, i, j, hardHeight, hardWidth)->isStopped = true;

	while (true)
	{
		if (findNode(cell, i, j, hardHeight, hardWidth)->isStopped)
		{
			findNode(cell, oldi, oldj, hardHeight, hardWidth)->drawCell(hardHeight, hardWidth); // Set the previous standing cell back to default
			oldi = i;
			oldj = j;

			findNode(cell, i, j, hardHeight, hardWidth)->drawCell(hardHeight, hardWidth); // Set the current standing cell
			findNode(cell, i, j, hardHeight, hardWidth)->isStopped = false;
		}

		// If the game is completed
		if (deletedCount == hardHeight * hardWidth)
		{
			findNode(cell, i, j, hardHeight, hardWidth)->drawCell(hardHeight, hardWidth);
			Sleep(1500);
			clearConsole();
			if (!win)
			{
				setColor(12);
				gotoxy(midWidth - 10, midHeight + 2);
				cout << "YOU LOSE, CHICKEN!!!";
				setColor(7);
				switch (generateMenu(midWidth - 12, midHeight + 6, "21,23", "RESTART,BACK TO MAIN MENU", 2))
				{
				case 0:
					p->hard.isPlaying = false;
					deleteBoard(p->hboard, hardHeight);
					clearConsole();
					return false;
				case 1:
					p->hard.isPlaying = false;
					deleteBoard(p->hboard, hardHeight);
					return true;
				}
			}
			else
			{
				p->hard.isFinised = true;
				switch (generateMenu(midWidth - 12, midHeight + 6, "21,23,25,27", "CONTINUE WITH CURRENT SCORE,RESTART WITH NEW SCORE,SAVE AND MAIN MENU,JUST QUIT", 4))
				{
				case 0: // If quit and don't save
					p->hard.isPlaying = false;
					deleteBoard(p->hboard, hardHeight);
					clearConsole();
					return false;
				case 1: // If continue playing with the current parameter
					p->hard.isPlaying = true;
					return true;
				case 2: // If continue playing with new parameter
					p->hard.isPlaying = false;
					deleteBoard(p->hboard, hardHeight);
					return true;
				case 3: // If quit and save parameter
					p->hard.isPlaying = true;
					clearConsole();
					return false;
				}

			}
		}

		switch (getConsoleInput()) // Take input from keyboard
		{
		case 1: // UP
		{
			if (i == 1)
				i = hardHeight;
			else
				i--;
			findNode(cell, i, j, hardHeight, hardWidth)->isStopped = true;
			break;
		}
		case 2: // DOWN
		{
			if (i == hardHeight)
				i = 1;
			else
				i += 1;
			findNode(cell, i, j, hardHeight, hardWidth)->isStopped = true;
			break;
		}
		case 3: // LEFT
		{
			if (j == 1)
				j = hardWidth;
			else
				j -= 1;
			findNode(cell, i, j, hardHeight, hardWidth)->isStopped = true;
			break;
		}
		case 4: // RIGHT
		{
			if (j == hardWidth)
				j = 1;
			else
				j += 1;
			findNode(cell, i, j, hardHeight, hardWidth)->isStopped = true;
			break;
		}
		case 5:
		{
			// If a cell is valid and not selected
			if (!findNode(cell, i, j, hardHeight, hardWidth)->isSelected && findNode(cell, i, j, hardHeight, hardWidth)->isValid)
			{
				findNode(cell, i, j, hardHeight, hardWidth)->isSelected = true;
				findNode(cell, i, j, hardHeight, hardWidth)->isValid = false;
				findNode(cell, i, j, hardHeight, hardWidth)->isStopped = true;

				if (selectedCount == 2) // Save the location of the first selected
				{
					iselected = i;
					jselected = j;
				}
				selectedCount--;

				if (selectedCount == 0) // If 2 cells are selected -> check match
				{
					selectedCount = 2;
					int checkselectecd = processSelectedHardCell(p, i, j, iselected, jselected, deletedCount, hardHeight, hardWidth);
					if (checkselectecd == 1)
						p->hard.streak++;
					else if (checkselectecd == 0)
						p->hard.streak = 0;
					else
					{
						deletedCount = hardHeight * hardWidth;
						win = false;
					}
					processHardPoint(p);
					if (p->hard.point > p->hard.maxpoint)
						p->hard.maxpoint = p->hard.point;
				}
			}
			else if (findNode(cell, i, j, hardHeight, hardWidth)->isSelected && !findNode(cell, i, j, hardHeight, hardWidth)->isValid) // If a selected cell is selected again -> unselected
			{
				findNode(cell, i, j, hardHeight, hardWidth)->isSelected = false;
				findNode(cell, i, j, hardHeight, hardWidth)->isValid = true;
				findNode(cell, i, j, hardHeight, hardWidth)->isStopped = true;
				selectedCount = 2;
			}
			else if (!findNode(cell, i, j, hardHeight, hardWidth)->isSelected && !findNode(cell, i, j, hardHeight, hardWidth)->isValid) // If an unvalid cell is selected
			{
				PlaySound(NULL, NULL, 0);
				playSound(3);
			}
			break;
		}
		case 6:
		{
			if (p->hard.hint)
			{
				showMoveSuggestion(cell, i, j, hardHeight, hardWidth);
				p->hard.hint--;
			}
			break;
		}
		case 7: // If ESC is pressed
		{
			clearConsole();
			bool pause = true;
			while (pause)
			{
				switch (generateMenu(midWidth - 12, midHeight + 7, "22,24,26", "RESUME,RESTART,QUIT", 3))
				{
				case 0: // If QUIT is selected
					switch (generateMenu(midWidth - 12, midHeight + 7, "22,24,26", "SAVE,DON'T SAVE,BACK", 3))
					{
					case 0: // BACK
						break;
					case 1: // SAVE
						p->hard.isPlaying = true;
						return false;
					case 3: // DON'T SAVE
						p->hard.isPlaying = false;
						deleteBoard(p->hboard, hardHeight);
						return false;
					}
					break;
				case 1: // If RESUME -> go back
					pause = false;
					findNode(cell, i, j, hardHeight, hardWidth)->isStopped = true;
					displayBoard(p->hboard, 0, hardHeight, hardWidth);
					showParameter(p, "hard");
					break;
				case 3: // If RESTART -> delete
					p->hard.isPlaying = false;
					deleteBoard(p->hboard, hardHeight);
					return true;
				}
			}
			break;
		}
		default:
			break;
		}

		showParameter(p, "hard");
	}
}

void hardMode(Player* p, int& hardHeight, int& hardWidth)
{

	while (true)
	{
		if (!p->hard.isPlaying)
		{
			clearConsole();
			setColor(12);
			gotoxy(midWidth - 14, midHeight + 5);
			cout << "THE TOTAL CELLS MUST BE EVEN";
			gotoxy(midWidth - 13, midHeight + 6);
			cout << "ROWS MUST BE SMALLER THAN 7";
			gotoxy(midWidth - 15, midHeight + 7);
			cout << "COLUMNS MUST BE SMALLER THAN 12";
			setColor(11);
			gotoxy(midWidth - 8, midHeight - 5);
			cout << "ENTER BOARD SIZE";

			gotoxy(midWidth - 11, midHeight - 3);
			cout << "ROWS (RECOMMENDED: 6): ";
			gotoxy(midWidth - 1, midHeight - 2);
			cin >> hardHeight;
			gotoxy(midWidth - 13, midHeight - 1);
			cout << "COLUMNS (RECOMMENDED: 11): ";
			gotoxy(midWidth - 1, midHeight);
			cin >> hardWidth;
			if (hardHeight * hardWidth % 2 == 0)
			{
				if (hardHeight < 7 && hardHeight >0 && hardWidth < 12 && hardWidth >0)
					break;
				else
				{
					gotoxy(midWidth - 3, midHeight + 2);
					cout << "ERROR!";
				}
			}
			else
			{
				gotoxy(midWidth - 3, midHeight + 2);
				cout << "ERROR!";
			}
			setColor(7);
		}
		else
		{
			bool check = true;
			setColor(11);
			gotoxy(midWidth - 15, midHeight);
			cout << "DO YOU WANT TO CHOOSE NEW SIZE";
			switch (generateMenu(midWidth - 12, midHeight + 6, "21,23", "YES,NO", 2))
			{
			case 0:
				break;
			case 1:
				p->hard.isPlaying = false;
				deleteBoard(p->hboard, hardHeight);
				check = false;
				break;
			}
			clearConsole();
			if (check)
				break;
		}
	}


	int boardHardHeight = hardHeight + 2,
		boardHardWidth = hardWidth + 2;
	srand(time(NULL));
	// If player want to continue playing
	do
	{
		// Check if the board is being played or not
		if (!p->hard.isPlaying) // If no -> reset new board
		{
			clearConsole();
			p->hard.streak = 0;
			p->hard.point = 0;
			p->hard.hint = 2;
			do
			{
				p->hboard = new Board_2 * [boardHardHeight];
				generateBoard(p->hboard, hardHeight, hardWidth);
				if (!checkValidBoard(p->hboard, hardHeight, hardWidth))
					deleteBoard(p->hboard, hardHeight);
			} while (!checkValidBoard(p->hboard, hardHeight, hardWidth));
		}
		else // If yes -> check if the board is finished
		{
			if (p->hard.isFinised) // If yes -> reset new board
			{
				clearConsole();
				do
				{
					resetPlayingBoard(p->hboard, hardHeight, hardWidth);
				} while (!checkValidBoard(p->hboard, hardHeight, hardWidth));
				p->hard.isFinised = false;
			}
		}
		displayBoard(p->hboard, 5, hardHeight, hardWidth);
		showParameter(p, "hard");
	} while (processAction(p->hboard, p, hardHeight, hardWidth));
}