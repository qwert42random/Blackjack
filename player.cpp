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

std::string Dealer::printHand(bool holeCard) {

	std::string handString;
	int count;

	if (holeCard) {
		count = 1;
	} else {
		count = handSize;
	}

	for (int i = 0; i < count; i++) {

		switch(hand[i]) {
			case 1:
				handString += "A(S)";
				break;
			case 2:
				handString += "A(D)";
				break;
			case 3:
				handString += "A(C)";
				break;
			case 4:
				handString += "A(H)";
				break;
			case 5:
				handString += "2(S)";
				break;
			case 6:
				handString += "2(D)";
				break;
			case 7:
				handString += "2(C)";
				break;
			case 8:
				handString += "2(H)";
				break;
			case 9:
				handString += "3(S)";
				break;
			case 10:
				handString += "3(D)";
				break;
			case 11:
				handString += "3(C)";
				break;
			case 12:
				handString += "3(H)";
				break;
			case 13:
				handString += "4(S)";
				break;
			case 14:
				handString += "4(D)";
				break;
			case 15:
				handString += "4(C)";
				break;
			case 16:
				handString += "4(H)";
				break;
			case 17:
				handString += "5(S)";
				break;
			case 18:
				handString += "5(D)";
				break;
			case 19:
				handString += "5(C)";
				break;
			case 20:
				handString += "5(H)";
				break;
			case 21:
				handString += "6(S)";
				break;
			case 22:
				handString += "6(D)";
				break;
			case 23:
				handString += "6(C)";
				break;
			case 24:
				handString += "6(H)";
				break;
			case 25:
				handString += "7(S)";
				break;
			case 26:
				handString += "7(D)";
				break;
			case 27:
				handString += "7(C)";
				break;
			case 28:
				handString += "7(H)";
				break;
			case 29:
				handString += "8(S)";
				break;
			case 30:
				handString += "8(D)";
				break;
			case 31:
				handString += "8(C)";
				break;
			case 32:
				handString += "8(H)";
				break;
			case 33:
				handString += "9(S)";
				break;
			case 34:
				handString += "9(D)";
				break;
			case 35:
				handString += "9(C)";
				break;
			case 36:
				handString += "9(H)";
				break;
			case 37:
				handString += "10(S)";
				break;
			case 38:
				handString += "10(D)";
				break;
			case 39:
				handString += "10(C)";
				break;
			case 40:
				handString += "10(H)";
				break;
			case 41:
				handString += "J(S)";
				break;
			case 42:
				handString += "J(D)";
				break;
			case 43:
				handString += "J(C)";
				break;
			case 44:
				handString += "J(H)";
				break;
			case 45:
				handString += "Q(S)";
				break;
			case 46:
				handString += "Q(D)";
				break;
			case 47:
				handString += "Q(C)";
				break;
			case 48:
				handString += "Q(H)";
				break;
			case 49:
				handString += "K(S)";
				break;
			case 50:
				handString += "K(D)";
				break;
			case 51:
				handString += "K(C)";
				break;
			case 52:
				handString += "K(H)";
				break;
		}

		handString += " ";

	}

	return handString;
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

