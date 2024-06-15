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

    // game object creation per game --> should use while loop
    int smallBlind = 5;
    Game game = {playerNumber, smallBlind};
    game.setCardsOnField(game.generateDeck());
    dealerPosition = game.chooseDealerPosition(game.getPlayerNumber());
    std::cout << dealerPosition;
    std::cout << "Dealer Position is right side of " << players[dealerPosition - 1].getName() << "\n";
    std::cout << "Here is the List of the player positions.\n";
    players = game.playerSort(players, dealerPosition);

    //small blind
    
    
    

    return 0;
}