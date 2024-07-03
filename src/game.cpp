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
    for (int i = 0; i < players.size(); ++i) {
        drawHoleCards(players[i]);
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
    std::cout << "totalCoin: " << totalCoin << "\n";
    std::cout << "smallBlind: " << smallBlind << "\n";
    std::cout << "maxBetting: " << maxBetting << "\n";
    std::cout << "round: " << round << "\n";
    std::cout << "cardLeft: " << cardsLeft.size() << "\n";
    std::cout << "cards On Field: " << cardsOnField.size() << "\n";
    std::cout << "Player Stats:\n";
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
    }
} /* checkGameStat() */



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

std::vector<Player*> Game::findWinners() {
    std::vector<std::vector<std::string>> bestHands;  // Stores the best 5-card hands for each player
    std::vector<Player*> activePlayers;  // Store only the active players (those who haven't folded)

    // Iterate through players and filter out the ones who have folded
    for (auto& player : players) {
        if (!player->getIsFold()) {
            // Each player finds their best hand from their complete set of 7 cards
            bestHands.push_back(player->findBestFiveCardHand(player->makeCompleteHand(getCommunityCards())));
            activePlayers.push_back(player);
        }
    }

    std::vector<Player*> winners;
    if (!activePlayers.empty()) {
        winners.push_back(activePlayers[0]);
    }

    // Compare each active player's best hand to find the winner
    for (size_t i = 1; i < activePlayers.size(); ++i) {
        // Correctly refer to the best hands of the currently considered winner and the current player
        int result = compareSameHands(bestHands[winners.front() - activePlayers[0]], bestHands[i]);
        if (result < 0) {
            winners.clear();  // Clear previous winners as a better hand is found
            winners.push_back(activePlayers[i]);  // Push the address of the player
        } else if (result == 0) {
            winners.push_back(activePlayers[i]);  // Add this player to winners if it's a draw
        }
    }

    return winners;
} /* findWinners() */

/*
 *  distributeCoins() dirstributes winning coins to the winners.
 */

void Game::distributeCoins(std::vector<Player*>& winners) {
    int numWinners = winners.size();
    if (numWinners == 0) { // if no winners, which is not possible.
        std::cout << "no winner detected. Please check\n";
        return;
    }

    int coinsPerWinner = getTotalCoin() / numWinners;  // Each winner's equal share
    int remainder = getTotalCoin() % numWinners;       // Remainder if not divisible evenly

    for (int i = 0; i < numWinners; ++i) {
        int additionalCoin = (i < remainder) ? 1 : 0;
        int winnerCoin = winners[i]->getCoin() + coinsPerWinner + additionalCoin;
        winners[i]->setCoin(winnerCoin);
    }
} /* distributeCoins() */

/*
 *  resetForNextGame() resets fields 
 */
void Game::resetForNextGame() {
    for (int i = 0; i < players.size(); ++i) {
        players[i]->setHoleCards();
        players[i]->setCoinBet(0);
        players[i]->setIsFold(false);
        players[i]->setDoneAction(false);
    }
    setCardsOnField();
    setCommunityCards();
    setCardsLeft(generateDeck());
    setTotalCoin(0);
    setHasBet(false);
    setMaxBetting(0);
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
    for (int i = 1; i <= getPlayerNumber() - 1; ++i) {
        std::string playerName = "player" + std::to_string(i);
        Player* player = new Player(playerName, 10000);
        players.push_back(player);
    }
    Player* user = new Player("user", 10000);
    players.push_back(user);

    setPlayers(players);
} /* initializePlayers() */

/*
 *  printPlyerOrder() prints the players in order.
 */

void Game::printPlayerOrder() {
    for (int i = 0; i < players.size(); ++i) {
        std::cout << players[i]->getName() << " ";
    }
    std::cout << "\n";
} /* printPlayerOrder() */

/*
 *  makeDoneActionFalse() makes everyone's makeDone to False. 
 *  It is used when someone bets or raises.
 */

void Game::makeDoneActionFalse() {
    for (int i = 0; i < players.size(); i++) {
        players[i]->setDoneAction(false);
    }
} /* makeDoneActionFalse() */

/*
 *  isPlayerAllDone() checks whether players done action or not.
 */

bool Game::isPlayerAllDone() {
    for (int i = 0; i < playerNumber; ++i) {
        if (!players[i]->getDoneAction() && !players[i]->getIsFold()) {
            return false;
        }
    }
    return true;
} /* isPlayerAllDone() */





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