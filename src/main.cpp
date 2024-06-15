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



    
    

    return 0;
}