#include "Player.h"
#include "Game.h"




int main() {
    // greeting
    std::cout << GREETING;

    // playerNumber request (doesn't include user)
    int playerNumber = requestPlayerNumbers();
    
    // player initalization
    std::vector<Player*> players = initializePlayers(playerNumber);

    // game initialization variables
    int dealerPosition = 0;
    int smallBlind = 5;
    bool keepPlaying = true;

    // repeat round
    while (keepPlaying) {
        /*------------------game setup------------------------------*/
        Game game = {playerNumber + 1, smallBlind}; // include user
        std::cout << "Dealer Position is " << players[dealerPosition]->getName() << "\n";
        std::cout << "Here is the List of the player positions.\n";
        game.sortPlayer(players, dealerPosition);
        game.printPlayerOrder(players);
        //small blind
        players[0]->betting(smallBlind, game);
        //big blind
        players[1]->betting(smallBlind * 2, game);

        // setup hole cards
        game.setupHoleCards(players);
        // printing cards for debugging
        for (int i = 0; i < players.size(); ++i) {
            std::cout << players[i]->getName() << " cards: ";
            for (std::string card : players[i]->getHoleCards()) {
                std::cout << card << " ";
            }
            std::cout << "\n";
        }

        /*--------------------round repeating------------------------*/
        int round = 1;
        bool onlyOnePlayer = false;

        while ((round < 5) && (!onlyOnePlayer)) {
            if (round == 2) {
                // draw three cards
                std::vector<std::string> initialSet;
                for (int i = 0; i < 3; ++i) {
                    initialSet.push_back(game.pickRandomCard());
                }
                game.setCommunityCards(initialSet);
                std::cout << "community cards: ";
                for (auto cards : game.getCommunityCards()) {
                    std::cout << cards << " ";
                }
                std::cout << "\n";
            }
            else if ((round == 3) || (round == 4)) {
                // draw one card
                std::vector<std::string> newSet = game.getCommunityCards();
                newSet.push_back(game.pickRandomCard());
                game.setCommunityCards(newSet);
                for (auto cards : game.getCommunityCards()) {
                    std::cout << cards << " ";
                }
                std::cout << "\n";
            }




        }

        // after one round, update the dealer Position
        dealerPosition++;
    }

while ((round < 5) && (game.getCheck() > 1)) {
    }
    
    // Directly use the players vector to ensure changes affect the game state
    for (auto it = players.begin(); it != players.end();) {
        it->doAction(it->chooseAction(), game); // Perform action based on player choice
        
        if (it->getFold()) {
            // Erase the player and update the iterator to the next element
            it = players.erase(it);
        } else {
            ++it;  // Move to the next element
        }
        
        // Check if there is only one player left who hasn't folded
        if (game.getCheck() <= 1) {
            onlyOnePlayer = true;
            std::cout << "only one player left.\n";
            break;
        }
    }
    
    if (onlyOnePlayer) {
        break;  // Exit the outer loop if only one player is left
    }
    
    // Check and update game state with the current set of players
    game.checkGameStat(players);
    round++;
}








    std::vector<Player> winners;
    Hands bestHand = Hands::NoMatch;
    if (!onlyOnePlayer) {
    for (auto it = players.begin(); it != players.end(); ++it) {
        std::vector<std::string> completeHand = it->makeCompleteHand(game.getCommunityCards());
        Hands thisHand = it->evaluateHand(completeHand);

        std::cout << it->getName() << ": ";
        for (const auto& card : completeHand) {
            std::cout << card << " ";
        }
        std::cout << " " << it->handsToString(thisHand) << "\n";

        if (thisHand > bestHand) {
            winners.clear();
            winners.push_back(*it);
            bestHand = thisHand;
        } else if (thisHand == bestHand) {
            winners.push_back(*it);
        }
    }
}
    if (winners.size() == 1) {
        std::cout << "The winner is: " << winners[0].getName() << " with hand: " << winners[0].handsToString(bestHand) << "\n";
    }



    
    

    return 0;
}