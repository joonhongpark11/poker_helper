#include <gtest/gtest.h>
#include "../src/Player.h"

// Test numberConversion
TEST(NumberConversionTest, ValidRanks) {
    EXPECT_EQ(Player::numberConversion('2'), 2);
    EXPECT_EQ(Player::numberConversion('9'), 9);
    EXPECT_EQ(Player::numberConversion('T'), 10);
    EXPECT_EQ(Player::numberConversion('J'), 11);
    EXPECT_EQ(Player::numberConversion('Q'), 12);
    EXPECT_EQ(Player::numberConversion('K'), 13);
    EXPECT_EQ(Player::numberConversion('A'), 14);
}

TEST(NumberConversionTest, InvalidRank) {
    EXPECT_THROW(Player::numberConversion('X'), std::invalid_argument);
}

// Test convertHandToNumbers
TEST(ConvertHandToNumbersTest, ValidHand) {
    std::vector<std::string> hand = {"2H", "3D", "5S", "9C", "KD"};
    std::vector<int> expected = {2, 3, 5, 9, 13};
    EXPECT_EQ(Player::convertHandToNumbers(hand), expected);
}

// Test convertHandToSuits
TEST(ConvertHandToSuitsTest, ValidHand) {
    std::vector<std::string> hand = {"2H", "3D", "5S", "9C", "KD"};
    std::vector<char> expected = {'H', 'D', 'S', 'C', 'D'};
    EXPECT_EQ(Player::convertHandToSuits(hand), expected);
}

// Test isOnePair
TEST(IsOnePairTest, ValidHand) {
    Player player = {"player1", 100};
    std::vector<std::string> newHand = {"2H", "8D"};
    player.setHand(newHand);
    //true
    std::vector<std::string> communityCards = {"3H", "2D", "5S", "9C", "KD"};
    EXPECT_TRUE(player.isOnePair(communityCards));
    //false
    communityCards = {"JH", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(player.isOnePair(communityCards));
}

// Test isTwoPairs
TEST(IsTwoPairsTest, ValidHand) {
    Player player = {"player1", 100};
    std::vector<std::string> newHand = {"2H", "5D"};
    player.setHand(newHand);
    //true
    std::vector<std::string> communityCards = {"AH", "2D", "3S", "5C", "KD"};
    EXPECT_TRUE(player.isTwoPairs(communityCards));
    //false
    communityCards = {"AH", "2D", "3S", "JC", "KD"};
    EXPECT_FALSE(player.isTwoPairs(communityCards));
}

// Test isThreeOfAKind
TEST(IsThreeOfAKindTest, ValidHand) {
    Player player = {"player1", 100};
    std::vector<std::string> newHand = {"2H", "5D"};
    player.setHand(newHand);
    //true
    std::vector<std::string> communityCards = {"3H", "2D", "2S", "9C", "KD"};
    EXPECT_TRUE(player.isThreeOfAKind(communityCards));
    //false
    communityCards = {"6H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(player.isThreeOfAKind(communityCards));
}

// Test isStraight
TEST(IsStraightTest, ValidHand) {
    Player player = {"player1", 100};
    std::vector<std::string> newHand = {"2H", "5D"};
    player.setHand(newHand);
    
    //true
    std::vector<std::string> communityCards = {"AH", "3D", "4S", "5C", "6D"};
    EXPECT_TRUE(player.isStraight(communityCards));
    //false
    communityCards = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(player.isStraight(communityCards));
}

// Test isFlush
TEST(IsFlushTest, ValidHand) {
    Player player = {"player1", 100};
    std::vector<std::string> newHand = {"2H", "5D"};
    player.setHand(newHand);
    //true
    std::vector<std::string> communityCards = {"2D", "4H", "6H", "8H", "TH"};
    EXPECT_TRUE(player.isFlush(communityCards));
    //false
    communityCards = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(player.isFlush(communityCards));
}

// Test isFullHouse
TEST(IsFullHouseTest, ValidHand) {
    Player player = {"player1", 100};
    std::vector<std::string> newHand = {"2H", "5H"};
    player.setHand(newHand);
    //true
    std::vector<std::string> communityCards = {"2D", "7D", "2S", "5C", "5D"};
    EXPECT_TRUE(player.isFullHouse(communityCards));
    //false
    communityCards = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(player.isFullHouse(communityCards));
}

// Test isFourOfAKind
TEST(IsFourOfAKindTest, ValidHand) {
    Player player = {"player1", 100};
    std::vector<std::string> newHand = {"2H", "5D"};
    player.setHand(newHand);
    //true
    std::vector<std::string> communityCards = {"4H", "2D", "2S", "2C", "KD"};
    EXPECT_TRUE(player.isFourOfAKind(communityCards));
    //false
    communityCards = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(player.isFourOfAKind(communityCards));
}

// Test isStraightFlush
TEST(IsStraightFlushTest, ValidHand) {
    Player player = {"player1", 100};
    std::vector<std::string> newHand = {"2H", "5D"};
    player.setHand(newHand);
    //true
    std::vector<std::string> communityCards = {"6D", "3D", "4D", "5D", "7D"};
    EXPECT_TRUE(player.isStraightFlush(communityCards));
    //false
    communityCards = {"2C", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(player.isStraightFlush(communityCards));
}

// Test isRoyalFlush
TEST(IsRoyalFlushTest, ValidHand) {
    Player player = {"player1", 100};
    std::vector<std::string> newHand = {"TH", "5D"};
    player.setHand(newHand);
    //true
    std::vector<std::string> communityCards = {"JH", "QH", "KH", "AH", "2S"};
    EXPECT_TRUE(player.isRoyalFlush(communityCards));
    //false
    communityCards = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(player.isRoyalFlush(communityCards));
}

// Test determineHand
TEST(DetermineHandTest, ValidHands) {
    Player player = {"player1", 100};
    EXPECT_EQ(player.determineHand({"TH", "JH", "QH", "KH", "AH", "2D"}), "Royal Flush");
    EXPECT_EQ(player.determineHand({"9H", "TH", "JH", "QH", "KH", "3S"}), "Straight Flush");
    EXPECT_EQ(player.determineHand({"2H", "2D", "2S", "2C", "KD", "3S"}), "Four of a Kind");
    EXPECT_EQ(player.determineHand({"2H", "2D", "2S", "5C", "5D", "3S"}), "Full House");
    EXPECT_EQ(player.determineHand({"2H", "4H", "6H", "8H", "TH", "5S"}), "Flush");
    EXPECT_EQ(player.determineHand({"2H", "3D", "4S", "5C", "6D", "AS"}), "Straight");
    EXPECT_EQ(player.determineHand({"2H", "2D", "2S", "9C", "KD", "7C"}), "Three of a Kind");
    EXPECT_EQ(player.determineHand({"2H", "2D", "5S", "5C", "KD", "3H"}), "Two Pairs");
    EXPECT_EQ(player.determineHand({"2H", "2D", "5S", "9C", "KD", "7H"}), "One Pair");
    EXPECT_EQ(player.determineHand({"2H", "3D", "5S", "9C", "KD", "AS"}), "No Match");
}

// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
