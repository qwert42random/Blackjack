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

void Deck::deal(handStruct *hand) {

	hand->handList[hand->handSize++] = *(topCard++);
    hand->value = calcHandValue(*hand);

}

void Deck::swap(card &a, card &b) {
    card temp;

    temp = a;
    a = b;
    b = temp;
}

// Print Dealer's hand.
void Dealer::printHand(bool hideHole) {

    if (go) {
        std::cout << "[Dealer]" << std::endl;
    } else {
        std::cout << "Dealer" << std::endl;
    }

    std::cout << obtainHandString(mainHand, hideHole);

    if (hideHole) std::cout << "? ";

    std::cout << "[";

    if (hideHole) {

        switch(mainHand.handList[0].value) {
            case 11:
                std::cout << "10";
                break;
            case 12:
                std::cout << "10";
                break;
            case 13:
                std::cout << "10";
                break;
            default:
                std::cout << mainHand.handList[0].value;
        };

    } else {
        std::cout << mainHand.value;
    }

    std::cout << "]" << std::endl;
}

void Player::resetHand() {
    for (int i = 0; i < 4; i++) {
        handList[i].doubleDown = false;
        handList[i].surrender = false;
        handList[i].stand = false;
        handList[i].bust = false;

        handList[i].handSize = 0;
    }
    handListSize = 1;
}

void Player::printHand() {

    // Print Player's Hand.
    if (go) {
        std::cout << "[" << name << "]" << std::endl;
    } else {
        std::cout << name << std::endl;
    }

    for (int i = 0; i < handListSize; i++) {
        if (handListSize > 1) std::cout << i << ": ";
        std::cout << obtainHandString(handList[i], false);
        std::cout << "[" << handList[i].value << "] ";

        if (handList[i].doubleDown) {
            std::cout << "DOUBLEDOWN";
        } else if (handList[i].surrender) {
            std::cout << "SURR";
        } else if (handList[i].stand) {
            std::cout << "STAND";
        } else if (handList[i].bust) {
            std::cout << "BUST";
        }

        if (go && handToDeal == &handList[i]) std::cout << "<-";
        std::cout << "\n";
    }

}

// Return hand as string to be printed.
std::string obtainHandString(handStruct hand, bool hole) {

	int reveal;
	std::string handString;

    // Only reveal one card if hiding hole card for dealer.
	if (hole) {
        reveal = 1;
	} else {
        reveal = hand.handSize;
	}

	for (int i = 0; i < reveal; i++) {

        switch(hand.handList[i].value) {
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
                handString += std::to_string(hand.handList[i].value);
        };

        handString += "(";

        switch(hand.handList[i].suit) {
            case SPADE:
                handString += "S";
                break;
            case CLUB:
                handString += "C";
                break;
            case DIAMOND:
                handString += "D";
                break;
            case HEART:
                handString += "H";
                break;
        };

		handString += ") ";

	}

	return handString;
}

// Calculate the value of hand.
int Deck::calcHandValue(handStruct &hand) {

	int aceCount = 0;
	int handValue = 0;

	for (int i = 0; i < hand.handSize; i++) {
        switch(hand.handList[i].value) {
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
                handValue += hand.handList[i].value;
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

