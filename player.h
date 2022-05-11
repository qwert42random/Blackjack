#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

enum suitSymbols {SPADE, CLUB, DIAMOND, HEART};

struct card {
    int value;
    enum suitSymbols suit;
};

struct handStruct {
    card handList[20];
    int handSize;
};

int calcHandValue(handStruct hand, bool hole);
std::string printHand(handStruct hand, bool hole);

class Deck {
    public:
        Deck();

        card cardDeck[52];

        void deal(handStruct &hand);
        void shuffle();

    private:
        card *topCard;
        void swap(card &a, card &b);
};

class Dealer {
    public:
        handStruct mainHand;
};

class Player: public Dealer {
    public:
        std::string name;
        int money = 500;
		bool split;
        handStruct splitHand;
        
};
