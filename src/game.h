// game.h

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <random>
#include <unordered_set>

#define GREETING "Welcome to Poker Helper!\nThis program is designed to help you win Poker, especially Texas Hold'em game.\n\n"
#define PLAYER_INPUT "How many players do you want to play with?\n"
#define INVALID_PLAYER_NUMBER "Player Number should be an integer from 1 to 9.\nPlease type the player number again!\n\n"

#define MAX_PLAYER (9)
#define MIN_PLAYER (1)
#define OK (1)
#define ERROR (-1)


// Function declaration for generateDeck
std::vector<std::string> generateDeck();
std::string pickRandomCard(std::vector<std::string>& cardsOnField);
int playerInputLoop();


#endif // GAME_H