#include "Game.h"

/*--------------game setting functions--------------------------------------*/

/*
 *  generateDeck() will generates a full 52 cards deck.
 */

std::vector<std::string> Game::generateDeck() {
    char numbers[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    char suits[] = {'D', 'H', 'C', 'S'};

    int size1 = sizeof(numbers) / sizeof(numbers[0]);
    int size2 = sizeof(suits) / sizeof(suits[0]);

    std::vector<std::string> deck;
    deck.reserve(size1 * size2);  // Reserve space for all possible cards
    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            std::string card;
            card += numbers[i];
            card += suits[j];
            deck.push_back(card);
        }
    }
    return deck;
} /* generateDeck() */

/*
 *  pickRandomCard() picks a random card from 'cardsLeft' and moves it to 'cardsOnField'.
 */

std::string Game::pickRandomCard() {
    static std::mt19937 rdm(std::time(nullptr));  // Static to initialize seed only once

    if (!cardsLeft.empty()) {
        std::shuffle(cardsLeft.begin(), cardsLeft.end(), rdm);
        std::string selectedCard = cardsLeft.back();
        // remove from the cardsLeft
        cardsLeft.pop_back();
        // add to cardsOnField
        cardsOnField.push_back(selectedCard);
        setCardsOnField(cardsOnField);

        // need to be always 52
        assert((cardsLeft.size() + cardsOnField.size()) == 52);

        return selectedCard;
    }

    return ""; // Return empty string when no cards are left
}

/*
 *  drawHoleCards() draws hole cards for one player
 */

void Game::drawHoleCards(Player* p) {
    std::string card1 = pickRandomCard();
    std::string card2 = pickRandomCard();
    p->setHoleCards({card1, card2});
} /* drawHoleCards() */

/*
 *  setupHoleCards() draws holecards for all players.
 */

void Game::setupHoleCards() {
    for (Player* player : players) {
        drawHoleCards(player);
    }
} /* setupHoleCards() */

/*
 *  sortPlayer() will sort the playerlist based on the dealer position.
 */

void Game::sortPlayer(int dealerPosition) {
    // Create a temporary vector to hold elements before dealerPosition
    std::vector<Player*> temp;
    for (int i = 0; i <= dealerPosition; ++i) {
        temp.push_back(players[i]);
    }

    // Shift elements from dealerPosition onwards to the start of players
    int newIndex = 0;
    for (int i = dealerPosition + 1; i < players.size(); ++i) {
        players[newIndex++] = players[i];
    }

    // Move elements from temp to the end of players
    for (int i = 0; i < temp.size(); ++i) {
        players[newIndex++] = temp[i];
    }
} /* sortPlayer() */

/*
 *  checkGameStat() prints the current game stats.
 *  mostly for debugging.
 */
void Game::checkGameStat() {
    std::cout << "Game stats:\n";
    std::cout << "playerNumber: " << playerNumber << "\n";
    std::cout << "smallBlind: " << smallBlind << "\n";
    std::cout << "maxBetting: " << maxBetting << "\n";
    printPotInfo();
    std::cout << "round: " << round << "\n";
    std::cout << "cardLeft: " << cardsLeft.size() << "\n";
    std::cout << "cards On Field: " << cardsOnField.size() << "\n";
    std::cout << "community cards: ";
    for (std::string card : communityCards) {
        std::cout << card << " ";
    }
    std::cout << "\n";
    std::cout << "Player Stats:\n";
    int total = 0;
    for (auto player : players) {
        std::cout << player->getName() << ":\n";
        std::cout << "coin: " << player->getCoin() << ", ";
        std::cout << "coinBet: " << player->getCoinBet() << ", ";
        std::cout << "holeCards: ";
        for (auto card : player->getHoleCards()) {
            std::cout << card << " ";
        }
        std:: cout << ", ";
        std::cout << "Fold: " << player->getIsFold() << "\n";
        total += player->getCoin();
    }
    std::cout << "total coin: " << total << "\n";
} /* checkGameStat() */

void Game::printPotInfo() {
    Pot* curPot = *pots;
    int index = 0;
    while (curPot != nullptr) {
        if (index == 0) {
            std::cout << "mainpot: \n";
        }
        else {
            std::cout << "sidepot" << index << " \n";
        }
        std::cout << "amount: " << curPot->getAmount() << "\n";
        std::cout << "eligible players: ";
        std::vector<Player*> players = curPot->getEligiblePlayers();
        for (Player* player : players) {
            std::cout << player->getName() << " ";
        }
        std::cout << "\n";

        curPot = curPot->getNextPtr();
    }
}



/*
 *  compareHands() compares two hands.
 *  return 1 when first arg has higher hand.
 *  return -1 when second arg has higher hand.
 *  return 0 when two args have the same hand.
 */

int Game::compareHands(const std::vector<std::string>& hand1, const std::vector<std::string>& hand2) {
    // Evaluate ranks of both hands
    Player player = {"util", 100};
    Hands rank1 = player.evaluateHand(hand1);
    Hands rank2 = player.evaluateHand(hand2);

    // Compare hand ranks first
    if (rank1 > rank2) return 1;
    if (rank1 < rank2) return -1;

    return 0;
} /* cmopareHands() */

/*
 *  compareSameHand() evalulates the better than between two same hands.
 *  Returns 1 if hand1 is better, -1 if hand2 is better, 0 if they are equal
 *  draw is only for number. We don't consider suit for winner determination.
 */

int Game::compareSameHands(const std::vector<std::string>& hand1, const std::vector<std::string>& hand2) {
    if (hand1.empty() && hand2.empty()) {
        return 0;
    }
    if (hand1.empty()) {
        return -1;
    }
    if (hand2.empty()) {
        return 1;
    }
    std::vector<int> values1, values2;
    for (const auto& card : hand1) {
        values1.push_back(convertNumbers(card[0]));
    }
    for (const auto& card : hand2) {
        values2.push_back(convertNumbers(card[0]));
    }

    std::sort(values1.begin(), values1.end(), std::greater<int>());
    std::sort(values2.begin(), values2.end(), std::greater<int>());

    for (int i = 0; i < values1.size(); i++) {
        if (values1[i] > values2[i]) return 1;
        if (values1[i] < values2[i]) return -1;
    }
    return 0;  // If completely equal, return 0 indicating a draw
} /* compareSameHands() */

/*
 *  findWinners() finds winner for the round. It can be multiple
 *  if two or more players have the same hands and same cards(numbers).
 */

std::vector<Player*> Game::findWinners(Pot* pot) {
    std::vector<Player*> activePlayers;
    std::vector<std::vector<std::string>> bestHands;

    // Filter active players and find their best hands
    for (auto& player : pot->getEligiblePlayers()) {
        if (!player->getIsFold()) {
            activePlayers.push_back(player);
            bestHands.push_back(player->findBestFiveCardHand(player->makeCompleteHand(getCommunityCards())));
        }
    }

    if (activePlayers.empty()) {
        throw std::runtime_error("No active players found");
    }

    std::vector<Player*> winners = {activePlayers[0]};
    std::vector<std::string> bestHand = bestHands[0];

    // Compare each player's hand to the current best
    for (size_t i = 1; i < activePlayers.size(); ++i) {
        int result = compareHands(bestHands[i], bestHand);
        if (result > 0) {
            winners.clear();
            winners.push_back(activePlayers[i]);
            bestHand = bestHands[i];
        } else if (result == 0) {
            // If hands have the same ranking, use compareSameHands to break the tie
            int sameHandResult = compareSameHands(bestHands[i], bestHand);
            if (sameHandResult > 0) {
                winners.clear();
                winners.push_back(activePlayers[i]);
                bestHand = bestHands[i];
            } else if (sameHandResult == 0) {
                winners.push_back(activePlayers[i]);
            }
        }
    }

    return winners;
} /* findWinners() */

/*
 *  distributeCoins() dirstributes winning coins to the winners.
 *  amount argument is the amount of the current pot
 */

void Game::distributeCoins(std::vector<Player*>& winners, Pot* pot) {
    int amount = pot->getAmount();
    assert(amount != 0);
    int numWinners = winners.size();
    if (numWinners == 0) { // if no winners, which is not possible.
        std::cout << "no winner detected. Please check\n";
        return;
    }

    int coinsPerWinner = amount / numWinners;  // Each winner's equal share
    int remainder = amount % numWinners;       // Remainder if not divisible evenly

    for (int i = 0; i < numWinners; ++i) {
        int additionalCoin = (i < remainder) ? 1 : 0;
        int winnerCoin = winners[i]->getCoin() + coinsPerWinner + additionalCoin;
        winners[i]->setCoin(winnerCoin);
    }
} /* distributeCoins() */

void Game::doShowDown() {
    Pot* curPot = *pots;
    int index = 0;
    while (curPot != nullptr) {
        std::vector<Player*> winners = findWinners(curPot);
        if (index == 0 ) {
            std::cout << "Mainpot Winner(s): ";
        }
        else {
            std::cout << "sidePot" << index<< " Winner(s): ";
        }
        for (int i = 0; i < winners.size(); ++i) {
            std::cout << winners[i]->getName() << " ";
        }
        std::cout << "\n";
        distributeCoins(winners, curPot);
        //update pointer
        curPot = curPot->getNextPtr();
    }
}

/*
 *  resetForNextGame() resets fields 
 */
void Game::resetForNextGame() {
    for (Player* player : players) {
        player->setHoleCards();
        player->setCoinBet(0);
        player->setIsFold(false);
        player->setDoneAction(false);
    }
    setCardsOnField();
    setCommunityCards();
    setCardsLeft(generateDeck());
    removeAllPots();
    setHasBet(false);
    setMaxBetting(0);
    setRound(1);
} /* resetForNextGame() */

/*-----------------Game process functions------------------------------*/

/*
 *  requestPlayerNumbers() will asks users how many players they want to play, and return the number.
 */

int requestPlayerNumbers() {
    int playerNum;
    while (1) {
        std::cout << PLAYER_INPUT;
        if ((std::cin >> playerNum) && (playerNum <= MAX_PLAYER && playerNum >= MIN_PLAYER)) {
            std::cout << "Got it! I will make a game with " << playerNum << " other players!\n";
            break;
        }
        else {
            std::cout << INVALID_PLAYER_NUMBER;
            std::cin.clear(); // Clears the error state of cin.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignores the rest of the current line, up to '\n' or EOF.
        }
    }
    return playerNum;
} /* playerInputLoop() */

/*
 *  initializePlayers() initializes a vector of Player pointers.
 */

void Game::initializePlayers() {
    std::vector<Player*> players;
    for (int i = 1; i < players.size(); ++i) {
        std::string playerName = "player" + std::to_string(i);
        Player* player = new Player(playerName, 10000);
        players.push_back(player);
    }
    Player* user = new Player("user", 10000);
    players.push_back(user);

    setPlayers(players);
} /* initializePlayers() */

void Game::freePlayers() {
    // Iterate through the vector of player pointers and delete each one
    for (Player* player : players) {
        delete player;  // Free the memory allocated for each player
    }
    players.clear();  // Clear the vector of pointers after deleting all objects
}

/*
 *  printPlyerOrder() prints the players in order.
 */

void Game::printPlayerOrder() {
    for (Player* player : players) {
        std::cout << player->getName() << " ";
    }
    std::cout << "\n";
} /* printPlayerOrder() */

/*
 *  makeDoneActionFalse() makes everyone's makeDone to False. 
 *  It is used when someone bets or raises.
 */

void Game::makeDoneActionFalse() {
    for (Player* player : players) {
        player->setDoneAction(false);
    }
} /* makeDoneActionFalse() */

/*
 *  isPlayerAllDone() checks whether players done action or not.
 */

bool Game::isPlayerAllDone() {
    for (Player* player : players) {
        if (!player->getDoneAction() && !player->getIsFold()) {
            return false;
        }
    }
    return true;
} /* isPlayerAllDone() */

bool Game::isOnlyOnePlayerLeft() {
    int numFold = 0;
    for (Player* player : players) {
        if (player->getIsFold()) {
            numFold++;
        }
    }
    if (numFold == playerNumber) {
        throw std::runtime_error("At least one player should not be fold. Game invalid");
    }
    if (numFold == (playerNumber - 1)) {
        std::cout << "only one player left!\n";
        return true;
    }
    return false;
} /* isOnlyOnePlayerLeft() */

bool Game::hasAllIn() {
    for (Player* player : players) {
        if (player->getIsAllIn()) {
            return true;
        }
    }
    return false;
}

Pot* Game::createNewPot() {
    Pot* newPot = new Pot;
    newPot->setAmount(0);
    newPot->setThreshold(0);
    newPot->setNextPtr(nullptr);
    newPot->setPrevPtr(nullptr);

    if (*pots == nullptr) {
        // If there are no pots yet, initialize pots with newPot
        *pots = newPot;
    } else {
        // Otherwise, find the last pot in the list and add the new pot
        Pot* currentPot = *pots;
        while (currentPot->getNextPtr() != nullptr) {
            currentPot = currentPot->getNextPtr();
        }
        currentPot->setNextPtr(newPot);
        newPot->setPrevPtr(currentPot);
    }

    return newPot;
}

void Game::removeAllPots() {
    Pot* currentPot = *pots;
    while (currentPot != nullptr) {
        Pot* nextPot = currentPot->getNextPtr();
        delete currentPot;
        currentPot = nextPot;
    }
    *pots = nullptr; // head Pointer to null
}



/*-------currently not in use ------------*/
/*
std::vector<std::string> Game::eraseCommon() {
    std::vector<std::string> deck = generateDeck();

    // Use a manual loop to iterate and remove items
    for (int i = 0; i < deck.size(); ++i) {
        bool found = false;
        for (const auto& fieldCard : cardsOnField) {
            if (deck[i] == fieldCard) {
                found = true;
                break;
            }
        }
        if (found) {
            deck.erase(deck.begin() + i);
            i--;  // Decrement index to adjust for the shift in elements
        }
    }
    return deck;
}
*/