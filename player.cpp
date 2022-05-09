#include "player.h"

Deck::Deck() {
    srand(time(0));
}

void Deck::shuffle() {
    int randInt;

    // Apply Fisher Yates shuffling algorithm.
    for (int i = 51; i > 0; i--) {
        randInt = rand() % i;
        swap(cardDeck[i], cardDeck[randInt]);
    }

    topCard = &cardDeck[0];
}

int Deck::deal() {
    return *(topCard++);
}

void Deck::swap(int &a, int &b) {
    int temp;

    temp = a;
    a = b;
    b = temp;
}

int Dealer::handValue() {
	return 0;
}

