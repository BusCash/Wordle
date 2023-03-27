#include "generateConsole.h"

void gotoxy(int x, int y)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos;
    cursorPos.X = x;
    cursorPos.Y = y;

    // Set position of cursor
    SetConsoleCursorPosition(console, cursorPos);
}

void setWindowSizeAndPos()
{
    HWND console1 = GetForegroundWindow();
    RECT rectWindow;

    GetClientRect(console1, &rectWindow);
    int xPos = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
    int yPos = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

    // Set the position and size for the window
    MoveWindow(console1, xPos, yPos, windowWidth, windowHeight, TRUE);
}

void setCursor(int mode)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = mode;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}

void generateWindow()
{
    setWindowSizeAndPos();
    SetConsoleTitleW(L"Matching Game");
    setCursor(0);
}

void setColor(int color)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, color);
}

void drawGraph(int delayTime)
{
    system("cls");
    setColor(14);

    // Draw the top, bottom edge
    for (int i = 0; i < gameWidth; i++)
    {
        gotoxy(i, 0);
        putchar(219);
        gotoxy(gameWidth - i - 1, gameHeight - 1);
        putchar(219);
        Sleep(delayTime);
    }

    // Draw the left, right edge
    for (int i = 1; i < gameHeight; i++)
    {
        gotoxy(gameWidth - 1, i);
        putchar(219);
        gotoxy(0, gameHeight - i);
        putchar(219);
        Sleep(delayTime);
    }
}

void drawTitle()
{
    int x = gameWidth / 4 - 15;
    int y = gameHeight / 4;
    gotoxy(x, y);
    cout << "~77:   .77!   :7777777.  :77777777!   ~7777777     !77.        :777777777?^";
    gotoxy(x, y + 1);
    cout << "P@@! . .&@&..5#@?!7!Y@G? 7@@B!7!!B@P~ 5@@5!!5&G7. .#@@^        ~@@#";
    gotoxy(x, y + 2);
    cout << "P@@J7&Y7&@#..&@&.   !@@P 7@@P   ~G@@7 5@@7   :&@#: #@&^        ~@@B!!!!!~~~";
    gotoxy(x, y + 3);
    cout << "P@@@@&@@@@#..&@&.   !@@P 7@@#Y5G@577: 5@@7   :&@&: #@&:        ~@@B77777!!!";
    gotoxy(x, y + 4);
    cout << "P@@B5:?B@@&..5#@7~!~J@BJ 7@@G:5#@&G~. 5@@5~~5&G?. .#@@?~!!!!!~ ~@@B";
    gotoxy(x, y + 5);
    cout << "!??:   .??7.  ^???????.  ^??!  .???J^ ~???????     7?????????7 :?????????J^";
}

void generateGraphic()
{
    drawGraph(5);
    drawTitle();
}

int getConsoleInput()
{
    int key = _getch();
    if (key == 0 || key == 224) // If arrows keyboard hit
    {
        key = _getch();
        if (key == UP)
            return 1;
        else if (key == DOWN)
            return 2;
        else if (key == LEFT)
            return 3;
        else if (key == RIGHT)
            return 4;
    }
    else
    {
        if (key == ENTER || key == SPACEBAR)
            return 5;
    }
}


void changeBarStatus(int barX, int barY, int moveY, string s, int bColor, int tColor)
{
    setColor(bColor * 16 + tColor);

    if (moveY == barY)
    {
        gotoxy(barX, barY);
        cout << "                        ";
        gotoxy(barX + 12 - s.length() / 2, barY);
        cout << s;
    }

    setColor(7);
}

int generateMenu()
{
    int barX = midWidth - 12, barY = midHeight + 6;
    int moveY = barY, oldY = barY;

    for (int i = barY; i <= barY + 2 * 3; i += 2)
    {
        changeBarStatus(barX, 21, i, "PLAY", 0, 7);
        changeBarStatus(barX, 23, i, "LEADERBOARD", 0, 7);
        changeBarStatus(barX, 25, i, "CREDITS", 0, 7);
        changeBarStatus(barX, 27, i, "QUIT", 0, 7);
    }

    bool check = true;
    int input;
    while (true)
    {
        if (check == true)
        {
            changeBarStatus(barX, 21, oldY, "PLAY", 0, 7);
            changeBarStatus(barX, 23, oldY, "LEADERBOARD", 0, 7);
            changeBarStatus(barX, 25, oldY, "CREDITS", 0, 7);
            changeBarStatus(barX, 27, oldY, "QUIT", 0, 7);
            oldY = moveY;

            // Highlight the selected bar
            changeBarStatus(barX, 21, moveY, "PLAY", 6, 13);
            changeBarStatus(barX, 23, moveY, "LEADERBOARD", 6, 13);
            changeBarStatus(barX, 25, moveY, "CREDITS", 6, 13);
            changeBarStatus(barX, 27, moveY, "QUIT", 6, 13);
            check = false;
        }

        switch (getConsoleInput())
        {
        case 1:
        {
            check = true;
            if (moveY != barY)
                moveY -= 2;
            else
                moveY = barY + 2 * 3;
            break;
        }
        case 2:
        {
            check = true;
            if (moveY != barY + 2 * 3)
                moveY += 2;
            else
                moveY = barY;
            break;
        }
        case 5:
        {
            changeBarStatus(barX, 21, 21, "", 0, 0);
            changeBarStatus(barX, 23, 23, "", 0, 0);
            changeBarStatus(barX, 25, 25, "", 0, 0);
            changeBarStatus(barX, 27, 27, "", 0, 0);
            if (moveY == 27) // If "QUIT" is selected
                return 0;
            else if (moveY == 21) // If "PLAY" is selected
                return 1;
            else if (moveY == 23) // If "LEADERBOARD" is selected
                return 2;
            else if (moveY == 25) // If "CREDITS" is selected
                return 3;
        }
        default:
            break;
        }
    }
}

void clearConsole()
{
    setColor(7);
    for (int i = 1; i < gameHeight - 1; i++)
    {
        for (int j = 1; j < gameWidth - 1; j++)
        {
            gotoxy(j, i);
            cout << " ";
        }
    }
}


int showPlayMenu()
{
    int barX = midWidth - 12, barY = midHeight + 7;
    int moveY = barY, oldY = barY;

    for (int i = barY; i <= barY + 2 * 2; i += 2)
    {
        changeBarStatus(barX, 22, i, "EASY", 0, 7);
        changeBarStatus(barX, 24, i, "HARDCORE", 0, 7);
        changeBarStatus(barX, 26, i, "BACK", 0, 7);
    } 

    bool check = true;
    int input;
    while (true)
    {
        if (check == true)
        {
            changeBarStatus(barX, 22, oldY, "EASY", 0, 7);
            changeBarStatus(barX, 24, oldY, "HARDCORE", 0, 7);
            changeBarStatus(barX, 26, oldY, "BACK", 0, 7);
            oldY = moveY;

            changeBarStatus(barX, 22, moveY, "EASY", 6, 13);
            changeBarStatus(barX, 24, moveY, "HARDCORE", 6, 13);
            changeBarStatus(barX, 26, moveY, "BACK", 6, 13);
            check = false;
        }

        switch (getConsoleInput())
        {
        case 1:
        {
            check = true;
            if (moveY != barY)
                moveY -= 2;
            else
                moveY = barY + 2 * 2;
            break;
        }
        case 2:
        {
            check = true;
            if (moveY != barY + 2 * 2)
                moveY += 2;
            else
                moveY = barY;
            break;
        }
        case 5:
        {
            changeBarStatus(barX, 22, 22, "", 0, 0);
            changeBarStatus(barX, 24, 24, "", 0, 0);
            changeBarStatus(barX, 26, 26, "", 0, 0);
            if (moveY == 26) // If "BACK" is selected
                return 0;
            else if (moveY == 22) // If "EASY" is selected
                return 1;
            else if (moveY == 24) // If "LEADERBOARD" is selected
                return 2;
        }
        default:
            break;
        }
    }
}