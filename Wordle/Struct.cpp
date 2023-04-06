#include "Struct.h"
#include "ConsoleAndUtility.h"

char cell[cellHeight][cellWidth] = {
	{"     "},
	{"     "},
	{"     "},
};

void Board_1::drawBackgroundCell(char bg[][65], int easyHeight, int easyWidth)
{
	setColor(7);
	for (int h = 0; h < cellHeight + 1; h++)
	{
		if (ci == easyHeight && h == cellHeight)
			break;
		gotoxy(x, y + h);
		for (int k = 0; k < 6; k++)
		{
			if (cj == easyWidth && k == cellWidth - 1)
				break;
			cout << bg[(ci - 1) * 4 + h][(cj - 1) * 6 + k];
		}
	}
}

void Board_1::drawCell(int easyHeight, int easyWidth)
{
	if (isHint)
	{
		// Change the hint cell to PURPLE
		setColor(13 * 16);
		for (int i = 0; i < cellHeight; i++)
		{
			gotoxy(x, y + i);
			cout << cell[i];
		}
		gotoxy(cx, cy);
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
				deleteCell(7, easyHeight, easyWidth);
		}
	}
	setColor(7);
}

void Board_1::deleteCell(int color, int easyHeight, int easyWidth)
{
	setColor(color);
	for (int i = 0; i < cellHeight; i++)
	{
		gotoxy(x, y + i);
		cout << cell[i];

		if (ci == 0)
		{
			gotoxy(cx, y + 1 + i);
			cout << cell[i];
		}
		else if (ci == easyHeight + 1)
		{
			gotoxy(cx, y - 1 + i);
			cout << cell[i];
		}
		else if (cj == 0)
		{
			gotoxy(x + 1, cy + i);
			cout << cell[i];
		}
		else if (cj == easyWidth + 1)
		{
			gotoxy(x - 1, cy + i);
			cout << cell[i];
		}
	}

	char bg[23][65];
	getBackground(bg, cellHeight * easyHeight + easyHeight - 1, (cellWidth - 1) * easyWidth + easyWidth - 1, "background\\easy.txt");
	if (ci != 0 && ci != easyHeight + 1 && cj != 0 && cj != easyWidth + 1)
		drawBackgroundCell(bg, easyHeight, easyWidth);
}

void Board_1::drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2, int boardEasyHeight, int boardEasyWidth)
{
	int ci2 = (cy2 - 1 - (midHeight + 2 - (boardEasyHeight * (cellHeight + 1) - 1) / 2)) / (cellHeight + 1),
		cj2 = (cx2 - 2 - (midWidth - (boardEasyWidth * cellWidth - 1) / 2)) / (cellWidth);

	setColor(14 * 16);
	if ((ci == i1 && cj == j1 && ci2 == i2 && cj2 == j2) || (ci == i2 && cj == j2 && ci2 == i1 && cj2 == j1)) // If both are the selected
	{
		if (cy == cy2)
		{
			gotoxy(min(cx, cx2) + 1, cy);
			cout << char(17);
			for (int i = min(cx, cx2) + 2; i < max(cx, cx2) - 1; i++)
			{
				gotoxy(i, cy);
				cout << char(45);
			}
			cout << char(16);
		}
		if (cx == cx2)
		{
			gotoxy(cx, min(cy, cy2) + 1);
			cout << char(30);
			for (int i = min(cy, cy2) + 2; i < max(cy, cy2) - 1; i++)
			{
				gotoxy(cx, i);
				cout << char(124);
			}
			gotoxy(cx, max(cy, cy2) - 1);
			cout << char(31);
		}
	}
	else if ((ci == i1 && cj == j1 && (ci2 != i2 || cj2 != j2)) || (ci == i2 && cj == j2 && (ci2 != i1 || cj2 != j1))) // If the first is the selected
	{
		if (cy == cy2)
		{
			if (cx < cx2)
			{
				gotoxy(cx + 1, cy);
				cout << char(17);
				for (int i = cx + 2; i < cx2 + 1; i++)
				{
					gotoxy(i, cy);
					cout << char(45);
				}
			}
			else
			{
				for (int i = cx2; i < cx - 1; i++)
				{
					gotoxy(i, cy);
					cout << char(45);
				}
				gotoxy(cx - 1, cy);
				cout << char(16);
			}
		}
		if (cx == cx2)
		{
			if (cy < cy2)
			{
				gotoxy(cx, cy + 1);
				cout << char(30);
				for (int i = cy + 2; i < cy2; i++)
				{
					gotoxy(cx, i);
					cout << char(124);
				}
			}
			else
			{
				for (int i = cy2 + 1; i < cy - 1; i++)
				{
					gotoxy(cx, i);
					cout << char(124);
				}
				gotoxy(cx, cy - 1);
				cout << char(31);
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
				cout << char(17);
				for (int i = cx2 + 2; i < cx + 1; i++)
				{
					gotoxy(i, cy2);
					cout << char(45);
				}
			}
			else
			{
				for (int i = cx; i < cx2 - 1; i++)
				{
					gotoxy(i, cy2);
					cout << char(45);
				}
				gotoxy(cx2 - 1, cy2);
				cout << char(16);
			}
		}
		if (cx == cx2)
		{
			if (cy2 < cy)
			{
				gotoxy(cx2, cy2 + 1);
				cout << char(30);
				for (int i = cy2 + 2; i < cy; i++)
				{
					gotoxy(cx2, i);
					cout << char(124);
				}
			}
			else
			{
				for (int i = cy + 1; i < cy2 - 1; i++)
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
		if (cy == cy2)
		{
			for (int i = min(cx, cx2); i < max(cx, cx2) + 1; i++)
			{
				gotoxy(i, cy);
				cout << char(45);
			}
		}
		if (cx == cx2)
		{
			for (int i = min(cy, cy2) + 1; i < max(cy, cy2); i++)
			{
				gotoxy(cx, i);
				cout << char(124);
			}
		}
	}
}

void Board_2::drawBackgroundCell(char bg[][65], int hardHeight, int hardWidth)
{
	setColor(7);
	for (int h = 0; h < cellHeight + 1; h++)
	{
		if (ci == hardHeight && h == cellHeight)
			break;
		gotoxy(x, y + h);
		for (int k = 0; k < 6; k++)
		{
			if (cj == hardWidth && k == cellWidth - 1)
				break;
			cout << bg[(ci - 1) * 4 + h][(cj - 1) * 6 + k];
		}
	}
}

void Board_2::drawCell(int hardHeight, int hardWidth)
{
	if (isHint)
	{
		// Change the hint cell to PURPLE
		setColor(13 * 16);
		for (int i = 0; i < cellHeight; i++)
		{
			gotoxy(x, y + i);
			cout << cell[i];
		}
		gotoxy(cx, cy);
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
				// If the cell is matched -> BLUE
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
				deleteCell(7, hardHeight, hardWidth);
		}
	}
	setColor(7);
}

void Board_2::deleteCell(int color, int hardHeight, int hardWidth)
{
	setColor(color);
	for (int i = 0; i < cellHeight; i++)
	{
		gotoxy(x, y + i);
		cout << cell[i];
		gotoxy(cx - 1, cy);
		cout << cell[0];

		if (ci != hardHeight + 1)
		{
			gotoxy(x, y + cellHeight);
			cout << cell[0];
		}

		if (ci == 0)
		{
			gotoxy(cx, y + 1 + i);
			cout << cell[i];
		}
		else if (ci == hardHeight + 1)
		{
			gotoxy(cx, y - 1 + i);
			cout << cell[i];
		}
		else if (cj == 0)
		{
			gotoxy(x + 1, cy + i);
			cout << cell[i];
		}
		else if (cj == hardWidth + 1)
		{
			gotoxy(x - 1, cy + i);
			cout << cell[i];
		}
	}

	char bg[23][65];
	getBackground(bg, cellHeight * hardHeight + hardHeight - 1, (cellWidth - 1) * hardWidth + hardWidth - 1, "background\\hard.txt");
	if (ci != 0 && ci != hardHeight + 1 && cj != 0 && cj != hardWidth + 1)
		drawBackgroundCell(bg, hardHeight, hardWidth);
}

void Board_2::drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2, int boardHardHeight, int boardHardWidth)
{
	int ci2 = (cy2 - 1 - (midHeight + 2 - (boardHardHeight * (cellHeight + 1) - 1) / 2)) / (cellHeight + 1),
		cj2 = (cx2 - 2 - (midWidth - (boardHardWidth * cellWidth - 1) / 2)) / (cellWidth);

	setColor(14 * 16);
	if ((ci == i1 && cj == j1 && ci2 == i2 && cj2 == j2) || (ci == i2 && cj == j2 && ci2 == i1 && cj2 == j1)) // If both are the selected
	{
		if (cy == cy2)
		{
			gotoxy(min(cx, cx2) + 1, cy);
			cout << char(17);
			for (int i = min(cx, cx2) + 2; i < max(cx, cx2) - 1; i++)
			{
				gotoxy(i, cy);
				cout << char(45);
			}
			cout << char(16);
		}
		if (cx == cx2)
		{
			gotoxy(cx, min(cy, cy2) + 1);
			cout << char(30);
			for (int i = min(cy, cy2) + 2; i < max(cy, cy2) - 1; i++)
			{
				gotoxy(cx, i);
				cout << char(124);
			}
			gotoxy(cx, max(cy, cy2) - 1);
			cout << char(31);
		}
	}
	else if ((ci == i1 && cj == j1 && (ci2 != i2 || cj2 != j2)) || (ci == i2 && cj == j2 && (ci2 != i1 || cj2 != j1))) // If the first is the selected
	{
		if (cy == cy2)
		{
			if (cx < cx2)
			{
				gotoxy(cx + 1, cy);
				cout << char(17);
				for (int i = cx + 2; i < cx2 + 1; i++)
				{
					gotoxy(i, cy);
					cout << char(45);
				}
			}
			else
			{
				for (int i = cx2; i < cx - 1; i++)
				{
					gotoxy(i, cy);
					cout << char(45);
				}
				gotoxy(cx - 1, cy);
				cout << char(16);
			}
		}
		if (cx == cx2)
		{
			if (cy < cy2)
			{
				gotoxy(cx, cy + 1);
				cout << char(30);
				for (int i = cy + 2; i < cy2; i++)
				{
					gotoxy(cx, i);
					cout << char(124);
				}
			}
			else
			{
				for (int i = cy2 + 1; i < cy - 1; i++)
				{
					gotoxy(cx, i);
					cout << char(124);
				}
				gotoxy(cx, cy - 1);
				cout << char(31);
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
				cout << char(17);
				for (int i = cx2 + 2; i < cx + 1; i++)
				{
					gotoxy(i, cy2);
					cout << char(45);
				}
			}
			else
			{
				for (int i = cx; i < cx2 - 1; i++)
				{
					gotoxy(i, cy2);
					cout << char(45);
				}
				gotoxy(cx2 - 1, cy2);
				cout << char(16);
			}
		}
		if (cx == cx2)
		{
			if (cy2 < cy)
			{
				gotoxy(cx2, cy2 + 1);
				cout << char(30);
				for (int i = cy2 + 2; i < cy; i++)
				{
					gotoxy(cx2, i);
					cout << char(124);
				}
			}
			else
			{
				for (int i = cy + 1; i < cy2 - 1; i++)
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
		if (cy == cy2)
		{
			for (int i = min(cx, cx2); i < max(cx, cx2) + 1; i++)
			{
				gotoxy(i, cy);
				cout << char(45);
			}
		}
		if (cx == cx2)
		{
			for (int i = min(cy, cy2) + 1; i < max(cy, cy2); i++)
			{
				gotoxy(cx, i);
				cout << char(124);
			}
		}
	}
}