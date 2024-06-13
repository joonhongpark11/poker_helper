#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <map>

/* maybe use later
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
*/

class Player {
private:
    std::string name;
    int coin;
    std::vector<std::string> holeCards;

public:
    // constructor
    Player(const std::string& name, int coin) : name(name), coin(coin) {
        // 'holeCards' is automatically initialized to an empty vector
    }

    // Getters and setters
    std::string getName() { return name; }
    int getCoin() { return coin; }
    void setCoin(int coin) { this->coin = coin; }
    std::vector<std::string> getHoleCards() { return holeCards; }
    void setHand(const std::vector<std::string>& newHand) { holeCards = newHand; }

    // Poker hand evaluation functions
    static int numberConversion(char rank);
    static std::vector<int> convertHandToNumbers(const std::vector<std::string>& hand);
    static std::vector<char> convertHandToSuits(const std::vector<std::string>& hand);
    static int compareHighest(const std::vector<std::string>& hand1,
                              const std::vector<std::string>& hand2);
    std::vector<std::string> makeCompleteHand(const std::vector<std::string>& communityCards);                          
    bool isOnePair(const std::vector<std::string>& communityCards);
    bool isTwoPairs(const std::vector<std::string>& communityCards);
    bool isThreeOfAKind(const std::vector<std::string>& communityCards);
    bool isStraight(const std::vector<std::string>& communityCards);
    bool isFlush(const std::vector<std::string>& communityCards);
    bool isFullHouse(const std::vector<std::string>& communityCards);
    bool isFourOfAKind(const std::vector<std::string>& communityCards);
    bool isStraightFlush(const std::vector<std::string>& communityCards);
    bool isRoyalFlush(const std::vector<std::string>& communityCards);
    std::string determineHand(const std::vector<std::string>& communityCards);
};

#endif // PLAYER_H
