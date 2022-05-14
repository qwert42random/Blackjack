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
        bool allowSplit;

        // Check if splitting is allowed.
        if (player.mainHand.handList[0].value == player.mainHand.handList[1].value) {
            allowSplit = true;
        } else {
            allowSplit = false;
        }

		// TODO: If split, keep hitting one hand until finished. Then move to second hand.
        // TODO: Remove playerMove and just break out of loop?
		while (playerMove == true) {

			// Print Dealer's hand (but prevent showing hole card).
            dealer.printHand(true);
            player.printHand();


            // Check if player hand value is >= 21.
            //if (calcHandValue(player.mainHand, false) >= 21) {
            //    playerMove = false;
            //    break;
            //}

			// Prompt player for move.
            if (allowSplit) {
    		    std::cout << player.name << "'s Move (hit, split, doubleDown, stand, surrender): ";
            } else {
    		    std::cout << player.name << "'s Move (hit, doubleDown, stand, surrender): ";
            }
			std::cin >> move;
			std::transform(move.begin(), move.end(), move.begin(), ::toupper);
			std::cout << "Move: " << move << std::endl;

			// Progress according to player move input.
			if (move.compare("HIT") == 0) {

                deck.deal(player.mainHand);

			} else if (move.compare("SPLIT") == 0 && allowSplit) {

                if (playerBet * 2 <= player.money) {

                    player.splitHand.handSize = 1;
                    player.splitHand.handList[0] = player.mainHand.handList[1];
                    player.mainHand.handSize = 1;

                    deck.deal(player.splitHand);
                    deck.deal(player.mainHand);

                    player.split = true;

                } else {

                    std::cout << "Insufficient funds to split" << std::endl;

                }

                allowSplit = false;

			} else if (move.compare("DOUBLEDOWN") == 0) {

                // Check if player has enough money.
                if (playerBet * 2 > player.money) {
                    playerBet * 2;
                    deck.deal(player.mainHand);
                    playerMove = false;
                } else {
                    std::cout << "Insufficient funds to Double Down" << std::endl;
                }

			} else if (move.compare("STAND") == 0) {

                playerMove = false;

            } else if (move.compare("SURRENDER") == 0) {

                playerMove = false;

			} else {
                std::cout << "Unrecognised Move" << std::endl;
			}

		}


        std::cout << "break" << std::endl;

		break;
	}


	return 0;
}
