#include "Cell.h"
#include "ConsoleAndUtility.h"

char cell[cellHeight][cellWidth] = {
	{"     "},
	{"     "},
	{"     "},
};

void Board_1::drawBackgroundCell(char bg[][65])
{
	setColor(7);
	for (int h = 0; h < cellHeight + 1; h++)
	{
		if (ci == 4 && h == 3)
			break;
		gotoxy(x, y + h);
		for (int k = 0; k < 6; k++)
		{
			if (cj == 7 && k == 5)
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
				deleteCell(7);
		}
	}
	setColor(7);
}

void Board_1::deleteCell(int color)
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
		else if (ci == 5)
		{
			gotoxy(cx, y - 1 + i);
			cout << cell[i];
		}
		else if (cj == 0)
		{
			gotoxy(x + 1, cy + i);
			cout << cell[i];
		}
		else if (cj == 8)
		{
			gotoxy(x - 1, cy + i);
			cout << cell[i];
		}
	}

	char bg[15][65];
	getBackground(bg, 15, 41, "background\\bg.txt");
	if (ci != 0 && ci != 5 && cj != 0 && cj != 8)
		drawBackgroundCell(bg);
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

void Board_2::drawBackgroundCell(char bg[][65])
{
	setColor(7);
	for (int h = 0; h < cellHeight + 1; h++)
	{
		if (ci == 6 && h == 3)
			break;
		gotoxy(x, y + h);
		for (int k = 0; k < 6; k++)
		{
			if (cj == 11 && k == 5)
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
				deleteCell(7);
		}
	}
	setColor(7);
}

void Board_2::deleteCell(int color)
{
	setColor(color);
	for (int i = 0; i < cellHeight; i++)
	{
		gotoxy(x, y + i);
		cout << cell[i];
		gotoxy(cx - 1, cy);
		cout << cell[0];

		if (ci != 7)
		{
			gotoxy(x, y + cellHeight);
			cout << cell[0];
		}

		if (ci == 0)
		{
			gotoxy(cx, y + 1 + i);
			cout << cell[i];
		}
		else if (ci == 7)
		{
			gotoxy(cx, y - 1 + i);
			cout << cell[i];
		}
		else if (cj == 0)
		{
			gotoxy(x + 1, cy + i);
			cout << cell[i];
		}
		else if (cj == 12)
		{
			gotoxy(x - 1, cy + i);
			cout << cell[i];
		}
	}

	char bg[23][65];
	getBackground(bg, 23, 65, "background\\bg.txt");
	if (ci != 0 && ci != 7 && cj != 0 && cj != 12)
		drawBackgroundCell(bg);
}

void Board_2::drawArrow(int cx2, int cy2, int i1, int j1, int i2, int j2)
{
	int ci2 = (cy2 - 1 - 3) / (cellHeight + 1),
		cj2 = (cx2 - 2 - 5) / (cellWidth);

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