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

        // Reset hands.
		dealer.mainHand.handSize = 0;
		player.handList[0].handSize = 0;
        player.handListSize = 1;

        player.handToDeal = &player.handList[0];

		// Deal the initial hand.
		for (int i = 0; i < 2; i++) {
			deck.deal(&dealer.mainHand);
			deck.deal(player.handToDeal);
		}

		std::string move;
        bool finishMove = false;
        bool allowSplit, allowDoubleDown;
        int totalBetAmount = playerBet;

        while (true) {
            
            // Check if splitting is allowed.
            if (player.handToDeal->handList[0].value == player.handToDeal->handList[1].value && player.handToDeal->handSize == 2 && totalBetAmount + playerBet < player.money) {
                 allowSplit = true;
            } else {
                allowSplit = false;
            }

            // Check if doubling down is allowed.
            if (player.handToDeal->handSize == 2 && totalBetAmount + playerBet < player.money) {
                allowDoubleDown = true;
            } else {
                allowDoubleDown = false;
            }

            // Print hands for dealer and player.
            player.printHand();
            dealer.printHand(true);

            // Print move prompt for player.
            std::cout << player.name << "'s Move (hit, ";
            if (allowSplit) std::cout << "split, ";
            if (allowDoubleDown) std::cout << "doubleDown, ";
            std::cout << "stand, surrender): ";

            // Take in player move.
            std::cin >> move;
            std::transform(move.begin(), move.end(), move.begin(), ::toupper);
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "Move: " << move << std::endl;

			// Progress according to player move input.
			if (move.compare("HIT") == 0) {

                deck.deal(player.handToDeal);

                // Check if hand is bust or 21.
                if (player.handToDeal->value >= 21) {
                    finishMove = true;
                }

			} else if (move.compare("SPLIT") == 0 && allowSplit) {
			} else if (move.compare("DOUBLEDOWN") == 0 && allowDoubleDown) {

                deck.deal(player.handToDeal);
                totalBetAmount += playerBet;
                player.handToDeal->doubleDown = true;
                finishMove = true;

			} else if (move.compare("STAND") == 0) {

                finishMove = true;

            } else if (move.compare("SURRENDER") == 0) {

                finishMove = true;

			} else {
                std::cout << "Unrecognised Move" << std::endl;
			}

            // Switch hand to split hand if move finished.
            if (finishMove == true) {
            }

        }


        std::cout << "----------break----------" << std::endl;
        // Print hands for dealer and player.
        dealer.printHand(true);
        player.printHand();

		break;
	}


	return 0;
}
