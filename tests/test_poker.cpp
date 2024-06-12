#include <gtest/gtest.h>
#include "../src/Poker.h"

// Test numberConversion
TEST(NumberConversionTest, ValidRanks) {
    EXPECT_EQ(numberConversion('2'), 2);
    EXPECT_EQ(numberConversion('9'), 9);
    EXPECT_EQ(numberConversion('T'), 10);
    EXPECT_EQ(numberConversion('J'), 11);
    EXPECT_EQ(numberConversion('Q'), 12);
    EXPECT_EQ(numberConversion('K'), 13);
    EXPECT_EQ(numberConversion('A'), 14);
}

TEST(NumberConversionTest, InvalidRank) {
    EXPECT_THROW(numberConversion('X'), std::invalid_argument);
}

// Test convertHandToNumbers
TEST(ConvertHandToNumbersTest, ValidHand) {
    std::vector<std::string> hand = {"2H", "3D", "5S", "9C", "KD"};
    std::vector<int> expected = {2, 3, 5, 9, 13};
    EXPECT_EQ(convertHandToNumbers(hand), expected);
}

// Test convertHandToSuits
TEST(ConvertHandToSuitsTest, ValidHand) {
    std::vector<std::string> hand = {"2H", "3D", "5S", "9C", "KD"};
    std::vector<char> expected = {'H', 'D', 'S', 'C', 'D'};
    EXPECT_EQ(convertHandToSuits(hand), expected);
}

// Test isOnePair
TEST(IsOnePairTest, ValidHand) {
    std::vector<std::string> hand = {"2H", "2D", "5S", "9C", "KD"};
    EXPECT_TRUE(isOnePair(hand));
    hand = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(isOnePair(hand));
}

// Test isTwoPairs
TEST(IsTwoPairsTest, ValidHand) {
    std::vector<std::string> hand = {"2H", "2D", "5S", "5C", "KD"};
    EXPECT_TRUE(isTwoPairs(hand));
    hand = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(isTwoPairs(hand));
}

// Test isThreeOfAKind
TEST(IsThreeOfAKindTest, ValidHand) {
    std::vector<std::string> hand = {"2H", "2D", "2S", "9C", "KD"};
    EXPECT_TRUE(isThreeOfAKind(hand));
    hand = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(isThreeOfAKind(hand));
}

// Test isStraight
TEST(IsStraightTest, ValidHand) {
    std::vector<std::string> hand = {"2H", "3D", "4S", "5C", "6D"};
    EXPECT_TRUE(isStraight(hand));
    hand = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(isStraight(hand));
}

// Test isFlush
TEST(IsFlushTest, ValidHand) {
    std::vector<std::string> hand = {"2H", "4H", "6H", "8H", "TH"};
    EXPECT_TRUE(isFlush(hand));
    hand = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(isFlush(hand));
}

// Test isFullHouse
TEST(IsFullHouseTest, ValidHand) {
    std::vector<std::string> hand = {"2H", "2D", "2S", "5C", "5D"};
    EXPECT_TRUE(isFullHouse(hand));
    hand = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(isFullHouse(hand));
}

// Test isFourOfAKind
TEST(IsFourOfAKindTest, ValidHand) {
    std::vector<std::string> hand = {"2H", "2D", "2S", "2C", "KD"};
    EXPECT_TRUE(isFourOfAKind(hand));
    hand = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(isFourOfAKind(hand));
}

// Test isStraightFlush
TEST(IsStraightFlushTest, ValidHand) {
    std::vector<std::string> hand = {"2H", "3H", "4H", "5H", "6H"};
    EXPECT_TRUE(isStraightFlush(hand));
    hand = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(isStraightFlush(hand));
}

// Test isRoyalFlush
TEST(IsRoyalFlushTest, ValidHand) {
    std::vector<std::string> hand = {"TH", "JH", "QH", "KH", "AH"};
    EXPECT_TRUE(isRoyalFlush(hand));
    hand = {"2H", "3D", "5S", "9C", "KD"};
    EXPECT_FALSE(isRoyalFlush(hand));
}

// Test determineHand
TEST(DetermineHandTest, ValidHands) {
    EXPECT_EQ(determineHand({"TH", "JH", "QH", "KH", "AH"}), "Royal Flush");
    EXPECT_EQ(determineHand({"9H", "TH", "JH", "QH", "KH"}), "Straight Flush");
    EXPECT_EQ(determineHand({"2H", "2D", "2S", "2C", "KD"}), "Four of a Kind");
    EXPECT_EQ(determineHand({"2H", "2D", "2S", "5C", "5D"}), "Full House");
    EXPECT_EQ(determineHand({"2H", "4H", "6H", "8H", "TH"}), "Flush");
    EXPECT_EQ(determineHand({"2H", "3D", "4S", "5C", "6D"}), "Straight");
    EXPECT_EQ(determineHand({"2H", "2D", "2S", "9C", "KD"}), "Three of a Kind");
    EXPECT_EQ(determineHand({"2H", "2D", "5S", "5C", "KD"}), "Two Pairs");
    EXPECT_EQ(determineHand({"2H", "2D", "5S", "9C", "KD"}), "One Pair");
    EXPECT_EQ(determineHand({"2H", "3D", "5S", "9C", "KD"}), "High Card");
}

// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
