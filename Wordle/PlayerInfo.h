#pragma once
#include "Cell.h"
#include "ConsoleAndUtility.h"

bool checkNewPlayer();
void showWordDisplayEffect(string s);
void readPlayerInfo(Player player[], int& n);
Player getPlayerInfo(bool newbie);
void processPlayerInfo(Player& p, Player player[], int n);
Player signIn();
bool compareScore(Player a, Player b, string mode);
void saveRecord(Player player[], int n);
void showLeaderboard();
void printLeaderboard();