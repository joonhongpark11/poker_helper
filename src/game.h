// game.h

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <random>

// Function declaration for generateDeck
std::vector<std::string> generateDeck();
std::string pickRandomCard(std::vector<std::string>& cardsOnField);

#endif // GAME_H