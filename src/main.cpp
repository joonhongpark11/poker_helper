#include "Player.h"
#include "Game.h"

#include<unistd.h> 



int main() {
    // greeting
    std::cout << GREETING;
    sleep(1);

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
        usleep(500000);
        std::cout << "Here is the List of the player positions.\n";
        usleep(500000);
        game.printPlayerOrder();
        sleep(1);

        game.checkGameStat();
        sleep(2);

        //small blind
        int index1 = 0;
        bool hasPlayer = false;

        while (index1 <= game.getPlayerNumber()) {
            Player* tempPlayer = game.getPlayers()[index1];
            if (!tempPlayer->getIsOut()) {
                tempPlayer->betting(smallBlind, game);
                hasPlayer = true;
                std::cout << tempPlayer->getName() << ": small blind: " << smallBlind << "\n";
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
                std::cout << tempPlayer->getName() << ": big blind: " << smallBlind * 2 << "\n";
                break;  // Exit the loop after finding the first player to bet big blind
            }
            index2++;
        }

        if (index2 >= game.getPlayerNumber()) {
            throw std::runtime_error("No active players found for big blind!!!");
        }


        // cards setup
        game.setCardsLeft(game.generateDeck());
        // setup hole cards
        game.setupHoleCards();

        // whole game 4 rounds
        while (game.getRound() < 5) {
            // consider small and big blind
            if (game.getRound() == 1) {
                game.setHasBet(true);
            }
            std::cout << "--------------------------------------------\n";
            std::cout << "round: " << game.getRound() << "\n";
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
                    int action = -1;
                    if (currentPlayer->getName() == "user") {
                        std::vector<int> validActions = currentPlayer->getAvailableOptions(game);
                        std::cout << "--------------------------------------------\n";
                        std::cout << "It is your turn\n";
                        currentPlayer->printActions(validActions);
                        std::cout << "Which action do you want to do?\n>";
                        while (true) {
                            std::cin >> action;
                            if (std::find(validActions.begin(), validActions.end(), action) != validActions.end()) {
                                break;
                            } else {
                                std::cin.clear(); // clear the error flags
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid action. Please enter a valid action.\n";
                            }
                        }
                        std::cout << "--------------------------------------------\n";
                    }
                    else {
                        action = currentPlayer->chooseAction(game);
                    }
                    currentPlayer->doAction(action, game);
                }

                // move to the next player
                index++;
                if (index == game.getPlayerNumber()) {
                    index = 0;
                }
            }
            game.checkGameStat();
            //reset done action
            game.makeDoneActionFalse();
            // update round
            game.setRound(game.getRound() + 1);
            game.setHasBet(false);

        }
        game.checkGameStat();
        game.doShowDown();
        game.makeNoCoinPlayersOut();

        //update dealerposition
        game.sortPlayer(0);

        //game reset
        game.resetForNextGame();
    } while(!(game.getPlayers()[0]->getName() == "player1"));

    game.checkGameStat();
    
    // free dynamically allocated memories
    game.freePlayers();


    return 0;
}