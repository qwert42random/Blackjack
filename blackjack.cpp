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

		bool split = false;

		while (true) {

			// Print Dealer's hand.
			std::cout << "Dealer's Hand: ";
			std::cout << "(" << dealer.calcHandValue() << ")" << std::endl;

			if (split == true) {
			}

			std::cout << player.name << "'s Move (hit, split, doubleDown, stand, surrender): ";
			std::cin >> player.move;


		}

		break;
	}


	return 0;
}
