#include <gtest/gtest.h>
#include "../src/Game.h"

// generateDeck() Test
TEST(generateDeck, generateDeckTest) {
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

// pickRandomCard() Test
TEST(pickRandomCard, pickRandomCardTest) {
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

// drawHoleCards() Test
TEST(drawHoleCards, drawHoleCardsTest) {
    Game game = {5, 15};
    Player player1 = {"p1", 100};

    game.drawHoleCards(&player1);

    EXPECT_EQ(player1.getHoleCards().size(), 2);
}

// setupHoleCards() Test
TEST(setupHoleCards, setupHoleCardsTest) {
    Game game = {5, 15}; // 5 players
    game.setupHoleCards();
    for (int i = 0; i < game.getPlayerNumber(); ++i) {
        EXPECT_EQ(game.getPlayers()[i]->getHoleCards().size(), 2);
    }
}

// sortPlayer() Test
TEST(sortPlayer, sortPlayerTest) {
    Game game = {5 ,15};
    int dealerPosition = 3;
    game.sortPlayer(dealerPosition);
    // user->1->2->3->4
    EXPECT_EQ(game.getPlayers()[0]->getName(), "user");
    EXPECT_EQ(game.getPlayers()[1]->getName(), "player1");
    EXPECT_EQ(game.getPlayers()[2]->getName(), "player2");
    EXPECT_EQ(game.getPlayers()[3]->getName(), "player3");
    EXPECT_EQ(game.getPlayers()[4]->getName(), "player4");
}

// no test for checkGameStat()

// compareHands() Test
TEST(compareHands, compareHandsTest) {
    Game game = {5, 15};
    

    std::vector<std::string> hand1 = {"2H", "5D", "7S", "9C", "KH", "3D", "4S"}; //no pair
    std::vector<std::string> hand2 = {"3H", "3D", "5S", "8C", "KD", "2S", "9H"}; // pair
    EXPECT_EQ(game.compareHands(hand1, hand2), -1);
    EXPECT_EQ(game.compareHands(hand2, hand1), 1);
    EXPECT_EQ(game.compareHands(hand1, hand1), 0);
}

// compareSameHands() Test
TEST(compareSameHands, compareSameHandsTest) {
    Game game = {5, 15};

    //straight same numbers
    std::vector<std::string> hand1 = {"2H", "3D", "4S", "5C", "6H", "7D", "8S"};
    std::vector<std::string> hand2 = {"2C", "3H", "4D", "5S", "6C", "7H", "8D"};
    EXPECT_EQ(game.compareSameHands(hand1, hand2), 0);

    //two pairs, different numbers
    std::vector<std::string> hand3 = {"2H", "3D", "4S", "6C", "6H", "8D", "8S"};
    std::vector<std::string> hand4 = {"2C", "3H", "4D", "5S", "5C", "8H", "8D"};
    EXPECT_EQ(game.compareSameHands(hand3, hand4), 1);

    // same two pairs, but the last one number is different
    std::vector<std::string> hand5 = {"2H", "3D", "4S", "6C", "6H", "8D", "8S"};
    std::vector<std::string> hand6 = {"AC", "2H", "4D", "6S", "6C", "8H", "8D"};
    EXPECT_EQ(game.compareSameHands(hand5, hand6), -1);
}


// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}