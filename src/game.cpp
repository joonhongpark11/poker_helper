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

/*
 * pickRandomCard() picks a random card from 'cardsLeft' and moves it to 'cardsOnField'.
 */
std::string Game::pickRandomCard(std::vector<std::string>& cardsOnField, std::vector<std::string>& cardsLeft) {
    static std::mt19937 rdm(std::time(nullptr));  // Static to initialize seed only once

    if (!cardsLeft.empty()) {
        std::shuffle(cardsLeft.begin(), cardsLeft.end(), rdm);
        std::string selectedCard = cardsLeft.back();
        cardsLeft.pop_back();

        cardsOnField.push_back(selectedCard);
        return selectedCard;
    }

    return ""; // Return empty string when no cards are left
} /* pickRandomCard() */


int Game::draw(std::vector<std::string>& cardsLeft, std::vector<std::string>& cardsOnField, Player& p) {
    if (cardsLeft.size() < 2) {
        return ERROR;
    }

    std::string card1 = pickRandomCard(cardsOnField, cardsLeft);
    std::string card2 = pickRandomCard(cardsOnField, cardsLeft);
    /*
    p.hand.push_back(card1);
    p.hand.push_back(card2);
    */

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

