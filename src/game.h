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

#define GREETING "Welcome to Poker Helper!\nThis program is designed to help you win Poker, especially Texas Hold'em game.\n\n"
#define PLAYER_INPUT "How many players do you want to play with?\n"
#define INVALID_PLAYER_NUMBER "Player Number should be an integer from 1 to 9.\nPlease type the player number again!\n\n"

#define MAX_PLAYER (9)
#define MIN_PLAYER (1)
#define OK (1)
#define ERROR (-1)

//forward declaration
class Player;

class Game {
private:
    // need to reset each game
    std::vector<std::string> cardsLeft;
    std::vector<std::string> cardsOnField;
    std::vector<std::string> communityCards;
    int totalCoin;
    int maxBetting;
    bool hasBet;

    std::vector<Player*> players;
    int playerNumber;
    int smallBlind;
    int round;

public:
    //constructor
    Game(int players, int smallBlind) : totalCoin(0), playerNumber(players),
         smallBlind(smallBlind), maxBetting(0), round(1), hasBet(false) {
            initializePlayers();
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
    int getTotalCoin() { return totalCoin; }
    void setTotalCoin(int coin) { this->totalCoin = coin; }
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

    // game setting functions
    std::vector<std::string> generateDeck();


    std::vector<std::string> eraseCommon();
    std::string pickRandomCard();
    void drawHoleCards(Player* p);
    void setupHoleCards();
    void sortPlayer(int dealerPosition);
    void checkGameStat();
    std::vector<Player*> findWinners();
    int compareHands(const std::vector<std::string>& hand1, const std::vector<std::string>& hand2);
    int static compareSameHands(const std::vector<std::string>& hand1, const std::vector<std::string>& hand2);
    void distributeCoins(std::vector<Player*>& winners);
    void resetForNextGame();
    void printPlayerOrder();
    void initializePlayers();
    void freePlayers();
    void makeDoneActionFalse();
    bool isPlayerAllDone();
    bool isOnlyOnePlayerLeft();
};

// game process functions
int requestPlayerNumbers();


#endif // GAME_H