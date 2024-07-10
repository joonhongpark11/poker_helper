#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"

#include <algorithm>
#include <random>
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
struct Pot;

class Player {
private:
    std::string name;
    int coin;
    int coinBet;
    std::vector<std::string> holeCards;
    bool isFold;
    bool doneAction;
    bool isAllIn;


public:
    // constructor
    Player(const std::string& name, int coin)
    : name(name), coin(coin), coinBet(0), isFold(false), doneAction(false) {}


    // Getters and setters
    std::string getName() { return name; }
    int getCoin() { return coin; }
    void setCoin(int coin) { this->coin = coin; }
    std::vector<std::string> getHoleCards() { return holeCards; }
    void setHoleCards(const std::vector<std::string>& newHand) { holeCards = newHand; }
    void setHoleCards() { holeCards.clear(); }
    int getCoinBet() { return coinBet; }
    void setCoinBet(int coin) { this->coinBet = coin; }
    bool getIsFold() { return isFold; }
    void setIsFold(bool isFold) { this->isFold = isFold; }
    bool getDoneAction() { return doneAction; }
    void setDoneAction(bool doneAction) { this->doneAction = doneAction; }
    bool getIsAllIn() { return isAllIn; }
    void setIsAllIn(bool isAllIn ) { this->isAllIn = isAllIn; }

    // util function in Player
    std::vector<std::string> makeCompleteHand(const std::vector<std::string>& communityCards);

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

    // player action functions
    void putCoin(int amount, Game& game, Pot* pot);
    void betting(int amount, Game& game);
    int chooseWeightedAction(const std::vector<int>& actions, const std::vector<double>& weights, std::mt19937& rng);
    int chooseAction(Game& game);
    void doAction(int action, Game& game);
    void createSidePot(Game& game);
};

// util global functions
int convertNumbers(char rank);
std::vector<int> convertHandToNumbers(const std::vector<std::string>& hand);
std::vector<char> convertHandToSuits(const std::vector<std::string>& hand);
std::string handsToString(Hands hand);

#endif // PLAYER_H
