#include <gtest/gtest.h>
#include "../src/Player.h"

//example

/*
TEST(test_name, output_setence_for_pass) {
    EXPECT_EQ(value1, value2);
    ASSERT_EQ(value1, value2);
    EXPECT_THROW(value1, throw_type);
}
*/

// convertNumbers() Test
TEST(numberConversionTest, validConversion) {
    //normal numbers
    EXPECT_EQ(Player::convertNumbers('3'), 3);
    EXPECT_EQ(Player::convertNumbers('5'), 5);
    EXPECT_EQ(Player::convertNumbers('9'), 9);

    // letter numbers
    EXPECT_EQ(Player::convertNumbers('T'), 10);
    EXPECT_EQ(Player::convertNumbers('J'), 11);
    EXPECT_EQ(Player::convertNumbers('Q'), 12);
    EXPECT_EQ(Player::convertNumbers('K'), 13);
    EXPECT_EQ(Player::convertNumbers('A'), 14);

    // invalid number
    EXPECT_THROW(Player::convertNumbers('0'), std::invalid_argument);
}

// convertHandToNumbers() Test
TEST(convertHandToNumbersTest, validNumberConversion) {
    //correct input
    std::vector<std::string> hand = {"AC", "JD", "3H", "5C", "9S", "KS"};
    std::vector<int> expectedResult = {14, 11, 3, 5, 9, 13};
    EXPECT_EQ(Player::convertHandToNumbers(hand), expectedResult);

    //wrong input
    std::vector<std::string> hand2 = {"AC", "JD", "3H", "5C", "9S", "KS", "S"};
    EXPECT_THROW(Player::convertHandToNumbers(hand2), std::invalid_argument);
}

// convertHandToSuits() Test
TEST(convertHandToSuitsTest, validSuitConversion) {
    //correct input
    std::vector<std::string> hand = {"AC", "JD", "3H", "5C", "9S", "KS"};
    std::vector<char> expectedResult = {'C', 'D', 'H', 'C', 'S', 'S'};
    EXPECT_EQ(Player::convertHandToSuits(hand), expectedResult);

    //wrong suit
    std::vector<std::string> hand2 = {"AC", "JD", "3H", "5C", "9S", "KT"};
    EXPECT_THROW(Player::convertHandToSuits(hand2), std::invalid_argument);

    //wrong format
    std::vector<std::string> hand3 = {"AC", "JD", "3H", "5C", "9S", "T"};
    EXPECT_THROW(Player::convertHandToSuits(hand3), std::invalid_argument);
}

// makeCompleteHand() Test
TEST(makeCompleteHandTest, validCompleteHand) {
    Player player = {"Joon", 1000};
    player.setHoleCards({"3D", "8C"});

    //correct input
    std::vector<std::string> communityCards = {"AC", "JD", "3H", "5C", "9S"};
    std::vector<std::string> expectedResult = {"AC", "JD", "3H", "5C", "9S", "3D", "8C"};
    EXPECT_EQ(player.makeCompleteHand(communityCards), expectedResult);
}

// isOnePair() Test
TEST(isOnePairTest, validOnePair) {
    Player player = {"Joon", 1000};
    player.setHoleCards({"3D", "8C"});

    //correct input
    std::vector<std::string> communityCards = {"AC", "JD", "3H", "5C", "9S"};
    EXPECT_EQ(player.isOnePair(communityCards), true);

    //wrong input
    std::vector<std::string> communityCards2 = {"AC", "JD", "7H", "5C", "9S"};
    EXPECT_EQ(player.isOnePair(communityCards2), false);
}

// isTwoPair() Test
TEST(isTwoPairTest, validTwoPair) {
    Player player = {"Joon", 1000};
    player.setHoleCards({"3D", "8C"});

    //correct input
    std::vector<std::string> communityCards = {"AC", "JD", "3H", "8C", "9S"};
    EXPECT_EQ(player.isTwoPair(communityCards), true);

    //wrong input
    std::vector<std::string> communityCards2 = {"3C", "JD", "7H", "5C", "9S"};
    EXPECT_EQ(player.isTwoPair(communityCards2), false);
}

// isThreeOfAKind() Test
TEST(isThreeOfAKindTest, validThreeOfAKind) {
    Player player = {"Joon", 1000};
    player.setHoleCards({"3D", "8C"});

    //correct input
    std::vector<std::string> communityCards = {"3C", "JD", "3H", "8C", "9S"};
    EXPECT_EQ(player.isThreeOfAKind(communityCards), true);

    //wrong input
    std::vector<std::string> communityCards2 = {"AC", "JD", "3H", "8C", "9S"};
    EXPECT_EQ(player.isThreeOfAKind(communityCards2), false);
}

// isStraight() Test
TEST(isStraightTest, validStraight) {
    Player player = {"Joon", 1000};
    player.setHoleCards({"3D", "5C"});

    //correct input
    std::vector<std::string> communityCards = {"4C", "JD", "6H", "7C", "9S"};
    EXPECT_EQ(player.isStraight(communityCards), true);

    // ace as a low
    std::vector<std::string> communityCards2 = {"AC", "4D", "6H", "2C", "9S"};
    EXPECT_EQ(player.isStraight(communityCards2), true);

    //wrong input
    std::vector<std::string> communityCards3 = {"4C", "JD", "JH", "7C", "9S"};
    EXPECT_EQ(player.isStraight(communityCards3), false);
}

// isFlush() Test
TEST(isFlushTest, validFlush) {
    Player player = {"Joon", 1000};
    player.setHoleCards({"3D", "5D"});

    //correct input
    std::vector<std::string> communityCards = {"4D", "JD", "6H", "QD", "9S"};
    EXPECT_EQ(player.isFlush(communityCards), true);

    //wrong input
    std::vector<std::string> communityCards2 = {"4C", "JD", "6H", "QD", "9S"};
    EXPECT_EQ(player.isFlush(communityCards2), false);
}

// isFullHouse() Test
TEST(isFullHouseTest, validFullHouse) {
    Player player = {"Joon", 1000};
    player.setHoleCards({"3D", "5D"});

    //correct input
    std::vector<std::string> communityCards = {"3S", "3H", "5H", "5D", "9S"};
    EXPECT_EQ(player.isFullHouse(communityCards), true);

    //wrong input
    std::vector<std::string> communityCards2 = {"3S", "2H", "JH", "5D", "9S"};
    EXPECT_EQ(player.isFullHouse(communityCards2), false);
}





// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
