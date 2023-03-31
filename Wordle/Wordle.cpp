#include "EasyMode.h"
#include "PlayerInfo.h"

int main()
{
	generateWindow();
	generateGraphic();
	Player p;

	bool quit = false;
	while (!quit)
	{
		switch (generateMenu())
		{
		case 0:
			quit = true;
			break;
		case 1:
		{
			switch (showPlayMenu())
			{
			case 0:
				break;
			case 1:
				clearConsole();
				p = getPlayerInfo();
				easyMode(p);
				break;
			case 2:
				break;
			}
			break;
		}
		case 2:
			break;
		case 3:
			bool credits = true;
			clearConsole();
			while (credits)
			{
				showCredits();
				switch (getConsoleInput())
				{
				case 5:
					credits = false;
					clearConsole();
					drawTitle();
					break;
				default:
					break;
				}
			}
		}
	}
	return 0;
}
