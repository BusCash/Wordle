#include "Hack.h"



void loadFileHacking(string fileName, savefile& hack)
{
	ifstream inFile(fileName, ios::binary);
	char ignore[PADDING];

	inFile.read((char*)&hack.mask, 1);
	inFile.read((char*)&hack.name, NAMESIZE);
	inFile.read((char*)&hack.password, PASSSIZE);
	inFile.read((char*)&ignore, PADDING);

	// record
	for (int i = 0; i < 5; i++)
	{
		inFile.read((char*)&hack.record[i].date.dd, 4);
		inFile.read((char*)&hack.record[i].date.mm, 4);
		inFile.read((char*)&hack.record[i].date.yy, 4);
		inFile.read((char*)&hack.record[i].points, 4);
		inFile.read((char*)&ignore, PADDING);
	}
	// state 
	for (int i = 0; i < 5; i++)
	{
		inFile.read((char*)&hack.state[i].p, 4);
		inFile.read((char*)&hack.state[i].q, 4);
		inFile.read((char*)&hack.state[i].p_, 4);
		inFile.read((char*)&hack.state[i].q_, 4);
		inFile.read((char*)&hack.state[i].board, BOARDSIZE);
		inFile.read((char*)&hack.state[i].file_background, URLSIZE);
		inFile.read((char*)&ignore, PADDING);
	}
	inFile.close();
}

void test(savefile hack)
{
	cout << hack.mask << endl;
	cout << hack.name << endl;
	cout << hack.password << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << hack.record[i].date.dd << "/" << hack.record[i].date.mm << "/" << hack.record[i].date.yy << endl;
		cout << hack.record[i].points << endl;

		cout << hack.state[i].p << " " << hack.state[i].q << ", " << hack.state[i].p_ << " " << hack.state[i].q_ << endl;
		cout << hack.state[i].board << endl;
		cout << hack.state[i].file_background << endl;
	}
}