#include <gtest/gtest.h>
#include "../src/Game.h"

// Test generateDeck()
TEST(generateDeckTest, ValidDeck) {
    Game game = {5, 15};
    std::vector<std::string> deck = game.generateDeck();

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

//Test  pickRandomCard()
TEST(pickRandomCardTest, wellPicked) {
    Game game = {5, 15};
    for (int i = 0; i < 52; ++i) {
        std::string pickedCard = game.pickRandomCard();
        EXPECT_FALSE(pickedCard.empty());
        EXPECT_EQ(game.getCardsLeft().size() + game.getCardsOnField().size(), 52);
    }
    // After 52 picks, cardsLeft should be empty
    EXPECT_TRUE(game.getCardsLeft().empty());

    std::string pickedCard = game.pickRandomCard();
    EXPECT_EQ(pickedCard, "");
}


// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}