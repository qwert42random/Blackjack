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

        do {
            std::cout << "Enter bet amount (max: " << player.money << "): ";
            std::cin >> player.playerBet;

            if (std::cin.fail()) {
                std::cout << "Invalid input" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                validBet = true;
                std::cout << "You entered: " << player.playerBet << std::endl;
            }

        } while (validBet == false);


        break;
    }


    return 0;
}
