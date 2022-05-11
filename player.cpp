#include "player.h"

Deck::Deck() {
    srand(time(0));

    int deckIndex = 0;

    // Initialise the deck.
    for (int cardValue = 1; cardValue <= 13; cardValue++) {
        for (int cardSuit = 0; cardSuit < 4; cardSuit++) {
            switch(cardSuit) {
                case 0:
                    cardDeck[deckIndex].suit = SPADE;
                    break;
                case 1:
                    cardDeck[deckIndex].suit = CLUB;
                    break;
                case 2:
                    cardDeck[deckIndex].suit = DIAMOND;
                    break;
                case 3:
                    cardDeck[deckIndex].suit = HEART;
                    break;
            };

            cardDeck[deckIndex++].value = cardValue;
        }
    }
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

card Deck::deal() {
    return *(topCard++);
}

void Deck::swap(card &a, card &b) {
    card temp;

    temp = a;
    a = b;
    b = temp;
}

// Return hand as string to be printed.
std::string printHand(card *handList, int handListSize) {

	std::string handString;

	for (int i = 0; i < handListSize; i++) {

        switch(handList[i].value) {
            case 1:
                handString += "A";
                break;
            case 10:
                handString += "10";
                break;
            case 11:
                handString += "J";
                break;
            case 12:
                handString += "Q";
                break;
            case 13:
                handString += "K";
                break;
            default:
                handString += std::to_string(handList[i].value);
        };

        handString += "(";

        switch(handList[i].suit) {
            case 0:
                handString += "S";
                break;
            case 1:
                handString += "C";
                break;
            case 2:
                handString += "D";
                break;
            case 3:
                handString += "H";
                break;
        };

		handString += ") ";

	}

	return handString;
}

// Calculate the value of hand.
int calcHandValue(card *handList, int handListSize) {

	int aceCount = 0;
	int handValue = 0;

	for (int i = 0; i < handListSize; i++) {
        switch(handList[i].value) {
            case 1:
                aceCount++;
                break;
            case 11:
                handValue += 10;
                break;
            case 12:
                handValue += 10;
                break;
            case 13:
                handValue += 10;
                break;
            default:
                handValue += handList[i].value;
        };
	}


    // Calculate values for aces.
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

