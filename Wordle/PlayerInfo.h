#pragma once
#include "Struct.h"
#include "ConsoleAndUtility.h"

// Add a new player to the list of players
void addPlayer(Player*& list, Player* p);

// Read the player data from the player file and adds it to the list
void readPlayerFile(Player*& list);

// Update the player file with the data from the linked list of players
void updatePlayerFile(Player*& list);

// Delete the list of players
void deleteList(Player*& list);

// Check if user is a new player
bool checkNewPlayer();

// Get the player information
Player* signIn(Player*& list);

// Display a word display effect
void showWordDisplayEffect(string s);

// Sort the list of players by highest score
Player* sortRank(Player* list, string mode);

// Show the rank order in a specific mode
void showRank(Player* list, string mode);

// Display the leaderboard
void showLeaderboard(Player* list);