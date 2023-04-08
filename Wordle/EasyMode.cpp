#include "EasyMode.h"

int easyHeight,
easyWidth,
boardEasyHeight,
boardEasyWidth;

void generateBoard(Board_1** board)
{
	for (int i = 0; i < boardEasyHeight; i++)
	{
		board[i] = new Board_1[boardEasyWidth];
		for (int j = 0; j < boardEasyWidth; j++)
		{
			// Set the position for the cell
			board[i][j].cell.x = j * cellWidth + midWidth - (boardEasyWidth * cellWidth - 1) / 2;
			board[i][j].cell.y = i * (cellHeight + 1) + midHeight + 2 - (boardEasyHeight * (cellHeight + 1) - 1) / 2;

			// Set the position for the character
			board[i][j].character.x = board[i][j].cell.x + 2;
			board[i][j].character.y = board[i][j].cell.y + 1;
		}
	}

	// Set the board edge unavailable
	for (int i = 0; i < boardEasyHeight; i++)
	{
		board[i][0].isValid = false;
		board[i][boardEasyWidth - 1].isValid = false;
	}
	for (int j = 0; j < boardEasyWidth; j++)
	{
		board[0][j].isValid = false;
		board[boardEasyHeight - 1][j].isValid = false;
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
	if (board != NULL)
	{
		for (int i = 0; i < boardEasyHeight; i++)
			delete[] board[i];

		delete[] board;
	}
}

void displayBoard(Board_1** board, int delaytime)
{
	for (int i = 1; i < easyHeight + 1; i++)
	{
		for (int j = 1; j < easyWidth + 1; j++)
		{
			board[i][j].drawCell();
			Sleep(delaytime);
		}
	}
}

bool checkRowMatch(Board_1** board, int j1, int j2, int i)
{
	// Check if between 2 cells in a row is clear or if next to each other
	for (int j = min(j1, j2) + 1; j < max(j1, j2); j++)
		if (board[i][j].c != ' ')
			return false;
	return true;
}

bool checkColMatch(Board_1** board, int i1, int i2, int j)
{
	// Check if between 2 cells in a column is clear or if next to each other
	for (int i = min(i1, i2) + 1; i < max(i1, i2); i++)
		if (board[i][j].c != ' ')
			return false;
	return true;
}

bool checkIMatch(Board_1** board, int i1, int j1, int i2, int j2, int type)
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
				board[i1][j1].drawArrow(board[i2][j1].character.x, board[i2][j1].character.y, i1, j1, i2, j2);
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
				// Show the arrow for 0,2 seconds
				board[i1][j1].drawArrow(board[i1][j2].character.x, board[i1][j2].character.y, i1, j1, i2, j2);
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
	// Check 2 corners created by those cells 
	//	-> If the corners is clear
	//	-> Check the 2 lines from that corner to those cells

	if (board[i1][j2].c == ' ')
		if (checkRowMatch(board, j1, j2, i1) && checkColMatch(board, i1, i2, j2))
		{
			if (type == 0)
			{
				// Show the arrow for 0,2 seconds
				board[i1][j1].drawArrow(board[i1][j2].character.x, board[i1][j2].character.y, i1, j1, i2, j2);
				board[i1][j2].drawArrow(board[i2][j2].character.x, board[i2][j2].character.y, i1, j1, i2, j2);
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
				// Show the arrow for 0,2 seconds
				board[i2][j2].drawArrow(board[i2][j1].character.x, board[i2][j1].character.y, i1, j1, i2, j2);
				board[i2][j1].drawArrow(board[i1][j1].character.x, board[i1][j1].character.y, i1, j1, i2, j2);
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
					board[jmin.x][jmin.y].drawArrow(board[jmin.x][j].character.x, board[jmin.x][j].character.y, i1, j1, i2, j2);
					board[jmin.x][j].drawArrow(board[jmax.x][j].character.x, board[jmax.x][j].character.y, i1, j1, i2, j2);
					board[jmax.x][j].drawArrow(board[jmax.x][jmax.y].character.x, board[jmax.x][jmax.y].character.y, i1, j1, i2, j2);
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
					// Show the arrow for 0,2 seconds
					board[imin.x][imin.y].drawArrow(board[i][imin.y].character.x, board[i][imin.y].character.y, i1, j1, i2, j2);
					board[i][imin.y].drawArrow(board[i][imax.y].character.x, board[i][imax.y].character.y, i1, j1, i2, j2);
					board[imax.x][imax.y].drawArrow(board[i][imax.y].character.x, board[i][imax.y].character.y, i1, j1, i2, j2);
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
		while (jnext <= easyWidth + 1 && board[jmin.x][jnext].c == ' ' && board[jmax.x][jnext].c == ' ')
		{
			if (checkColMatch(board, jmin.x, jmax.x, jnext))
			{
				if (type == 0)
				{
					// Show the arrow for 0,2 seconds
					board[jmin.x][jnext].drawArrow(board[jmax.x][jnext].character.x, board[jmax.x][jnext].character.y, i1, j1, i2, j2);
					board[jmin.x][jmin.y].drawArrow(board[jmin.x][jnext].character.x, board[jmin.x][jnext].character.y, i1, j1, i2, j2);
					board[jmax.x][jmax.y].drawArrow(board[jmax.x][jnext].character.x, board[jmax.x][jnext].character.y, i1, j1, i2, j2);
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

	// Check left direction
	if (checkRowMatch(board, jmax.y, jmin.y - 1, jmax.x))
	{
		int jnext = jmin.y + upleft;
		while (jnext >= 0 && board[jmin.x][jnext].c == ' ' && board[jmax.x][jnext].c == ' ')
		{
			if (checkColMatch(board, jmin.x, jmax.x, jnext))
			{
				if (type == 0)
				{
					// Show the arrow for 0,2 seconds
					board[jmin.x][jnext].drawArrow(board[jmax.x][jnext].character.x, board[jmax.x][jnext].character.y, i1, j1, i2, j2);
					board[jmin.x][jmin.y].drawArrow(board[jmin.x][jnext].character.x, board[jmin.x][jnext].character.y, i1, j1, i2, j2);
					board[jmax.x][jmax.y].drawArrow(board[jmax.x][jnext].character.x, board[jmax.x][jnext].character.y, i1, j1, i2, j2);
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
					// Show the arrow for 0,2 seconds
					board[imin.x][imin.y].drawArrow(board[inext][imin.y].character.x, board[inext][imin.y].character.y, i1, j1, i2, j2);
					board[imax.x][imax.y].drawArrow(board[inext][imax.y].character.x, board[inext][imax.y].character.y, i1, j1, i2, j2);
					board[inext][imin.y].drawArrow(board[inext][imax.y].character.x, board[inext][imax.y].character.y, i1, j1, i2, j2);
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
					// Show the arrow for 0,2 seconds
					board[imin.x][imin.y].drawArrow(board[inext][imin.y].character.x, board[inext][imin.y].character.y, i1, j1, i2, j2);
					board[imax.x][imax.y].drawArrow(board[inext][imax.y].character.x, board[inext][imax.y].character.y, i1, j1, i2, j2);
					board[inext][imin.y].drawArrow(board[inext][imax.y].character.x, board[inext][imax.y].character.y, i1, j1, i2, j2);
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
		int pos[66];
		for (int i = 1; i < easyHeight + 1; i++)
		{
			for (int j = 1; j < easyWidth + 1; j++)
			{
				// Find the postion of cells have check character
				// Save all the positions in a pos array
				if (board[i][j].c == check && board[i][j].isValid)
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

void resetPlayingBoard(Board_1** board, int deletedCount)
{
	// Check if the game is complete or not
	if (deletedCount == 0) // If yes -> Set all the cells back to valid
		for (int i = 1; i < easyHeight + 1; i++)
			for (int j = 1; j < easyWidth + 1; j++)
				board[i][j].isValid = true;
	else				   // If no -> Set all the valid cell to null
		for (int i = 1; i < easyHeight + 1; i++)
			for (int j = 1; j < easyWidth + 1; j++)
				if (board[i][j].isValid)
					board[i][j].c = ' ';

	// Reset the cell character
	int restCount = (easyHeight * easyWidth - deletedCount) / 2;
	while (restCount)
	{
		int time = 2;
		char c = 65 + rand() % 26;
		while (time)
		{
			int i = rand() % easyHeight + 1, j = rand() % easyWidth + 1;
			if (board[i][j].isValid && board[i][j].c == ' ')
			{
				board[i][j].c = c;
				time--;
			}
		}
		restCount--;
	}
}

void showMoveSuggestion(Board_1** cell, int inow, int jnow)
{
	char check = 'A';
	while (check >= 'A' && check <= 'Z')
	{
		int cnt = 0;
		int pos[66];

		for (int i = 1; i < easyHeight + 1; i++)
		{
			for (int j = 1; j < easyWidth + 1; j++)
			{
				// Find the postion of cells have check character
				// Save all the positions in a pos array
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
				// Check if 2 cell are matched -> Show it on screen for 0,2s
				if (checkMatch(cell, pos[i], pos[i + 1], pos[j], pos[j + 1], 1))
				{
					cell[pos[i]][pos[i + 1]].isHint = true;
					cell[pos[j]][pos[j + 1]].isHint = true;
					cell[pos[i]][pos[i + 1]].drawCell();
					cell[pos[j]][pos[j + 1]].drawCell();

					playSound(2);
					Sleep(200);

					cell[pos[i]][pos[i + 1]].isHint = false;
					cell[pos[j]][pos[j + 1]].isHint = false;
					cell[pos[i]][pos[i + 1]].drawCell();
					cell[pos[j]][pos[j + 1]].drawCell();

					if (pos[i] == inow && pos[i + 1] == jnow)
						cell[pos[i]][pos[i + 1]].isStopped = true;
					else if (pos[j] == inow && pos[j + 1] == jnow)
						cell[pos[j]][pos[j + 1]].isStopped = true;

					return;
				}
			}
		}
		check++;
	}
}

bool processSelectedCell(Player* p, int i, int j, int iselected, int jselected, int& deletedCount)
{
	p->eboard[i][j].drawCell(); // Set the status of selected cell;
	Sleep(200);

	p->eboard[iselected][jselected].isSelected = false;
	p->eboard[i][j].isSelected = false;

	bool check = false;

	if (checkMatch(p->eboard, iselected, jselected, i, j, 0)) // Check if 2 cell are matched -> delete cell
	{
		if (p->easy.streak < 5)
			playSound(5);
		else if (p->easy.streak < 8)
			playSound(6);
		else if (p->easy.streak < 10)
			playSound(7);
		else if (p->easy.streak < 13)
			playSound(8);
		else
			playSound(9);

		// Set the character of deleted cells back to null
		p->eboard[iselected][jselected].c = ' ';
		p->eboard[i][j].c = ' ';

		p->eboard[iselected][jselected].deleteCell(7);
		p->eboard[i][j].deleteCell(7);

		deletedCount += 2;

		// Check if the board is not valid -> reset the board
		if (!checkValidBoard(p->eboard) && deletedCount != easyHeight * easyWidth)
		{
			do
			{
				resetPlayingBoard(p->eboard, deletedCount);
			} while (!checkValidBoard(p->eboard));
			displayBoard(p->eboard, 5);
		}

		check = true;
	}
	else
	{
		playSound(4);
		p->eboard[iselected][jselected].isValid = true;
		p->eboard[i][j].isValid = true;

		// Set the old selected cell back to default
		p->eboard[iselected][jselected].drawCell();
	}

	// When done process -> set the status of current standing cell
	p->eboard[i][j].isStopped = true;
	p->eboard[i][j].drawCell();
	p->eboard[i][j].isStopped = false;

	return check;
}

void processPoint(Player* p)
{
	// The point will increase depends on streak
	if (p->easy.streak == 0)
		return;
	if (p->easy.streak < 5)
		p->easy.point += 5;
	else if (p->easy.streak < 8)
		p->easy.point += 5 * p->easy.streak;
	else if (p->easy.streak < 10)
		p->easy.point += 15 * p->easy.streak;
	else if (p->easy.streak == 10)
		p->easy.point += 15 * p->easy.streak + 500;
	else if (p->easy.streak < 14)
		p->easy.point += (5 + p->easy.streak) * p->easy.streak + (p->easy.streak - 5) * 100;
	else
		p->easy.point += (5 + p->easy.streak) * p->easy.streak + 1005;
}

bool processAction(Board_1** cell, Player* p)
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
			cell[oldi][oldj].drawCell(); // Set the status of previous standing cell back to default
			oldi = i;
			oldj = j;

			cell[i][j].drawCell(); // Set the status of current standing cell
			cell[i][j].isStopped = false;
		}

		// If the game is completed
		if (deletedCount == easyHeight * easyWidth)
		{
			cell[i][j].drawCell();
			Sleep(1500);
			clearConsole();
			p->easy.isFinised = true;
			switch (generateMenu(midWidth - 12, midHeight + 6, "21,23,25,27", "CONTINUE WITH CURRENT SCORE,RESTART WITH NEW SCORE,BACK TO MAIN MENU,JUST QUIT", 4))
			{
			case 0: // JUST QUIT -> delete board and reset point
				p->easy.isPlaying = false;
				deleteBoard(p->eboard);
				clearConsole();
				return false;
			case 1: // CONTINUE -> reset new board
				p->easy.isPlaying = true;
				return true;
			case 2: // RESTART -> delete board and create new
				p->easy.isPlaying = false;
				deleteBoard(p->eboard);
				return true;
			case 3: // SAVE AND MAIN MENU -> save and out
				p->easy.isPlaying = true;
				clearConsole();
				return false;
			}
		}

		switch (getConsoleInput()) // Take input from keyboard
		{
		case 1: // UP
		{
			if (i == 1)
				i = easyHeight;
			else
				i--;
			cell[i][j].isStopped = true;
			break;
		}
		case 2: // DOWN
		{
			if (i == easyHeight)
				i = 1;
			else
				i += 1;
			cell[i][j].isStopped = true;
			break;
		}
		case 3: // LEFT
		{
			if (j == 1)
				j = easyWidth;
			else
				j -= 1;
			cell[i][j].isStopped = true;
			break;
		}
		case 4: // RIGHT
		{
			if (j == easyWidth)
				j = 1;
			else
				j += 1;
			cell[i][j].isStopped = true;
			break;
		}
		case 5: // SPACE or ENTER -> select a cell
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
				if (selectedCount == 0) // If 2 cells are selected -> check match
				{
					selectedCount = 2;
					if (processSelectedCell(p, i, j, iselected, jselected, deletedCount))
						p->easy.streak++;
					else
						p->easy.streak = 0;
					processPoint(p);
					if (p->easy.point > p->easy.maxpoint)
						p->easy.maxpoint = p->easy.point;
				}
			}
			else if (cell[i][j].isSelected && !cell[i][j].isValid) // If a selected cell is selected again -> unselected
			{
				cell[i][j].isSelected = false;
				cell[i][j].isValid = true;
				cell[i][j].isStopped = true;
				selectedCount = 2;
			}
			else if (!cell[i][j].isSelected && !cell[i][j].isValid) // If an unvalid cell is selected
			{
				PlaySound(NULL, NULL, 0);
				playSound(3);
			}
			break;
		}
		case 6: // H -> show hint if valid
		{
			if (p->easy.hint)
			{
				showMoveSuggestion(cell, i, j);
				p->easy.hint--;
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
						p->easy.isPlaying = true;
						return false;
					case 3: // DON'T SAVE -> delete board
						p->easy.isPlaying = false;
						deleteBoard(p->eboard);
						return false;
					}
					break;
				case 1: // RESUME -> go back
					pause = false;
					cell[i][j].isStopped = true;
					displayBoard(p->eboard, 0);
					showParameter(p, "easy");
					break;
				case 3: // RESTART -> delete board and create new
					p->easy.isPlaying = false;
					deleteBoard(p->eboard);
					return true;
				}
			}
		}
		default:
			break;
		}

		// Update parameter after an action
		showParameter(p, "easy");
	}
}

void easyMode(Player* p, int height, int width)
{
	easyHeight = height;
	easyWidth = width;
	boardEasyHeight = easyHeight + 2;
	boardEasyWidth = easyWidth + 2;

	srand(time(NULL));
	// A loop for continue playing
	do
	{
		// Check if the board is being played or not
		if (!p->easy.isPlaying) // If no -> reset new board
		{
			clearConsole();
			p->easy.streak = 0;
			p->easy.point = 0;
			p->easy.hint = 3;
			do
			{
				p->eboard = new Board_1 * [boardEasyHeight];
				generateBoard(p->eboard);
				if (!checkValidBoard(p->eboard))
					deleteBoard(p->eboard);
			} while (!checkValidBoard(p->eboard));
		}
		else // If yes -> check if the board is finished
		{
			if (p->easy.isFinised) // If yes -> reset new board
			{
				clearConsole();
				do
				{
					resetPlayingBoard(p->eboard, 0);
				} while (!checkValidBoard(p->eboard));
				p->easy.isFinised = false;
			}
		}
		displayBoard(p->eboard, 5);
		showParameter(p, "easy");
	} while (processAction(p->eboard, p));
}
