#include "game.h"

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
 *  generateDeck() will generates a full 52 cards deck.
 */

std::vector<std::string> generateDeck() {
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
 *  pickRandomCard() picks a random card excluding cards already picked.
 */

std::string pickRandomCard(std::vector<std::string>& cardsOnField) {
    std::vector<std::string> deck = generateDeck();

    static std::mt19937 rdm(std::time(nullptr));  // Static to initialize seed only once

    // Remove cards that are on the field
    for (const std::string& card : cardsOnField) {
        auto it = std::find(deck.begin(), deck.end(), card);
        if (it != deck.end()) {
            deck.erase(it);
        }
    }

    std::shuffle(deck.begin(), deck.end(), rdm);

    if (!deck.empty()) {
        return deck.front();
    }
    return ""; // empty string when all the cards are used
} /* pickRandomCard() */

/*
 *  removeFromDeck() adds a card to cardsOnField vector. 
 */
void removeFromDeck(const std::string& card, std::vector<std::string>& cardsOnField) {
    cardsOnField.push_back(card);
}