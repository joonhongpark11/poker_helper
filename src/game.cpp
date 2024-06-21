#include "Game.h"
#include "Player.h"

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

std::vector<std::string> Game::eraseCommon() {
    std::vector<std::string> deck = generateDeck();
    std::vector<std::string> fieldCards = getCardsOnField();

    // Use a manual loop to iterate and remove items
    for (int i = 0; i < deck.size(); ++i) {
        bool found = false;
        for (const auto& fieldCard : fieldCards) {
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

/*
 * pickRandomCard() picks a random card from 'cardsLeft' and moves it to 'cardsOnField'.
 */
std::string Game::pickRandomCard() {
    std::vector<std::string> currentDeck = eraseCommon();

    static std::mt19937 rdm(std::time(nullptr));  // Static to initialize seed only once

    if (!currentDeck.empty()) {
        std::shuffle(currentDeck.begin(), currentDeck.end(), rdm);
        std::string selectedCard = currentDeck.back();

        std::vector<std::string> fieldCards = getCardsOnField();
        fieldCards.push_back(selectedCard);
        setCardsOnField(fieldCards);

        return selectedCard;
    }

    return ""; // Return empty string when no cards are left
}


int Game::drawHoleCard(Player& p) {
    std::string card1 = pickRandomCard();
    std::string card2 = pickRandomCard();
    p.setHoleCards({card1, card2});

    return OK;
}


/*
 *  playerInputLoop() will asks users how many players they want to play, and return the number.
 */

int playerInputLoop() {
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
 *  chooseDealerPosition() choose the initial position of the dealer.
 */

int Game::chooseDealerPosition(int playerNumber) {
    // Static random number generator
    // This rng will be initialized only once across multiple calls
    static std::mt19937 rng(std::random_device{}());

    // Uniform distribution from 0 to playerNumber
    std::uniform_int_distribution<> dist(1, playerNumber + 1);

    // Generate and return a random number from the distribution
    return dist(rng);
} /* chooseDealerPosition() */

/*
 *  playerSort() will sort the playerlist based on the dealer position.
 */

std::vector<Player> Game::playerSort(std::vector<Player>& players, int dealerPosition) {
    std::vector<Player> temp;
    for (int i = 0; i < dealerPosition - 1; ++i) {
        temp.push_back(players[i]);
    }
    std::vector<Player> newPlayers;
    for (int i = dealerPosition - 1; i < players.size(); ++i) {
        newPlayers.push_back(players[i]);
    }
    
    // Insert all elements of temp at the end of newPlayers
    newPlayers.insert(newPlayers.end(), temp.begin(), temp.end());

    return newPlayers;
} /* playerSort() */


void Game::checkGameStat(std::vector<Player>& players) {
    std::cout << "Game stats:\n";
    std::cout << "playerNumber: " << getPlayerNumber() << "\n";
    std::cout << "totalCoin: " << getTotalCoin() << "\n";
    std::cout << "smallBlind: " << getSmallBlind() << "\n";
    std::cout << "maxBetting: " << getMaxBetting() << "\n";

    std::cout << "Player Stats:\n";
    for (auto player : players) {
        std::cout << player.getName() << ":\n";
        std::cout << "coin: " << player.getCoin() << ", ";
        std::cout << "coinBet: " << player.getCoinBet() << ", ";
        std::cout << "holeCards: ";
        for (auto card : player.getHoleCards()) {
            std::cout << card << " ";
        }
        std:: cout << ", ";
        std::cout << "Fold: " << player.getFold() << "\n";
    }
    std::cout << "Checks: " << getCheck() << "\n";
}



/*
 *  compareHighest() compares the highest value when two hands 
 *  have the same value. If the number is still a draw,
 *  it returns 0.
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
}

// Function to find the winner among multiple players, returns vector of winner indices
std::vector<Player> Game::findWinners(std::vector<Player>& players) {
    std::vector<std::vector<std::string>> playersHands;
    for (auto& player : players) {
        playersHands.push_back(player.makeCompleteHand(getCommunityCards()));
    }

    std::vector<Player> winners;
    if (!players.empty()) {
        winners.push_back(players[0]); // Start by assuming the first player is the winner
    }

    for (size_t i = 1; i < playersHands.size(); ++i) {
        int result = compareHands(winners.front().makeCompleteHand(getCommunityCards()), playersHands[i]);
        if (result < 0) {
            winners.clear();
            winners.push_back(players[i]);
        } else if (result == 0) {
            winners.push_back(players[i]);  // Add this player to winners if it's a draw
        }
    }

    return winners;
}

// to make: 
//  findBestFiveCardHand
// compareHighest --> when two or more people have the same highest hands,
// compare the best 5 cards and check whos the winner.
// when they have the same individual cards, then draw. 
// we don't compare the suit in this program. 