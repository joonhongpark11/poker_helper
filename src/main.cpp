#include "Poker.h"

int main() {
    std::vector<std::string> hand = {"2S", "3S", "5S", "9S", "TS", "JD", "QD"};
    std::cout << "The hand is: " << determineHand(hand) << std::endl;
    return 0;
}


