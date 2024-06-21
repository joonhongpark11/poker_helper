// game.h

#ifndef GAME_H
#define GAME_H

#include "Player.h"

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
    std::vector<std::string> cardsOnField;
    std::vector<std::string> communityCards;
    int totalCoin;
    int playerNumber;
    int smallBlind;
    int maxBetting;
    bool hasBet;
    int check;

public:
    //constructor
    Game(int players, int smallBlind) : playerNumber(players), smallBlind(smallBlind), hasBet(false), check(players + 1) {
    }

    //getter and setter
    std::vector<std::string> getCardsOnField() {return cardsOnField; }
    void setCardsOnField(std::vector<std::string> cards) {this->cardsOnField = cards; }
    std::vector<std::string> getCommunityCards() {return communityCards; }
    void setCommunityCards(std::vector<std::string> cards) { this->communityCards = cards; }
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
    int getCheck() { return check; }
    void setCheck(int check) { this->check = check; }



    std::vector<std::string> eraseCommon();
    std::vector<std::string> generateDeck();
    std::string pickRandomCard();
    int drawHoleCard(Player& p);
    int chooseDealerPosition(int playerNumber);
    std::vector<Player> playerSort(std::vector<Player>& players, int dealerPosition);
    void checkGameStat(std::vector<Player>& players);
    std::vector<Player> Game::findWinners(std::vector<Player>& players);
    int compareHands(const std::vector<std::string>& hand1, const std::vector<std::string>& hand2);
};


int playerInputLoop();


#endif // GAME_H