#include "player.h"
#include <limits>

enum playerMoves{hit, split, doubleDown, stand, surrender};

int main() {
    Deck deck;
    Player player;
    Dealer dealer;

    std::cout << "Blackjack C++ Edition" << std::endl;
    std::cout << "Enter Name: ";
    std::cin >> player.name;

    // While player still has money.
    while(player.money > 0) {
        
        bool validBet = false;
		int playerBet;

        // Prompt player for bet amount.
        while (validBet == false) {
            std::cout << "Enter bet amount (max: " << player.money << "): ";
            std::cin >> playerBet;

            if (std::cin.fail()) {
                std::cout << "Invalid: Input not recognized." << std::endl;

				// Flush buffer to allow another input.
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else if (playerBet < 0 || playerBet > player.money) {
				std::cout << "Invalid amount" << std::endl;

				// Flush buffer to allow another input.
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} else {
                validBet = true;
                std::cout << player.name  << " entered: " << playerBet << std::endl;
            }

        }

		deck.shuffle();

		// Reset hand sizes member.
		dealer.mainHand.handSize = 0;
		player.mainHand.handSize = 0;

		// Deal the initial hand.
		for (int i = 0; i < 2; i++) {
			deck.deal(dealer.mainHand);
			deck.deal(player.mainHand);
		}

		player.split = false;
		std::string move;
        bool playerMove = true;
        bool finishMove = false;
        bool allowSplit;
        bool bust = false;
        player.dealToSplit = false;

        // Check if splitting is allowed.
        if (player.mainHand.handList[0].value == player.mainHand.handList[1].value) {
            allowSplit = true;
        } else {
            allowSplit = false;
        }

        handStruct *handToDeal = &player.mainHand;

        while (true) {
            
            // Print hands for dealer and player.
            dealer.printHand(true);
            player.printHand();

            // Print move prompt for player.
            if (allowSplit) {
    		    std::cout << player.name << "'s Move (hit, split, doubleDown, stand, surrender): ";
            } else if (bust == false) {
    		    std::cout << player.name << "'s Move (hit, doubleDown, stand, surrender): ";
            } else {
                std::cout << player.name << "'s Move (stand): " << std::endl;
            }

            std::cin >> move;
            std::transform(move.begin(), move.end(), move.begin(), ::toupper);
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "Move: " << move << std::endl;

			// Progress according to player move input.
			if (move.compare("HIT") == 0) {

                deck.deal(*handToDeal);
                player.updateHandValue(*handToDeal, false);

                if (handToDeal->value > 21) {
                    finishMove = true;
                }

			} else if (move.compare("SPLIT") == 0 && allowSplit) {

                if (playerBet * 2 <= player.money) {

                    player.splitHand.handSize = 1;
                    player.splitHand.handList[0] = player.mainHand.handList[1];
                    player.mainHand.handSize = 1;

                    deck.deal(player.splitHand);
                    deck.deal(player.mainHand);

                    player.split = true;

                    player.updateHandValue(*handToDeal, false);

                } else {

                    std::cout << "Insufficient funds to split" << std::endl;

                }


			} else if (move.compare("DOUBLEDOWN") == 0) {

                // Check if player has enough money.
                if (playerBet * 2 <= player.money) {
                    playerBet * 2;
                    deck.deal(*handToDeal);
                    playerMove = false;
                } else {
                    std::cout << "Insufficient funds to Double Down" << std::endl;
                }

			} else if (move.compare("STAND") == 0) {

                finishMove = true;

            } else if (move.compare("SURRENDER") == 0) {

                finishMove = true;

			} else {
                std::cout << "Unrecognised Move" << std::endl;
			}

            // Switch hand to split hand if move finished.
            if (finishMove == true) {
                if (player.split == true && handToDeal == &player.mainHand) {
                    handToDeal = &player.splitHand;
                    player.dealToSplit = true;
                    finishMove = false;
                } else {
                    break;
                }
            }

            allowSplit = false;

        }


        std::cout << "----------break----------" << std::endl;
        // Print hands for dealer and player.
        dealer.printHand(true);
        player.printHand();

		break;
	}


	return 0;
}
