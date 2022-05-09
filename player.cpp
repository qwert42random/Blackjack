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

int Dealer::calcHandValue() {

	int aceCount = 0;
	handValue = 0;

	for (int i = 0; i < handSize; i++) {

		if (hand[i] <= 4) {
			aceCount++;
		} else if (hand[i] > 4 && hand[i] < 9) {
			handValue += 2;
		} else if (hand[i] > 8 && hand[i] < 13) {
			handValue += 3;
		} else if (hand[i] > 12 && hand[i] < 17) {
			handValue += 4;
		} else if (hand[i] > 16 && hand[i] < 21) {
			handValue += 5;
		} else if (hand[i] > 20 && hand[i] < 25) {
			handValue += 6;
		} else if (hand[i] > 24 && hand[i] < 29) {
			handValue += 7;
		} else if (hand[i] > 28 && hand[i] < 33) {
			handValue += 8;
		} else if (hand[i] > 32 && hand[i] < 37) {
		   handValue += 9;
		} else {
			handValue += 10;
		}	

	}

	for (int j = aceCount; j > 0; j--) {

		if ((j * 11) + handValue <= 21) {
			handValue += (j * 11);
			break;
		} else {
			handValue++;
		}

	}

	return handValue;
}

