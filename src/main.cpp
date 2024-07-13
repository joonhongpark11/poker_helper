#include "Player.h"
#include "Game.h"



int main() {
    // greeting
    std::cout << GREETING;

    // playerNumber request (doesn't include user)
    int playerNumber = requestPlayerNumbers();

    // game initialization variables
    int dealerPosition = playerNumber;
    int smallBlind = 20;

    // game setup
    Game game = {playerNumber + 1, smallBlind}; // include user

    game.sortPlayer(dealerPosition);
    do {
        // make mainpot
        assert(game.getPots() != nullptr);
        if (*game.getPots() == nullptr) {
            game.setPots();
        }
        std::cout << "Dealer Position is " << game.getPlayers()[game.getPlayerNumber() - 1]->getName() << "\n";
        std::cout << "Here is the List of the player positions.\n";
        game.printPlayerOrder();

        game.checkGameStat();

        //small blind
        std::cout << "Debug: small blind\n";
        int index1 = 0;
        bool hasPlayer = false;

        while (index1 <= game.getPlayerNumber()) {
            Player* tempPlayer = game.getPlayers()[index1];
            if (!tempPlayer->getIsOut()) {
                tempPlayer->betting(smallBlind, game);
                hasPlayer = true;
                break;  // Exit the loop after finding the first player to bet small blind
            }
            index1++;
        }

        if (!hasPlayer) {
            throw std::runtime_error("No active players found for small blind!!!");
        }

        int index2 = index1 + 1;

        while (index2 <= game.getPlayerNumber()) {
            Player* tempPlayer = game.getPlayers()[index2];
            if (!tempPlayer->getIsOut()) {
                tempPlayer->betting(smallBlind * 2, game);
                break;  // Exit the loop after finding the first player to bet big blind
            }
            index2++;
        }

        if (index2 >= game.getPlayerNumber()) {
            throw std::runtime_error("No active players found for big blind!!!");
        }


        // cards setup
        std::cout << "Debug: card setup\n";
        game.setCardsLeft(game.generateDeck());
        std::cout << "Debug: holeCards setup\n";
        // setup hole cards
        game.setupHoleCards();

        // whole game 4 rounds
        while (game.getRound() < 5) {
            // consider small and big blind
            if (game.getRound() == 1) {
                game.setHasBet(true);
            }
            std::cout << "round: " << game.getRound() << "\n";
            std::cout << "Debug: community card pick up\n";
            // the flop
            if (game.getRound() == 2) {
                std::vector<std::string> communityCards;
                for (int i = 0; i < 3; ++i) {
                    communityCards.push_back(game.pickRandomCard());
                    game.setCommunityCards(communityCards);
                }
            }
            // turn and river
            else if ((game.getRound() == 3) || (game.getRound() == 4)) {
                std::vector<std::string> newCommunitySet = game.getCommunityCards();
                std::string newCard = game.pickRandomCard();
                newCommunitySet.push_back(newCard);
                game.setCommunityCards(newCommunitySet);
            }

            // betting process
            int index = 2; // after small and big blind
            std::cout << "Debug:betting started\n";
            while (!game.isPlayerAllDone()) {
                // update proper index
                assert(index <= game.getPlayerNumber() - 1);

                // check if there is a winner already
                if (game.isOnlyOnePlayerLeft()) {
                    break;
                }

                // player checking and action
                Player* currentPlayer = game.getPlayers()[index];
                if (!currentPlayer->getDoneAction() && !currentPlayer->getIsFold() && !currentPlayer->getIsAllIn() && !currentPlayer->getIsOut()) {
                    int action = currentPlayer->chooseAction(game);
                    currentPlayer->doAction(action, game);
                }

                // move to the next player
                index++;
                if (index == game.getPlayerNumber()) {
                    index = 0;
                }
            }
            std::cout << "Debug: betting end\n";

            //reset done action
            std::cout << "make done actino false\n";
            game.makeDoneActionFalse();

            game.checkGameStat();
            // update round
            std::cout << "Debug: update round\n";
            game.setRound(game.getRound() + 1);

        }
        game.checkGameStat();
        std::cout << "Debug: showdown\n";
        game.doShowDown();
        game.makeNoCoinPlayersOut();

        //update dealerposition
        std::cout << "Debug: sort for next game\n";
        game.sortPlayer(0);

        //game reset
        std::cout << "Debug: game reset\n";
        game.resetForNextGame();
        std::cout << "Debug: loop done\n";
    } while(!(game.getPlayers()[0]->getName() == "player1"));

    game.checkGameStat();
    
    // free dynamically allocated memories
    game.freePlayers();


    return 0;
}

// deal with only one player
// deal with all in
// make printing for distribute coins