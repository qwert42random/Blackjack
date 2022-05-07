#include "player.h"

int main() {
    Deck deck;
    Player player;

    std::cout << "Blackjack C++ Edition" << std::endl;
    std::cout << "Enter Name: ";
    std::cin >> player.name;

    deck.shuffle();

    return 0;
}
