#include "Player.h"

/*---------------Array Processing Functions---------------------------------*/

/*
 *  convertNumbers() changes the character number to integer number.
 *  'A', which is 1 in general, is considered 14 for convenience.
 */

int Player::convertNumbers(char rank) {
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
} /* convertNumbers() */

/*
 *  convertHandToNumbers() converts a vector of card strings to
 *  a vector of integer card values.
 */

std::vector<int> Player::convertHandToNumbers(const std::vector<std::string>& hand) {
    std::vector<int> numbers;
    for (const std::string& card : hand) {
        if (card.size() != 2) {
            throw std::invalid_argument("wrong hand format");
        }
        int number = Player::convertNumbers(card[0]);
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
    std::unordered_set<char> suitSet = {'C', 'S', 'D', 'H'};
    for (const std::string& card : hand) {
        if (card.size() != 2) {
            throw std::invalid_argument("wrong hand format");
        }
        char suit = card[1];
        if (suitSet.find(suit) != suitSet.end()) {
            suits.push_back(suit);
        }
        else {
            throw std::invalid_argument("wrong suit");
        }
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
 *  isTwoPair() checks whether the hand has two pairs or not.
 */

bool Player::isTwoPair(const std::vector<std::string>& communityCards) {
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
} /* isTwoPair() */

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

    // Remove duplicates
    auto it = std::unique(numbers.begin(), numbers.end());
    numbers.erase(it, numbers.end());

    if (numbers.size() < 5) return false;

    // Check standard straight
    for (size_t i = 0; i <= numbers.size() - 5; ++i) {
        if (std::is_sorted(numbers.begin() + i, numbers.begin() + i + 5) &&
            numbers[i + 4] - numbers[i] == 4) {
            return true;
        }
    }

    // Check for a wheel straight: Ace - 2 - 3 - 4 - 5
    return numbers[0] == 2 && numbers[1] == 3 && numbers[2] == 4
           && numbers[3] == 5 && numbers[4] == 14;


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
    std::vector<int> numbers = convertHandToNumbers(completeHand);
    std::map<int, int> counts;

    for (int number : numbers) {
        counts[number]++;
    }

    bool hasThreeOfAKind = false;
    bool hasPair = false;
    int tripleValue = 0;

    // Check for three of a kind
    for (const auto& count : counts) {
        if (count.second >= 3) {
            hasThreeOfAKind = true;
            tripleValue = count.first;
            break;
        }
    }

    // Check for a pair, ensuring it's not the same as the triple
    for (const auto& count : counts) {
        if (count.first != tripleValue && count.second >= 2) {
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
    std::vector<int> numbers = convertHandToNumbers(completeHand);
    std::vector<char> suits = convertHandToSuits(completeHand);
    std::vector<std::pair<int, char>> cards;

    for (size_t i = 0; i < numbers.size(); ++i) {
        cards.push_back({numbers[i], suits[i]});
    }

    // Sort cards by number
    std::sort(cards.begin(), cards.end());

    // Check for straight flush
    for (size_t i = 0; i <= cards.size() - 5; ++i) {
        bool isSequential = true;
        bool isSameSuit = true;
        for (size_t j = i + 1; j < i + 5; ++j) {
            if (cards[j].first != cards[j - 1].first + 1 || cards[j].second != cards[i].second) {
                isSequential = false;
                break;
            }
        }
        if (isSequential && isSameSuit) {
            return true;
        }
    }

    return false;
} /* isStraightFlush() */

/*
 *  isRoyalFlush() checks if the hand is a Royal Flush.
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
            // Check if the highest cards are 10, J, Q, K, A
            auto it = std::find(nums.begin(), nums.end(), 10);
            if (it != nums.end() && it + 4 < nums.end() &&
                *(it + 1) == 11 && *(it + 2) == 12 && *(it + 3) == 13 && *(it + 4) == 14) {
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
 *  Should be in order from highest hand to lowest hand because
 *  the higher ranked hand counts the lower rank as well if true.
 */

Hands Player::determineHand(const std::vector<std::string>& hand) {

    if (isRoyalFlush(hand)) return Hands::RoyalFlush;
    if (isStraightFlush(hand)) return Hands::StraightFlush;
    if (isFourOfAKind(hand)) return Hands::FourOfAKind;
    if (isFullHouse(hand)) return Hands::FullHouse;
    if (isFlush(hand)) return Hands::Flush;
    if (isStraight(hand)) return Hands::Straight;
    if (isThreeOfAKind(hand)) return Hands::ThreeOfAKind;
    if (isTwoPair(hand)) return Hands::TwoPair;
    if (isOnePair(hand)) return Hands::OnePair;
    return Hands::NoMatch;
} /* determineHand() */

std::string Player::handsToString(Hands hand) {
    switch(hand) {
        case Hands::NoMatch: return "NoMatch";
        case Hands::OnePair: return "OnePair";
        case Hands::TwoPair: return "TwoPair";
        case Hands::ThreeOfAKind: return "ThreeOfAKind";
        case Hands::Straight: return "Straight";
        case Hands::Flush: return "Flush";
        case Hands::FullHouse: return "FullHouse";
        case Hands::FourOfAKind: return "FourOfAKind";
        case Hands::StraightFlush: return "StraightFlush";
        case Hands::RoyalFlush: return "RoyalFlush";
        default: return "Unknown";
    }
}

/*
 *  betting() makes betting for the player.
 */

void Player::betting(int amount, Game& game) {
    // add to game totalCoin
    // change maxBetting if bigger than current
    // add to the player betting amount
    // need to remove the amount from the player's coin
    game.setTotalCoin(game.getTotalCoin() + amount);
    if (amount > game.getMaxBetting()) {
        game.setMaxBetting(amount);
    }
    setCoinBet(getCoinBet() + amount);
    setCoin(getCoin() - amount);
} /* betting() */

/*
 *  chooseAction() will choose what action to choose in the current round.
 */
int Player::chooseAction() {
    // for now, I will choose randomly
    // after making statistical tool, this choice will be based on statistical result
    static std::mt19937 rng(std::random_device{}());  // Random number generator

    // Uniform distribution from 0 to 99 (100 possibilities)
    std::uniform_int_distribution<> dist(0, 99);

    // Generate a random number from the distribution
    int randomNumber = dist(rng);

    // Return 1 if the number is less than 80 (80% chance), else return 2
    return randomNumber < 80 ? 1 : 2;
} /* chooseAction() */

/*
 *  doAction() 
 */

void Player::doAction(int action, Game& game) {
    int amount; // Declare outside to avoid bypass
    switch (action) {
        case 1: // check
            if (getCoinBet() < game.getMaxBetting()) {
                amount = game.getMaxBetting() - getCoinBet();
                betting(amount, game);
            }
            std::cout << getName() << ": check\n";
            break;
        case 2: // fold
            setFold(true);
            game.setCheck(game.getCheck() - 1);
            std::cout << getName() << ": fold\n";
            break;
        default:
            throw std::invalid_argument("Invalid Action code received.");
    }
}
