#include "Poker.h"
#include "game.h"

int main() {
    std::vector<std::string> hand = {"2S", "3S", "5S", "9S", "TS", "JD", "QD"};
    for (int i = 0; i < 10; ++i) {
        std::cout << pickRandomCard(hand) << i << "\n" ;
    }
    
    return 0;
}


