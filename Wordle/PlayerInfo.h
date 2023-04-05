#pragma once
#include "Struct.h"
#include "ConsoleAndUtility.h"

void addPlayer(Player*& list, Player* p);
void readPlayerFile(Player*& list);
void updatePlayerFile(Player*& list);
void deleteList(Player*& list);
bool checkNewPlayer();
Player* signIn(Player*& list);
void showWordDisplayEffect(string s);
Player* sortRank(Player*& list, string mode);
void showLeaderboard(Player* easy, Player* hard);