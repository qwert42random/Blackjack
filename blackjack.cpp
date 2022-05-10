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

		// TODO: Maybe shove this into while loop as well?
        do {
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

        } while (validBet == false);

		player.money -= playerBet;

		deck.shuffle();

		// Reset hand sizes member.
		dealer.handSize = 0;
		player.handSize = 0;

		// Deal the initial hand.
		for (int i = 0; i < 2; i++) {
			dealer.hand[i] = deck.deal();
			dealer.handSize++;

			player.hand[i] = deck.deal();
			player.handSize++;
		}

		// TODO: Delete this later when done.
		for (int i = 0; i < 2; i++) {
			std::cout << dealer.hand[i] << std::endl;
		}

		bool split = false;

		while (true) {

			// Print Dealer's hand.
			std::cout << "Dealer's Hand: ";
			std::cout << printHand(dealer.hand, 1) << "? ";
			std::cout << "(" << calcHandValue(dealer.hand, 1) << ")" << std::endl;

			// Print Player's hand.
			std::cout << player.name << "'s Hand: ";
			std::cout << printHand(player.hand, player.handSize);
			std::cout << "(" << calcHandValue(player.hand, player.handSize) << ")" << std::endl;

			// Print Player's split hand.
			if (split == true) {
			}

			std::cout << player.name << "'s Move (hit, split, doubleDown, stand, surrender): ";
			std::cin >> player.move;


		}

		break;
	}


	return 0;
}
