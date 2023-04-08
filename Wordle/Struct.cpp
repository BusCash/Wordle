#include "Struct.h"
#include "ConsoleAndUtility.h"

// Define a char array to illustrate the cell
char box[cellHeight][cellWidth] = {
	{"     "},
	{"     "},
	{"     "},
};

void Board_1::drawBackgroundCell(char bg[][65])
{
	int ci = (character.y - 1 - (midHeight + 2 - (boardEasyHeight * (cellHeight + 1) - 1) / 2)) / (cellHeight + 1),
		cj = (character.x - 2 - (midWidth - (boardEasyWidth * cellWidth - 1) / 2)) / (cellWidth);

	setColor(7);
	for (int h = 0; h < cellHeight + 1; h++)
	{
		if (ci == easyHeight && h == 3)
			break;
		gotoxy(cell.x, cell.y + h);
		for (int k = 0; k < 6; k++)
		{
			if (cj == easyWidth && k == 5)
				break;
			cout << bg[(ci - 1) * 4 + h][(cj - 1) * 6 + k];
		}
	}
}

void Board_1::drawCell()
{
	if (isHint)
	{
		// Change the hint cell to PURPLE
		setColor(13 * 16);
		for (int i = 0; i < cellHeight; i++)
		{
			gotoxy(cell.x, cell.y + i);
			cout << box[i];
		}
		gotoxy(character.x, character.y);
		cout << c;
		return;
	}
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
					gotoxy(cell.x, cell.y + i);
					cout << box[i];
				}
				gotoxy(character.x, character.y);
				cout << c;
			}
			else
			{
				// Change the current standing cell to BLUE
				setColor(3 * 16 + 15);
				for (int i = 0; i < cellHeight; i++)
				{
					gotoxy(cell.x, cell.y + i);
					cout << box[i];
				}
				gotoxy(character.x, character.y);
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
					gotoxy(cell.x, cell.y + i);
					cout << box[i];
				}
				gotoxy(character.x, character.y);
				cout << c;
			}
			else
			{
				// Change the current deleted standing cell to BLUE
				setColor(3 * 16);
				for (int i = 0; i < cellHeight; i++)
				{
					gotoxy(cell.x, cell.y + i);
					cout << box[i];
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
					gotoxy(cell.x, cell.y + i);
					cout << box[i];
				}
				gotoxy(character.x, character.y);
				cout << c;
			}
		}
		else
		{
			if (!isSelected)
				deleteCell(7);
		}
	}
	setColor(7);
}

void Board_1::deleteCell(int color)
{
	int ci = (character.y - 1 - (midHeight + 2 - (boardEasyHeight * (cellHeight + 1) - 1) / 2)) / (cellHeight + 1),
		cj = (character.x - 2 - (midWidth - (boardEasyWidth * cellWidth - 1) / 2)) / (cellWidth);

	// Go to the postion of deleted cell and print an empty box
	setColor(color);
	for (int i = 0; i < cellHeight; i++)
	{
		gotoxy(cell.x, cell.y + i);
		cout << box[i];
		gotoxy(character.x + 3, character.y);
		cout << " ";
		gotoxy(character.x - 3, character.y);
		cout << " ";
		gotoxy(character.x, character.y - 2);
		cout << " ";
		gotoxy(character.x, character.y + 2);
		cout << " ";

		if (ci == 0)
		{
			gotoxy(character.x, cell.y + 1 + i);
			cout << box[i];
		}
		else if (ci == easyHeight + 1)
		{
			gotoxy(character.x, cell.y - 1 + i);
			cout << box[i];
		}
		else if (cj == 0)
		{
			gotoxy(cell.x + 1, character.y + i);
			cout << box[i];
		}
		else if (cj == easyWidth + 1)
		{
			gotoxy(cell.x - 1, character.y + i);
			cout << box[i];
		}
	}

	// Print the background after deleted the cell
	char bg[23][65];
	getBackground(bg, 23, 41, "background\\easy.txt");
	if (ci != 0 && ci != easyHeight + 1 && cj != 0 && cj != easyWidth + 1)
		drawBackgroundCell(bg);
}

void Board_1::drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2)
{
	int ci = (character.y - 1 - (midHeight + 2 - (boardEasyHeight * (cellHeight + 1) - 1) / 2)) / (cellHeight + 1),
		cj = (character.x - 2 - (midWidth - (boardEasyWidth * cellWidth - 1) / 2)) / (cellWidth);
	int ci2 = (cy2 - 1 - (midHeight + 2 - (boardEasyHeight * (cellHeight + 1) - 1) / 2)) / (cellHeight + 1),
		cj2 = (cx2 - 2 - (midWidth - (boardEasyWidth * cellWidth - 1) / 2)) / (cellWidth);

	// Check if the 2 input positions are the same with the 2 selected cells
	setColor(14 * 16);
	if ((ci == i1 && cj == j1 && ci2 == i2 && cj2 == j2) || (ci == i2 && cj == j2 && ci2 == i1 && cj2 == j1)) // If both are the selected
	{
		if (character.y == cy2)
		{
			gotoxy(min(character.x, cx2) + 1, character.y);
			cout << char(17);
			for (int i = min(character.x, cx2) + 2; i < max(character.x, cx2) - 1; i++)
			{
				gotoxy(i, character.y);
				cout << char(45);
			}
			cout << char(16);
		}
		if (character.x == cx2)
		{
			gotoxy(character.x, min(character.y, cy2) + 1);
			cout << char(30);
			for (int i = min(character.y, cy2) + 2; i < max(character.y, cy2) - 1; i++)
			{
				gotoxy(character.x, i);
				cout << char(124);
			}
			gotoxy(character.x, max(character.y, cy2) - 1);
			cout << char(31);
		}
	}
	else if ((ci == i1 && cj == j1 && (ci2 != i2 || cj2 != j2)) || (ci == i2 && cj == j2 && (ci2 != i1 || cj2 != j1))) // If the first is the selected
	{
		if (character.y == cy2)
		{
			if (character.x < cx2)
			{
				gotoxy(character.x + 1, character.y);
				cout << char(17);
				for (int i = character.x + 2; i < cx2 + 1; i++)
				{
					gotoxy(i, character.y);
					cout << char(45);
				}
			}
			else
			{
				for (int i = cx2; i < character.x - 1; i++)
				{
					gotoxy(i, character.y);
					cout << char(45);
				}
				gotoxy(character.x - 1, character.y);
				cout << char(16);
			}
		}
		if (character.x == cx2)
		{
			if (character.y < cy2)
			{
				gotoxy(character.x, character.y + 1);
				cout << char(30);
				for (int i = character.y + 2; i < cy2; i++)
				{
					gotoxy(character.x, i);
					cout << char(124);
				}
			}
			else
			{
				for (int i = cy2 + 1; i < character.y - 1; i++)
				{
					gotoxy(character.x, i);
					cout << char(124);
				}
				gotoxy(character.x, character.y - 1);
				cout << char(31);
			}
		}
	}
	else if (((ci != i1 || cj != j1) && ci2 == i2 && cj2 == j2) || ((ci != i2 || cj != j2) && ci2 == i1 && cj2 == j1)) // If the second is the selected
	{
		if (character.y == cy2)
		{
			if (cx2 < character.x)
			{
				gotoxy(cx2 + 1, cy2);
				cout << char(17);
				for (int i = cx2 + 2; i < character.x + 1; i++)
				{
					gotoxy(i, cy2);
					cout << char(45);
				}
			}
			else
			{
				for (int i = character.x; i < cx2 - 1; i++)
				{
					gotoxy(i, cy2);
					cout << char(45);
				}
				gotoxy(cx2 - 1, cy2);
				cout << char(16);
			}
		}
		if (character.x == cx2)
		{
			if (cy2 < character.y)
			{
				gotoxy(cx2, cy2 + 1);
				cout << char(30);
				for (int i = cy2 + 2; i < character.y; i++)
				{
					gotoxy(cx2, i);
					cout << char(124);
				}
			}
			else
			{
				for (int i = character.y + 1; i < cy2 - 1; i++)
				{
					gotoxy(cx2, i);
					cout << char(124);
				}
				gotoxy(cx2, cy2 - 1);
				cout << char(31);
			}
		}
	}
	else if ((ci != i1 || cj != j1 && ci2 != i2 || cj2 != j2) && (ci != i2 || cj != j2 || ci2 != i1 || cj2 != j1)) // If none is the selected
	{
		if (character.y == cy2)
		{
			for (int i = min(character.x, cx2); i < max(character.x, cx2) + 1; i++)
			{
				gotoxy(i, character.y);
				cout << char(45);
			}
		}
		if (character.x == cx2)
		{
			for (int i = min(character.y, cy2) + 1; i < max(character.y, cy2); i++)
			{
				gotoxy(character.x, i);
				cout << char(124);
			}
		}
	}
}

void Board_2::drawBackgroundCell(char bg[][65])
{
	int ci = (character.y - 1 - (midHeight + 2 - (boardHardHeight * (cellHeight + 1) - 1) / 2)) / (cellHeight + 1),
		cj = (character.x - 2 - (midWidth - (boardHardWidth * cellWidth - 1) / 2)) / (cellWidth);
	setColor(7);
	for (int h = 0; h < cellHeight + 1; h++)
	{
		if (ci == hardHeight && h == 3)
			break;
		gotoxy(cell.x, cell.y + h);
		for (int k = 0; k < 6; k++)
		{
			if (cj == hardWidth && k == 5)
				break;
			cout << bg[(ci - 1) * 4 + h][(cj - 1) * 6 + k];
		}
	}
}

void Board_2::drawCell()
{
	if (isHint)
	{
		// Change the hint cell to PURPLE
		setColor(13 * 16);
		for (int i = 0; i < cellHeight; i++)
		{
			gotoxy(cell.x, cell.y + i);
			cout << box[i];
		}
		gotoxy(character.x, character.y);
		cout << c;
		return;
	}
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
					gotoxy(cell.x, cell.y + i);
					cout << box[i];
				}
				gotoxy(character.x, character.y);
				cout << c;
			}
			else
			{
				// Change the current standing cell to BLUE
				setColor(3 * 16 + 15);
				for (int i = 0; i < cellHeight; i++)
				{
					gotoxy(cell.x, cell.y + i);
					cout << box[i];
				}
				gotoxy(character.x, character.y);
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
					gotoxy(cell.x, cell.y + i);
					cout << box[i];
				}
				gotoxy(character.x, character.y);
				cout << c;
			}
			else
			{
				// Change the current deleted standing cell to BLUE
				setColor(3 * 16);
				for (int i = 0; i < cellHeight; i++)
				{
					gotoxy(cell.x, cell.y + i);
					cout << box[i];
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
					gotoxy(cell.x, cell.y + i);
					cout << box[i];
				}
				gotoxy(character.x, character.y);
				cout << c;
			}
		}
		else
		{
			if (!isSelected)
				deleteCell(7);
		}
	}
	setColor(7);
}

void Board_2::deleteCell(int color)
{
	int ci = (character.y - 1 - (midHeight + 2 - (boardHardHeight * (cellHeight + 1) - 1) / 2)) / (cellHeight + 1),
		cj = (character.x - 2 - (midWidth - (boardHardWidth * cellWidth - 1) / 2)) / (cellWidth);

	// Go to the postion of deleted cell and print an empty box
	setColor(color);
	for (int i = 0; i < cellHeight; i++)
	{
		gotoxy(cell.x, cell.y + i);
		cout << box[i];
		gotoxy(character.x - 1, character.y);
		cout << box[0];

		if (ci != hardHeight + 1)
		{
			gotoxy(cell.x, cell.y + cellHeight);
			cout << box[0];
		}

		if (ci == 0)
		{
			gotoxy(character.x, cell.y + 1 + i);
			cout << box[i];
		}
		else if (ci == hardHeight + 1)
		{
			gotoxy(character.x, cell.y - 1 + i);
			cout << box[i];
		}
		else if (cj == 0)
		{
			gotoxy(cell.x + 1, character.y + i);
			cout << box[i];
		}
		else if (cj == hardWidth + 1)
		{
			gotoxy(cell.x - 1, character.y + i);
			cout << box[i];
		}
	}

	// Print the background after deleted the cell
	char bg[23][65];
	getBackground(bg, 23, 65, "background\\hard.txt");
	if (ci != 0 && ci != hardHeight + 1 && cj != 0 && cj != hardWidth + 1)
		drawBackgroundCell(bg);
}

void Board_2::drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2)
{
	int ci = (character.y - 1 - (midHeight + 2 - (boardHardHeight * (cellHeight + 1) - 1) / 2)) / (cellHeight + 1),
		cj = (character.x - 2 - (midWidth - (boardHardWidth * cellWidth - 1) / 2)) / (cellWidth);
	int ci2 = (cy2 - 1 - (midHeight + 2 - (boardHardHeight * (cellHeight + 1) - 1) / 2)) / (cellHeight + 1),
		cj2 = (cx2 - 2 - (midWidth - (boardHardWidth * cellWidth - 1) / 2)) / (cellWidth);

	// Check if the 2 input positions are the same with the 2 selected cells
	setColor(14 * 16);
	if ((ci == i1 && cj == j1 && ci2 == i2 && cj2 == j2) || (ci == i2 && cj == j2 && ci2 == i1 && cj2 == j1)) // If both are the selected
	{
		if (character.y == cy2)
		{
			gotoxy(min(character.x, cx2) + 1, character.y);
			cout << char(17);
			for (int i = min(character.x, cx2) + 2; i < max(character.x, cx2) - 1; i++)
			{
				gotoxy(i, character.y);
				cout << char(45);
			}
			cout << char(16);
		}
		if (character.x == cx2)
		{
			gotoxy(character.x, min(character.y, cy2) + 1);
			cout << char(30);
			for (int i = min(character.y, cy2) + 2; i < max(character.y, cy2) - 1; i++)
			{
				gotoxy(character.x, i);
				cout << char(124);
			}
			gotoxy(character.x, max(character.y, cy2) - 1);
			cout << char(31);
		}
	}
	else if ((ci == i1 && cj == j1 && (ci2 != i2 || cj2 != j2)) || (ci == i2 && cj == j2 && (ci2 != i1 || cj2 != j1))) // If the first is the selected
	{
		if (character.y == cy2)
		{
			if (character.x < cx2)
			{
				gotoxy(character.x + 1, character.y);
				cout << char(17);
				for (int i = character.x + 2; i < cx2 + 1; i++)
				{
					gotoxy(i, character.y);
					cout << char(45);
				}
			}
			else
			{
				for (int i = cx2; i < character.x - 1; i++)
				{
					gotoxy(i, character.y);
					cout << char(45);
				}
				gotoxy(character.x - 1, character.y);
				cout << char(16);
			}
		}
		if (character.x == cx2)
		{
			if (character.y < cy2)
			{
				gotoxy(character.x, character.y + 1);
				cout << char(30);
				for (int i = character.y + 2; i < cy2; i++)
				{
					gotoxy(character.x, i);
					cout << char(124);
				}
			}
			else
			{
				for (int i = cy2 + 1; i < character.y - 1; i++)
				{
					gotoxy(character.x, i);
					cout << char(124);
				}
				gotoxy(character.x, character.y - 1);
				cout << char(31);
			}
		}
	}
	else if (((ci != i1 || cj != j1) && ci2 == i2 && cj2 == j2) || ((ci != i2 || cj != j2) && ci2 == i1 && cj2 == j1)) // If the second is the selected
	{
		if (character.y == cy2)
		{
			if (cx2 < character.x)
			{
				gotoxy(cx2 + 1, cy2);
				cout << char(17);
				for (int i = cx2 + 2; i < character.x + 1; i++)
				{
					gotoxy(i, cy2);
					cout << char(45);
				}
			}
			else
			{
				for (int i = character.x; i < cx2 - 1; i++)
				{
					gotoxy(i, cy2);
					cout << char(45);
				}
				gotoxy(cx2 - 1, cy2);
				cout << char(16);
			}
		}
		if (character.x == cx2)
		{
			if (cy2 < character.y)
			{
				gotoxy(cx2, cy2 + 1);
				cout << char(30);
				for (int i = cy2 + 2; i < character.y; i++)
				{
					gotoxy(cx2, i);
					cout << char(124);
				}
			}
			else
			{
				for (int i = character.y + 1; i < cy2 - 1; i++)
				{
					gotoxy(cx2, i);
					cout << char(124);
				}
				gotoxy(cx2, cy2 - 1);
				cout << char(31);
			}
		}
	}
	else if ((ci != i1 || cj != j1 && ci2 != i2 || cj2 != j2) && (ci != i2 || cj != j2 || ci2 != i1 || cj2 != j1)) // If none is the selected
	{
		if (character.y == cy2)
		{
			for (int i = min(character.x, cx2); i < max(character.x, cx2) + 1; i++)
			{
				gotoxy(i, character.y);
				cout << char(45);
			}
		}
		if (character.x == cx2)
		{
			for (int i = min(character.y, cy2) + 1; i < max(character.y, cy2); i++)
			{
				gotoxy(character.x, i);
				cout << char(124);
			}
		}
	}
}