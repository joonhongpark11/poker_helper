#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"

#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <map>

enum class Hands {
    NoMatch = 0,
    HighCard = 1,
    OnePair = 2,
    TwoPair = 3,
    ThreeOfAKind = 4,
    Straight = 5,
    Flush = 6,
    FullHouse = 7,
    FourOfAKind = 8,
    StraightFlush = 9,
    RoyalFlush = 10
};


//forward declaration
class Game;

class Player {
private:
    std::string name;
    int coin;
    int coinBet;
    std::vector<std::string> holeCards;
    bool fold;

public:
    // constructor
    Player(const std::string& name, int coin)
    : name(name), coin(coin), fold(false) {}


    // Getters and setters
    std::string getName() { return name; }
    int getCoin() { return coin; }
    void setCoin(int coin) { this->coin = coin; }
    std::vector<std::string> getHoleCards() { return holeCards; }
    void setHoleCards(const std::vector<std::string>& newHand) { holeCards = newHand; }
    void setHoleCards() { holeCards.clear(); }
    int getCoinBet() { return coinBet; }
    void setCoinBet(int coin) { this->coinBet = coin; }
    bool getFold() { return fold; }
    void setFold(bool isFold) { this->fold = isFold; }

    

    // util functions
    static int convertNumbers(char rank);
    static std::vector<int> convertHandToNumbers(const std::vector<std::string>& hand);
    static std::vector<char> convertHandToSuits(const std::vector<std::string>& hand);
    std::vector<std::string> makeCompleteHand(const std::vector<std::string>& communityCards);
    std::string handsToString(Hands hand);

    // hand evalulation boolean functions                        
    bool isOnePair(const std::vector<std::string>& completeHand);
    bool isTwoPair(const std::vector<std::string>& completeHand);
    bool isThreeOfAKind(const std::vector<std::string>& completeHand);
    bool isStraight(const std::vector<std::string>& completeHand);
    bool isFlush(const std::vector<std::string>& completeHand);
    bool isFullHouse(const std::vector<std::string>& completeHand);
    bool isFourOfAKind(const std::vector<std::string>& ccompleteHand);
    bool isStraightFlush(const std::vector<std::string>& completeHand);
    bool isRoyalFlush(const std::vector<std::string>& completeHand);

    // post detection functions
    std::vector<std::string> findBestFiveCardHand(const std::vector<std::string>& completeHand);
    Hands evaluateHand(const std::vector<std::string>& completeHand);
    static int isBetterHand(const std::vector<std::string>& hand1, const std::vector<std::string>& hand2);

    // player action functions
    void betting(int amount, Game& game);
    int chooseAction();
    void doAction(int action, Game& game);
};

#endif // PLAYER_H
