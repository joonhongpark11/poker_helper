#include "Player.h"

/*---------------Array Processing Functions---------------------------------*/

/*
 *  numberConversion() changes the character number to integer number.
 *  'A', which is 1 in general, is considered 14 for convenience.
 */

int Player::numberConversion(char rank) {
    if (rank >= '2' && rank <= '9') {
        return rank - '0';  // Converts '2'-'9' to their respective integers
    }
    switch (rank) {
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        case 'A': return 14;
        default:
            throw std::invalid_argument("Invalid character for rank");
    }
} /* numberConversion() */

/*
 *  convertHandToNumbers() converts a vector of card strings to
 *  a vector of integer card values.
 */

std::vector<int> Player::convertHandToNumbers(const std::vector<std::string>& hand) {
    std::vector<int> numbers;
    for (const std::string& card : hand) {
        int number = Player::numberConversion(card[0]);
        numbers.push_back(number);
    }
    return numbers;
} /* convertHandToNumbers() */

/*
 *  convertHandToSuits() converts a vector of card strings to
 *  a vector of character suit values.
 */

std::vector<char> Player::convertHandToSuits(const std::vector<std::string>& hand) {
    std::vector<char> suits;
    for (const std::string& card : hand) {
        suits.push_back(card[1]);
    }
    return suits;
} /* convertHandToSuits() */

/*
 *  makeCompleteHand() adds community cards and hole Cards.
 */

std::vector<std::string> Player::makeCompleteHand(const std::vector<std::string>& communityCards) {
    std::vector<std::string> completeHand;
    completeHand.insert(completeHand.end(), communityCards.begin(), communityCards.end());
    completeHand.insert(completeHand.end(), holeCards.begin(), holeCards.end());

    return completeHand;
} /* makeCompleteHand() */

/*---------------Hand Detection Boolean Functions---------------------------*/

/*
 *  isOnePair() checks whether the hand has one pair or not.
 */   

bool Player::isOnePair(const std::vector<std::string>& communityCards) {
    std::vector<std::string> completeHand = makeCompleteHand(communityCards);
    std::vector<int> numbers = Player::convertHandToNumbers(completeHand);
    
    std::map<int, int> counts;
    for (int number : numbers) {
        counts[number]++;
    }
    for (const auto& count : counts) {
        if (count.second == 2) {
            return true;
        }
    }
    return false;
} /* isOnePair() */

/*
 *  isTwoPairs() checks whether the hand has two pairs or not.
 */

bool Player::isTwoPairs(const std::vector<std::string>& communityCards) {
    std::vector<std::string> completeHand = makeCompleteHand(communityCards);
    std::vector<int> numbers = convertHandToNumbers(completeHand);
    std::map<int, int> counts;
    int pairCount = 0;
    for (int number : numbers) {
        counts[number]++;
    }
    for (const auto& count : counts) {
        if (count.second == 2) {
            pairCount++;
            if (pairCount >= 2) {
                return true;
            }
        }
    }
    return false;
} /* isTwoPairs() */

/*
 *  isThreeOfAKind() checks whether the hand has triple or not.
 */

bool Player::isThreeOfAKind(const std::vector<std::string>& communityCards) {
    std::vector<std::string> completeHand = makeCompleteHand(communityCards);
    std::vector<int> numbers = convertHandToNumbers(completeHand);
    std::map<int, int> counts;
    for (int number : numbers) {
        counts[number]++;
    }
    for (const auto& count : counts) {
        if (count.second == 3) {
            return true;
        }
    }
    return false;
} /* isThreeOfAKind() */

/*
 *  isStraight() checks whether the hand has a straight or not.
 */

bool Player::isStraight(const std::vector<std::string>& communityCards) {
    std::vector<std::string> completeHand = makeCompleteHand(communityCards);
    std::vector<int> numbers = convertHandToNumbers(completeHand);
    std::sort(numbers.begin(), numbers.end());

    // auto is std::vector<int>::iterator
    // make it unique so that it doesn't count consecutive same numbers
    auto it = std::unique(numbers.begin(), numbers.end());
    // Erase the undefined elements after removing duplicates
    numbers.erase(it, numbers.end());
    if (numbers.size() < 5) {
        return false;
    }

    for (size_t i = 0; i <= numbers.size() - 5; ++i) {
        bool regularStraight = true;
        // check 5 consecutive sequence
        for (size_t j = i + 1; j < i + 5; ++j) {
            if (numbers[j] != numbers[j - 1] + 1) {
                regularStraight = false;
                break;
            }
        }

        if (regularStraight) {
            return true;
        }

        // Special case: Ace as low (A-2-3-4-5)
        if (i == 0 && numbers[0] == 2 && numbers[1] == 3 &&
                numbers[2] == 4 && numbers[3] == 5 && numbers.back() == 14) {
            return true;
        }
    }
    return false;
} /* isStraight() */

/*
 *  isFlush() checks whether the hand has flush or not.
 */

bool Player::isFlush(const std::vector<std::string>& communityCards) {
    std::vector<std::string> completeHand = makeCompleteHand(communityCards);
    std::vector<char> suits = convertHandToSuits(completeHand);
    std::map<char, int> counts;
    for (char suit : suits) {
        counts[suit]++;
        if (counts[suit] >= 5) {
            return true;
        }
    }
    return false;
} /* isFlush() */

/*
 *  isFullHouse() checks whether the hand is fullhouse or not.
 */

bool Player::isFullHouse(const std::vector<std::string>& communityCards) {
    std::vector<std::string> completeHand = makeCompleteHand(communityCards);
    if (completeHand.size() < 5) {
        return false;
    }

    std::vector<int> numbers = convertHandToNumbers(completeHand);
    std::map<int, int> counts;
    for (int number : numbers) {
        counts[number]++;
    }
    bool hasThreeOfAKind = false;
    bool hasPair = false;

    for (const auto& entry : counts) {
        if (entry.second >= 3) {
            hasThreeOfAKind = true;
            counts[entry.first] -= 3;
            break;
        }
    }

    for (const auto& entry : counts) {
        if (entry.second >= 2) {
            hasPair = true;
            break;
        }
    }

    return hasThreeOfAKind && hasPair;
} /* isFullHouse() */

/*
 *  isFourOfAKind() checks whether the hand has quad or not.
 */

bool Player::isFourOfAKind(const std::vector<std::string>& communityCards) {
    std::vector<std::string> completeHand = makeCompleteHand(communityCards);
    std::vector<int> numbers = convertHandToNumbers(completeHand);
    std::map<int, int> counts;
    for (int number : numbers) {
        counts[number]++;
    }
    for (const auto& count : counts) {
        if (count.second == 4) {
            return true;
        }
    }
    return false;
} /* isFourOfAKind() */

/*
 *  isStraightFlush() checks if the hand is both straight and flush.
 */
bool Player::isStraightFlush(const std::vector<std::string>& communityCards) {
    std::vector<std::string> completeHand = makeCompleteHand(communityCards);
    return isStraight(completeHand) && isFlush(completeHand);
} /* isStraightFlush() */

/*
 *  isRoyalFlush() checks if the hand is royalFlush.
 */

bool Player::isRoyalFlush(const std::vector<std::string>& communityCards) {
    std::vector<std::string> completeHand = makeCompleteHand(communityCards);
    std::vector<int> numbers = convertHandToNumbers(completeHand);
    std::vector<char> suits = convertHandToSuits(completeHand);

    std::map<char, std::vector<int>> suitToNumbers;
    for (size_t i = 0; i < numbers.size(); ++i) {
        suitToNumbers[suits[i]].push_back(numbers[i]);
    }

    for (auto& entry : suitToNumbers) {
        std::vector<int>& nums = entry.second;
        std::sort(nums.begin(), nums.end());
        if (nums.size() >= 5) {
            if (nums[0] == 10 && nums[1] == 11 && nums[2] == 12 && nums[3] == 13 && nums[4] == 14) {
                return true;
            }
        }
    }
    return false;
} /* isRoyalFlush() */

/*
 *  compareHighest() compares the highest value when two hands 
 *  have the same value. If the number is still a draw,
 *  it returns 0.
 */

int Player::compareHighest(const std::vector<std::string>& hand1,
                const std::vector<std::string>& hand2) {
    std::vector<int> num_1 = convertHandToNumbers(hand1);
    std::vector<int> num_2 = convertHandToNumbers(hand2);

    std::sort(num_1.begin(), num_1.end(), std::greater<int>());
    std::sort(num_2.begin(), num_2.end(), std::greater<int>());
    
    for (size_t i = 0; i < num_1.size(); ++i) {
        if (num_1[i] > num_2[i]) return 1;
        else if (num_1[i] < num_2[i]) return 2;
    }
    return 0;
} /* compareHighest() */

/*
 *  determineHand() will determine what hand the player has.
 */

std::string Player::determineHand(const std::vector<std::string>& hand) {
    if (isRoyalFlush(hand)) return "Royal Flush";
    if (isStraightFlush(hand)) return "Straight Flush";
    if (isFourOfAKind(hand)) return "Four of a Kind";
    if (isFullHouse(hand)) return "Full House";
    if (isFlush(hand)) return "Flush";
    if (isStraight(hand)) return "Straight";
    if (isThreeOfAKind(hand)) return "Three of a Kind";
    if (isTwoPairs(hand)) return "Two Pairs";
    if (isOnePair(hand)) return "One Pair";
    return "No Match";
} /* determineHand() */