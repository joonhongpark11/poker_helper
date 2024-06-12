#include "game.h"

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