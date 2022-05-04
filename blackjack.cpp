#include <iostream>
#include "player.h"

int main() {
    Deck deck;
    std::cout << "Blackjack C++ Edition" << std::endl;

    for (int i = 0; i < 52; i++) {
        std::cout << deck.cardDeck[i] << std::endl;
    }

    return 0;
}
