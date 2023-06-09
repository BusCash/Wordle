#include "HardMode.h"

int hardHeight,
hardWidth,
boardHardHeight,
boardHardWidth;

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

Board_2* findNode(Board_2** board, int i, int j)
{
	// Check if the order are within the bounds of the game board
	if (i >= 0 && i < boardHardHeight && j >= 0 && j < boardHardWidth)
	{
		Board_2* curnode = board[i];
		while (j > 0)
		{
			curnode = curnode->next;
			j--;
		}
		return curnode;
	}
	return NULL;
}

void generateBoard(Board_2** board)
{
	for (int i = 0; i < boardHardHeight; i++)
	{
		board[i] = NULL;
		for (int j = 0; j < boardHardWidth; j++)
		{
			Board_2* newnode = new Board_2;
			newnode->next = NULL;

			// Set the position for the cell
			newnode->cell.x = j * cellWidth + midWidth - (boardHardWidth * cellWidth - 1) / 2;
			newnode->cell.y = i * (cellHeight + 1) + midHeight + 2 - (boardHardHeight * (cellHeight + 1) - 1) / 2;

			// Set the position for the character
			newnode->character.x = newnode->cell.x + 2;
			newnode->character.y = newnode->cell.y + 1;

			// Add the node to the board
			addTail(board[i], newnode);
		}
	}

	// Set the board edge unavailable
	for (int i = 0; i < boardHardHeight; i++)
	{
		findNode(board, i, 0)->isValid = false;
		findNode(board, i, boardHardWidth - 1)->isValid = false;
	}
	for (int j = 1; j < boardHardWidth - 1; j++)
	{
		findNode(board, 0, j)->isValid = false;
		findNode(board, boardHardHeight - 1, j)->isValid = false;
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
			if (findNode(board, row, col)->c == ' ')
			{
				findNode(board, row, col)->c = c;
				time--;
			}
		}
		charNum--;
	}
}

void deleteBoard(Board_2** board)
{
	if (board != NULL)
	{
		for (int i = 0; i < boardHardHeight; i++)
		{
			for (Board_2* curnode = board[i]; board[i] != NULL; curnode = board[i])
			{
				board[i] = board[i]->next;
				delete curnode;
				curnode = NULL;
			}
		}
		delete[] board;
	}
}

void displayBoard(Board_2** board, int delaytime)
{
	for (int i = 1; i < hardHeight + 1; i++)
	{
		Board_2* curnode = board[i];
		while (curnode->next != NULL)
		{
			curnode->drawCell();
			Sleep(delaytime);

			curnode = curnode->next;
		}
	}
}

bool checkRowMatch(Board_2** board, int j1, int j2, int i)
{
	// Check if between 2 cells in a row is clear or if next to each other
	for (int j = min(j1, j2) + 1; j < max(j1, j2); j++)
		if (findNode(board, i, j)->c != ' ')
			return false;
	return true;
}

bool checkColMatch(Board_2** board, int i1, int i2, int j)
{
	// Check if between 2 cells in a column is clear or if next to each other
	for (int i = min(i1, i2) + 1; i < max(i1, i2); i++)
		if (findNode(board, i, j)->c != ' ')
			return false;
	return true;
}

bool checkIMatch(Board_2** board, int i1, int j1, int i2, int j2, int type)
{
	// Check if 2 cells are in the same row or collumn
	// If so, use the 2 functions above

	if (j1 == j2)
	{
		if (checkColMatch(board, i1, i2, j1))
		{
			if (type == 0)
			{
				// Show the arrow for 0,2 seconds
				findNode(board, i1, j1)->drawArrow(findNode(board, i2, j1)->character.x, findNode(board, i2, j1)->character.y, i1, j1, i2, j2);
				Sleep(200);

				for (int i = min(i1, i2) + 1; i < max(i1, i2); i++)
					findNode(board, i, j1)->deleteCell(7);
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
				// Show the arrow for 0,2 seconds
				findNode(board, i1, j1)->drawArrow(findNode(board, i1, j2)->character.x, findNode(board, i1, j2)->character.y, i1, j1, i2, j2);
				Sleep(200);

				for (int j = min(j1, j2) + 1; j < max(j1, j2); j++)
					findNode(board, i1, j)->deleteCell(7);
			}

			return true;
		}
	}
	return false;
}

bool checkLMatch(Board_2** board, int i1, int j1, int i2, int j2, int type)
{
	// Check 2 corners created by those cells 
	//	-> If the corners is clear
	//	-> Check the 2 lines from that corner to those cells

	if (findNode(board, i1, j2)->c == ' ')
		if (checkRowMatch(board, j1, j2, i1) && checkColMatch(board, i1, i2, j2))
		{
			if (type == 0)
			{
				// Show the arrow for 0,2 seconds
				findNode(board, i1, j1)->drawArrow(findNode(board, i1, j2)->character.x, findNode(board, i1, j2)->character.y, i1, j1, i2, j2);
				findNode(board, i1, j2)->drawArrow(findNode(board, i2, j2)->character.x, findNode(board, i2, j2)->character.y, i1, j1, i2, j2);
				Sleep(200);

				for (int j = min(j1, j2); j <= max(j1, j2); j++)
					findNode(board, i1, j)->deleteCell(7);
				for (int i = min(i1, i2); i <= max(i1, i2); i++)
					findNode(board, i, j2)->deleteCell(7);
			}

			return true;
		}

	if (findNode(board, i2, j1)->c == ' ')
		if (checkRowMatch(board, j1, j2, i2) && checkColMatch(board, i1, i2, j1))
		{
			if (type == 0)
			{
				// Show the arrow for 0,2 seconds
				findNode(board, i2, j2)->drawArrow(findNode(board, i2, j1)->character.x, findNode(board, i2, j1)->character.y, i1, j1, i2, j2);
				findNode(board, i2, j1)->drawArrow(findNode(board, i1, j1)->character.x, findNode(board, i1, j1)->character.y, i1, j1, i2, j2);
				Sleep(200);

				for (int j = min(j2, j1); j <= max(j2, j1); j++)
					findNode(board, i2, j)->deleteCell(7);
				for (int i = min(i2, i1); i <= max(i2, i1); i++)
					findNode(board, i, j1)->deleteCell(7);
			}

			return true;
		}
	return false;
}

bool checkZMatch(Board_2** board, int i1, int j1, int i2, int j2, int type)
{
	// Check all way in a rectangle created by p1 and p2
	// Find the cell has min j and the cell has min i to check

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
					// Show the arrow for 0,2 seconds
					findNode(board, jmin.x, jmin.y)->drawArrow(findNode(board, jmin.x, j)->character.x, findNode(board, jmin.x, j)->character.y, i1, j1, i2, j2);
					findNode(board, jmin.x, j)->drawArrow(findNode(board, jmax.x, j)->character.x, findNode(board, jmax.x, j)->character.y, i1, j1, i2, j2);
					findNode(board, jmax.x, j)->drawArrow(findNode(board, jmax.x, jmax.y)->character.x, findNode(board, jmax.x, jmax.y)->character.y, i1, j1, i2, j2);
					Sleep(200);

					for (int jd = jmin.y + 1; jd < j; jd++)
						findNode(board, jmin.x, jd)->deleteCell(7);
					for (int id = min(jmin.x, jmax.x); id <= max(jmin.x, jmax.x); id++)
						findNode(board, id, j)->deleteCell(7);
					for (int jd = j; jd < jmax.y; jd++)
						findNode(board, jmax.x, jd)->deleteCell(7);
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
					// Show the arrow for 0,2 seconds
					findNode(board, imin.x, imin.y)->drawArrow(findNode(board, i, imin.y)->character.x, findNode(board, i, imin.y)->character.y, i1, j1, i2, j2);
					findNode(board, i, imin.y)->drawArrow(findNode(board, i, imax.y)->character.x, findNode(board, i, imax.y)->character.y, i1, j1, i2, j2);
					findNode(board, imax.x, imax.y)->drawArrow(findNode(board, i, imax.y)->character.x, findNode(board, i, imax.y)->character.y, i1, j1, i2, j2);
					Sleep(200);

					for (int id = imin.x + 1; id < i; id++)
						findNode(board, id, imin.y)->deleteCell(7);
					for (int jd = min(imin.y, imax.y); jd <= max(imin.y, imax.y); jd++)
						findNode(board, i, jd)->deleteCell(7);
					for (int id = i + 1; id < imax.x; id++)
						findNode(board, id, imax.y)->deleteCell(7);
				}

				return true;
			}
		}

	return false;
}

bool checkUMatch(Board_2** board, int i1, int j1, int i2, int j2, int type)
{
	// Check if the line of the min pos cell and the cell in same line but have the max pos is clear
	// If so, check if the 2 next cells is clear
	// If so, check the line between those cells

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
		while (jnext <= hardWidth + 1 && findNode(board, jmin.x, jnext)->c == ' ' && findNode(board, jmax.x, jnext)->c == ' ')
		{
			if (checkColMatch(board, jmin.x, jmax.x, jnext))
			{
				if (type == 0)
				{
					// Show the arrow for 0,2 seconds
					findNode(board, jmin.x, jnext)->drawArrow(findNode(board, jmax.x, jnext)->character.x, findNode(board, jmax.x, jnext)->character.y, i1, j1, i2, j2);
					findNode(board, jmin.x, jmin.y)->drawArrow(findNode(board, jmin.x, jnext)->character.x, findNode(board, jmin.x, jnext)->character.y, i1, j1, i2, j2);
					findNode(board, jmax.x, jmax.y)->drawArrow(findNode(board, jmax.x, jnext)->character.x, findNode(board, jmax.x, jnext)->character.y, i1, j1, i2, j2);
					Sleep(200);

					for (int i = min(jmin.x, jmax.x); i <= max(jmin.x, jmax.x); i++)
						findNode(board, i, jnext)->deleteCell(7);
					for (int j = jmin.y + 1; j < jnext; j++)
						findNode(board, jmin.x, j)->deleteCell(7);
					for (int j = jmax.y + 1; j < jnext; j++)
						findNode(board, jmax.x, j)->deleteCell(7);
				}

				return true;
			}
			jnext += downright;
		}
	}

	// Check left direction
	if (checkRowMatch(board, jmax.y, jmin.y - 1, jmax.x))
	{
		int jnext = jmin.y + upleft;
		while (jnext >= 0 && findNode(board, jmin.x, jnext)->c == ' ' && findNode(board, jmax.x, jnext)->c == ' ')
		{
			if (checkColMatch(board, jmin.x, jmax.x, jnext))
			{
				if (type == 0)
				{
					// Show the arrow for 0,2 seconds
					findNode(board, jmin.x, jnext)->drawArrow(findNode(board, jmax.x, jnext)->character.x, findNode(board, jmax.x, jnext)->character.y, i1, j1, i2, j2);
					findNode(board, jmin.x, jmin.y)->drawArrow(findNode(board, jmin.x, jnext)->character.x, findNode(board, jmin.x, jnext)->character.y, i1, j1, i2, j2);
					findNode(board, jmax.x, jmax.y)->drawArrow(findNode(board, jmax.x, jnext)->character.x, findNode(board, jmax.x, jnext)->character.y, i1, j1, i2, j2);
					Sleep(200);

					for (int i = min(jmin.x, jmax.x); i <= max(jmin.x, jmax.x); i++)
						findNode(board, i, jnext)->deleteCell(7);
					for (int j = jnext + 1; j < jmin.y; j++)
						findNode(board, jmin.x, j)->deleteCell(7);
					for (int j = jnext + 1; j < jmax.y; j++)
						findNode(board, jmax.x, j)->deleteCell(7);
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
		while (inext <= hardHeight + 1 && findNode(board, inext, imin.y)->c == ' ' && findNode(board, inext, imax.y)->c == ' ')
		{
			if (checkRowMatch(board, imin.y, imax.y, inext))
			{
				if (type == 0)
				{
					// Show the arrow for 0,2 seconds
					findNode(board, imin.x, imin.y)->drawArrow(findNode(board, inext, imin.y)->character.x, findNode(board, inext, imin.y)->character.y, i1, j1, i2, j2);
					findNode(board, imax.x, imax.y)->drawArrow(findNode(board, inext, imax.y)->character.x, findNode(board, inext, imax.y)->character.y, i1, j1, i2, j2);
					findNode(board, inext, imin.y)->drawArrow(findNode(board, inext, imax.y)->character.x, findNode(board, inext, imax.y)->character.y, i1, j1, i2, j2);
					Sleep(200);

					for (int i = imin.x + 1; i < inext; i++)
						findNode(board, i, imin.y)->deleteCell(7);
					for (int i = imax.x + 1; i < inext; i++)
						findNode(board, i, imax.y)->deleteCell(7);
					for (int j = min(imin.y, imax.y); j <= max(imin.y, imax.y); j++)
						findNode(board, inext, j)->deleteCell(7);
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
		while (inext >= 0 && findNode(board, inext, imin.y)->c == ' ' && findNode(board, inext, imax.y)->c == ' ')
		{
			if (checkRowMatch(board, imin.y, imax.y, inext))
			{
				if (type == 0)
				{
					// Show the arrow for 0,2 seconds
					findNode(board, imin.x, imin.y)->drawArrow(findNode(board, inext, imin.y)->character.x, findNode(board, inext, imin.y)->character.y, i1, j1, i2, j2);
					findNode(board, imax.x, imax.y)->drawArrow(findNode(board, inext, imax.y)->character.x, findNode(board, inext, imax.y)->character.y, i1, j1, i2, j2);
					findNode(board, inext, imin.y)->drawArrow(findNode(board, inext, imax.y)->character.x, findNode(board, inext, imax.y)->character.y, i1, j1, i2, j2);
					Sleep(200);

					for (int i = inext + 1; i < imin.x; i++)
						findNode(board, i, imin.y)->deleteCell(7);
					for (int i = inext + 1; i < imax.x; i++)
						findNode(board, i, imax.y)->deleteCell(7);
					for (int j = min(imin.y, imax.y); j <= max(imin.y, imax.y); j++)
						findNode(board, inext, j)->deleteCell(7);
				}

				return true;
			}
			inext += upleft;
		}
	}

	return false;
}

bool checkMatch(Board_2** board, int i1, int j1, int i2, int j2, int type) // type 0: check player choice, 1: check valid board
{
	if (findNode(board, i1, j1)->c == findNode(board, i2, j2)->c)
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

void moveCell(Board_2** board, int i, int j)
{
	if (j == 11)
		return;

	// Find the first deleted cell from the left
	Board_2* curnode = board[i]->next;
	while (curnode->c != ' ')
		curnode = curnode->next;

	// Move each non-deleted cell behind the first deleted cell to the leftmost empty space
	Board_2* nextnode = curnode->next;
	while (nextnode->next != NULL)
	{
		while (nextnode->c == ' ')
		{
			nextnode = nextnode->next;

			// If there are no more non-deleted cells, deleted all the cell to the right
			if (nextnode->next == NULL)
			{
				while (curnode->next != NULL)
				{
					curnode->isValid = false;
					curnode = curnode->next;
				}
				return;
			}
		}

		// Swap the empty cell with the non-deleted cell and mark it as valid cell
		if (!curnode->isValid)
			curnode->isValid = true;
		swap(curnode->c, nextnode->c);

		curnode = curnode->next;
		curnode->isValid = false;

		nextnode = nextnode->next;
	}
}

bool checkValidBoard(Board_2** board)
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
				// Find the postion of cells have check character
				// Save all the positions in a pos array
				if (findNode(board, i, j)->c == check && findNode(board, i, j)->isValid)
				{
					pos[cnt++] = i;
					pos[cnt++] = j;
				}
			}
		}
		for (int i = 0; i < cnt - 2; i += 2) // Pos arr stores the position of 1 char in i and i+1;
		{
			for (int j = i + 2; j < cnt; j += 2)
				if (checkMatch(board, pos[i], pos[i + 1], pos[j], pos[j + 1], 1)) // Check if there are any ways lefts
					return true;
		}
		check++;
	}
	return false;
}

void resetPlayingBoard(Board_2** board)
{
	// Set all the cells back to valid
	for (int i = 1; i < hardHeight + 1; i++)
		for (int j = 1; j < hardWidth + 1; j++)
			findNode(board, i, j)->isValid = true;

	// Reset the cell character
	int restCount = (hardHeight * hardWidth) / 2;
	while (restCount)
	{
		int time = 2;
		char c = 65 + rand() % 26;
		while (time)
		{
			int i = rand() % hardHeight + 1, j = rand() % hardWidth + 1;
			if (findNode(board, i, j)->c == ' ')
			{
				findNode(board, i, j)->c = c;
				time--;
			}
		}
		restCount--;
	}
}

void showMoveSuggestion(Board_2** cell, int inow, int jnow)
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
				// Find the postion of cells have check character
				// Save all the positions in a pos array
				if (findNode(cell, i, j)->c == check && findNode(cell, i, j)->isValid)
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
				// Check if 2 cell are matched -> Show it on screen for 0,2s
				if (checkMatch(cell, pos[i], pos[i + 1], pos[j], pos[j + 1], 1))
				{
					findNode(cell, pos[i], pos[i + 1])->isHint = true;
					findNode(cell, pos[j], pos[j + 1])->isHint = true;
					findNode(cell, pos[i], pos[i + 1])->drawCell();
					findNode(cell, pos[j], pos[j + 1])->drawCell();

					playSound(2);
					Sleep(200);

					findNode(cell, pos[i], pos[i + 1])->isHint = false;
					findNode(cell, pos[j], pos[j + 1])->isHint = false;
					findNode(cell, pos[i], pos[i + 1])->drawCell();
					findNode(cell, pos[j], pos[j + 1])->drawCell();

					if (pos[i] == inow && pos[i + 1] == jnow)
						findNode(cell, pos[i], pos[i + 1])->isStopped = true;
					else if (pos[j] == inow && pos[j + 1] == jnow)
						findNode(cell, pos[j], pos[j + 1])->isStopped = true;

					return;
				}
			}
		}
		check++;
	}
}

int processSelectedHardCell(Player* p, int i, int j, int iselected, int jselected, int& deletedCount)
{
	findNode(p->hboard, i, j)->drawCell(); // Set the status of selected cell;
	Sleep(200);

	findNode(p->hboard, iselected, jselected)->isSelected = false;
	findNode(p->hboard, i, j)->isSelected = false;

	int check = 0;

	if (checkMatch(p->hboard, iselected, jselected, i, j, 0)) // Check if 2 cell are matched -> delete cell
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

		// Set the character of deleted cells back to null
		findNode(p->hboard, iselected, jselected)->c = ' ';
		findNode(p->hboard, i, j)->c = ' ';

		findNode(p->hboard, iselected, jselected)->deleteCell(7);
		findNode(p->hboard, i, j)->deleteCell(7);

		// Move other cells to the left
		moveCell(p->hboard, iselected, jselected);
		moveCell(p->hboard, i, j);

		displayBoard(p->hboard, 0);

		deletedCount += 2;

		// Check if the board is still valid
		if (!checkValidBoard(p->hboard) && deletedCount != hardHeight * hardWidth)
			return -1;

		check = 1;
	}
	else
	{
		playSound(4);
		findNode(p->hboard, iselected, jselected)->isValid = true;
		findNode(p->hboard, i, j)->isValid = true;

		// Set the old selected cell back to default
		findNode(p->hboard, iselected, jselected)->drawCell();
	}

	// When done process -> set the status of current standing cell
	findNode(p->hboard, i, j)->isStopped = true;
	findNode(p->hboard, i, j)->drawCell();
	findNode(p->hboard, i, j)->isStopped = false;

	return check;
}

void processHardPoint(Player* p)
{
	// The point will increase depends on streak
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

bool processAction(Board_2** cell, Player* p)
{
	int i = 1, j = 1;
	int oldi = i, oldj = j;

	int iselected = 0, jselected = 0;
	int selectedCount = 2;
	int deletedCount = 0;
	bool win = true;

	findNode(cell, i, j)->isStopped = true;

	while (true)
	{
		if (findNode(cell, i, j)->isStopped)
		{
			findNode(cell, oldi, oldj)->drawCell(); // Set the status of previous standing cell back to default
			oldi = i;
			oldj = j;

			findNode(cell, i, j)->drawCell(); // Set the status of current standing cell
			findNode(cell, i, j)->isStopped = false;
		}

		// If the game is completed
		if (deletedCount == hardHeight * hardWidth)
		{
			findNode(cell, i, j)->drawCell();
			Sleep(1500);
			clearConsole();
			if (!win) // LOSE
			{
				setColor(12);
				gotoxy(midWidth - 10, midHeight + 2);
				cout << "YOU LOSE, CHICKEN!!!";
				setColor(7);
				switch (generateMenu(midWidth - 12, midHeight + 6, "21,23", "RESTART,BACK TO MAIN MENU", 2))
				{
				case 0: // BACK TO MAIN MENU -> delete board and quit
					p->hard.isPlaying = false;
					deleteBoard(p->hboard);
					clearConsole();
					return false;
				case 1: // RESTART NEW GAME -> delete board and create new
					p->hard.isPlaying = false;
					deleteBoard(p->hboard);
					return true;
				}
			}
			else	// WIN
			{
				p->hard.isFinised = true;
				switch (generateMenu(midWidth - 12, midHeight + 6, "21,23,25,27", "CONTINUE WITH CURRENT SCORE,RESTART WITH NEW SCORE,SAVE AND MAIN MENU,JUST QUIT", 4))
				{
				case 0: // JUST QUIT -> delete board and reset point
					p->hard.isPlaying = false;
					deleteBoard(p->hboard);
					clearConsole();
					return false;
				case 1: // CONTINUE -> reset new board
					p->hard.isPlaying = true;
					return true;
				case 2: // RESTART -> delete board and create new
					p->hard.isPlaying = false;
					deleteBoard(p->hboard);
					return true;
				case 3: // SAVE AND MAIN MENU -> save and out
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
			findNode(cell, i, j)->isStopped = true;
			break;
		}
		case 2: // DOWN
		{
			if (i == hardHeight)
				i = 1;
			else
				i += 1;
			findNode(cell, i, j)->isStopped = true;
			break;
		}
		case 3: // LEFT
		{
			if (j == 1)
				j = hardWidth;
			else
				j -= 1;
			findNode(cell, i, j)->isStopped = true;
			break;
		}
		case 4: // RIGHT
		{
			if (j == hardWidth)
				j = 1;
			else
				j += 1;
			findNode(cell, i, j)->isStopped = true;
			break;
		}
		case 5: // SPACE or ENTER -> select a cell
		{
			// If a cell is valid and not selected
			if (!findNode(cell, i, j)->isSelected && findNode(cell, i, j)->isValid)
			{
				findNode(cell, i, j)->isSelected = true;
				findNode(cell, i, j)->isValid = false;
				findNode(cell, i, j)->isStopped = true;

				if (selectedCount == 2) // Save the location of the first selected
				{
					iselected = i;
					jselected = j;
				}
				selectedCount--;

				if (selectedCount == 0) // If 2 cells are selected -> check match
				{
					selectedCount = 2;
					int checkselectecd = processSelectedHardCell(p, i, j, iselected, jselected, deletedCount);
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
			else if (findNode(cell, i, j)->isSelected && !findNode(cell, i, j)->isValid) // If a selected cell is selected again -> unselected
			{
				findNode(cell, i, j)->isSelected = false;
				findNode(cell, i, j)->isValid = true;
				findNode(cell, i, j)->isStopped = true;
				selectedCount = 2;
			}
			else if (!findNode(cell, i, j)->isSelected && !findNode(cell, i, j)->isValid) // If an unvalid cell is selected
			{
				PlaySound(NULL, NULL, 0);
				playSound(3);
			}
			break;
		}
		case 6: // H -> show hint if valid
		{
			if (p->hard.hint)
			{
				showMoveSuggestion(cell, i, j);
				p->hard.hint--;
			}
			break;
		}
		case 7: // ESC
		{
			clearConsole();
			bool pause = true;
			while (pause)
			{
				switch (generateMenu(midWidth - 12, midHeight + 7, "22,24,26", "RESUME,RESTART,QUIT", 3))
				{
				case 0: // QUIT -> save or not save
					switch (generateMenu(midWidth - 12, midHeight + 7, "22,24,26", "SAVE,DON'T SAVE,BACK", 3))
					{
					case 0: // BACK
						break;
					case 1: // SAVE 
						p->hard.isPlaying = true;
						return false;
					case 3: // DON'T SAVE -> delete board
						p->hard.isPlaying = false;
						deleteBoard(p->hboard);
						return false;
					}
					break;
				case 1: // RESUME -> go back
					pause = false;
					findNode(cell, i, j)->isStopped = true;
					displayBoard(p->hboard, 0);
					showParameter(p, "hard");
					break;
				case 3: // RESTART -> delete board and create new
					p->hard.isPlaying = false;
					deleteBoard(p->hboard);
					return true;
				}
			}
			break;
		}
		default:
			break;
		}

		// Update parameter after an action
		showParameter(p, "hard");
	}
}

void hardMode(Player* p, int height, int width)
{
	hardHeight = height;
	hardWidth = width;
	boardHardHeight = hardHeight + 2;
	boardHardWidth = hardWidth + 2;

	srand(time(NULL));
	// A loop for continue playing
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
				generateBoard(p->hboard);
				if (!checkValidBoard(p->hboard))
					deleteBoard(p->hboard);
			} while (!checkValidBoard(p->hboard));
		}
		else // If yes -> check if the board is finished
		{
			if (p->hard.isFinised) // If yes -> reset new board
			{
				clearConsole();
				do
				{
					resetPlayingBoard(p->hboard);
				} while (!checkValidBoard(p->hboard));
				p->hard.isFinised = false;
			}
		}
		displayBoard(p->hboard, 5);
		showParameter(p, "hard");
	} while (processAction(p->hboard, p));
}