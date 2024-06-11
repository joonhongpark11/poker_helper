// Poker.h
#ifndef POKER_H
#define POKER_H

#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <map>


enum class Hands {
    NoMatch = 0,
    HighCard = 1,
    OnePair = 2,
    TwoPairs = 3,
    ThreeOfAKind = 4,
    Straight = 5,
    Flush = 6,
    FullHouse = 7,
    FourOfAKind = 8,
    StraightFlush = 9,
    RoyalFlush = 10
};

int numberConversion(char rank);
std::vector<int> convertHandToNumbers(const std::vector<std::string>& hand);
std::vector<char> convertHandToSuits(const std::vector<std::string>& hand);
bool isOnePair(const std::vector<std::string>& hand);
bool isTwoPairs(const std::vector<std::string>& hand);
bool isThreeOfAKind(const std::vector<std::string>& hand);
bool isStraight(const std::vector<std::string>& hand);
bool isFlush(const std::vector<std::string>& hand);
bool isFullHouse(const std::vector<std::string>& hand);
bool isFourOfAKind(const std::vector<std::string>& hand);
bool isStraightFlush(const std::vector<std::string>& hand);
bool isRoyalFlush(const std::vector<std::string>& hand);
int compareHighest(const std::vector<std::string>& hand1, const std::vector<std::string>& hand2);
std::string determineHand(const std::vector<std::string>& hand);

#endif // POKER_H

