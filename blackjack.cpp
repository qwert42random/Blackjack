#include "player.h"

int testList[] = {1, 2, 3, 4};

int main() {
    Deck deck;
    std::cout << "Blackjack C++ Edition" << std::endl;

    //deck.swap(testList[0], testList[3]);

    deck.shuffle();

    for (int i = 0; i < 52; i++) {
        std::cout << deck.cardDeck[i] << " ";
    }

    // deck.shuffle();

    return 0;
}
