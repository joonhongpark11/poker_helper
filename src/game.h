#ifndef GAME_H
#define GAME_H

#include "Player.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_set>

#define GREETING "Welcome to Poker Helper!\nThis program is designed to help you win Poker, Texas Hold'em game.\n\n"
#define PLAYER_INPUT "How many players do you want to play with?\n"
#define INVALID_PLAYER_NUMBER "Player Number should be an integer from 1 to 9.\nPlease type the player number again!\n\n"

#define MAX_PLAYER (9)
#define MIN_PLAYER (1)
#define OK (1)
#define ERROR (-1)

//forward declaration
class Player;

typedef struct Pot {
private:
    int amount;
    int threshold;
    std::vector<Player*> eligiblePlayers;
    struct Pot* nextPtr;
    struct Pot* prevPtr;

public:
    // Accessors
    int getAmount() const { return amount; }
    int getThreshold() const { return threshold; }
    std::vector<Player*> getEligiblePlayers() const { return eligiblePlayers; }
    Pot* getNextPtr() const { return nextPtr; }
    Pot* getPrevPtr() const { return prevPtr; }
    
    // Mutators
    void setAmount(int amt) { amount = amt; }
    void setThreshold(int thresh) { threshold = thresh; }
    void addPlayer(Player* player) { eligiblePlayers.push_back(player); }
    void setNextPtr(Pot* ptr) { nextPtr = ptr; }
    void setPrevPtr(Pot* ptr) { prevPtr = ptr; }
} Pot;

class Game {
private:
    // need to reset each game
    std::vector<std::string> cardsLeft;
    std::vector<std::string> cardsOnField;
    std::vector<std::string> communityCards;
    int maxBetting;
    bool hasBet;

    std::vector<Player*> players;
    int playerNumber;
    int smallBlind;
    int round;
    Pot** pots;
public:
    //constructor
    Game(int players, int smallBlind) : playerNumber(players),
         smallBlind(smallBlind), maxBetting(0), round(1), hasBet(false) {
            initializePlayers();
            createNewPot();
         }

    //getter and setter
    std::vector<Player*> getPlayers() { return players; }
    void setPlayers(std::vector<Player*> players) { this->players = players; }
    std::vector<std::string> getCardsLeft() { return cardsLeft; }
    void setCardsLeft( std::vector<std::string> cardsLeft) { this->cardsLeft = cardsLeft; }
    std::vector<std::string> getCardsOnField() {return cardsOnField; }
    void setCardsOnField(std::vector<std::string> cards) {this->cardsOnField = cards; }
    void setCardsOnField() { cardsOnField.clear(); }
    std::vector<std::string> getCommunityCards() {return communityCards; }
    void setCommunityCards(std::vector<std::string> cards) { this->communityCards = cards; }
    void setCommunityCards() { communityCards.clear(); }
    int getPlayerNumber() { return playerNumber; }
    void setPlayerNumber(int players) { this->playerNumber = players; }
    int getSmallBlind() { return smallBlind; }
    void setSmallBlind(int coin) { this->smallBlind = coin; }
    int getMaxBetting() { return maxBetting; }
    void setMaxBetting(int bet) { this->maxBetting = bet; }
    bool getHasBet() { return hasBet; }
    void setHasBet(bool bet) { this->hasBet = bet; }
    int getRound() { return round; }
    void setRound(int round) { this->round = round; }
    Pot** getPots() { return pots; }
    void setPots(Pot** pots) { this->pots = pots; }

    // game setting functions
    std::vector<std::string> generateDeck();


    std::vector<std::string> eraseCommon();
    std::string pickRandomCard();
    void drawHoleCards(Player* p);
    void setupHoleCards();
    void sortPlayer(int dealerPosition);
    void checkGameStat();
    void printPotInfo();
    std::vector<Player*> findWinners(Pot* pot);
    int compareHands(const std::vector<std::string>& hand1, const std::vector<std::string>& hand2);
    int static compareSameHands(const std::vector<std::string>& hand1, const std::vector<std::string>& hand2);
    void distributeCoins(std::vector<Player*>& winners, Pot* pot);
    void resetForNextGame();
    void printPlayerOrder();
    void initializePlayers();
    void freePlayers();
    void makeDoneActionFalse();
    bool isPlayerAllDone();
    bool isOnlyOnePlayerLeft();
    bool hasAllIn();
    Pot* createNewPot();
    void removeAllPots();
    void doShowDown();
};

// game process functions
int requestPlayerNumbers();


#endif // GAME_H