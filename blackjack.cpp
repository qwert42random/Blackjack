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
    deck.shuffle();

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
            } else if (playerBet < 0 || playerBet > playerMoney) {
	    	std::cout << "Invalid amount" << std::endl;

		// Flush buffer to allow another input.
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    } else {
                validBet = true;
                std::cout << player.name  << "You entered: " << playerBet << std::endl;
            }

        } while (validBet == false);

	player.playerMoney -= playerBet;

	// Deal the initial hand.
        break;
    }


    return 0;
}
