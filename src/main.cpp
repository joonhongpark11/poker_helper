#include "Player.h"
#include "Game.h"




int main() {
    std::cout << GREETING;
    int playerNumber = playerInputLoop();
    
    // player initalization
    std::vector<Player> players;
    for (int i = 1; i <= playerNumber; ++i) {
        std::string playerName = "player" + std::to_string(i);
        Player player(playerName, 100);
        players.push_back(player);
    }
    Player user("user", 100);
    players.push_back(user);

    // Dealer position is fixed per execution
    int dealerPosition;

    //small blind
    int smallBlind = 5;

    // game object creation per game --> should use while loop
    Game game = {playerNumber, smallBlind};
    dealerPosition = game.chooseDealerPosition(game.getPlayerNumber());
    std::cout << "Dealer Position is right side of " << players[dealerPosition - 1].getName() << "\n";
    std::cout << "Here is the List of the player positions.\n";
    players = game.playerSort(players, dealerPosition);
    for (int i = 0; i < players.size(); ++i) {
        std::cout << players[i].getName() << " ";
    }
    std::cout << "\n";

    //small blind
    players[0].betting(smallBlind, game);
    //big blind
    players[1].betting(smallBlind * 2, game);

    // need to pick two cards
    for (int i = 0; i < players.size(); ++i) {
        game.drawHoleCard(players[i]);
        std::cout << players[i].getName() << " cards: ";
        for (std::string card : players[i].getHoleCards()) {
            std::cout << card << " ";
        }
        std::cout << "\n";
    }
    
    // need to do first bet
   int round = 1;
bool onlyOnePlayer = false;

while ((round < 5) && (game.getCheck() > 1)) {

    std::cout << "round: " << round << "\n";

    // draw three cards
    if (round == 2) {
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
    else if (round == 3 || round == 4) {
        std::vector<std::string> newSet = game.getCommunityCards();
        newSet.push_back(game.pickRandomCard());
        game.setCommunityCards(newSet);
        for (auto cards : game.getCommunityCards()) {
            std::cout << cards << " ";
        }
        std::cout << "\n";
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