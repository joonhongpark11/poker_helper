#include <gtest/gtest.h>
#include "../src/game.h"

// Test generateDeck
TEST(generateDeckTest, ValidDeck) {
    std::vector<std::string> deck = generateDeck();

    // Check that the deck has 52 cards
    ASSERT_EQ(deck.size(), 52) << "Deck should contain exactly 52 cards";

    // Check that all cards are unique
    std::set<std::string> uniqueCards(deck.begin(), deck.end());
    ASSERT_EQ(uniqueCards.size(), 52) << "All cards in the deck must be unique";

    // Check that each card is valid
    char numbers[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    char suits[] = {'D', 'H', 'C', 'S'};
    for (const auto& card : deck) {
        bool validCard = false;
        for (char number : numbers) {
            for (char suit : suits) {
                if (card == std::string(1, number) + suit) {
                    validCard = true;
                    break;
                }
            }
            if (validCard) break;
        }
        ASSERT_TRUE(validCard) << "Invalid card found: " << card;
    }
}

// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}