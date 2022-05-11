#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

enum suitSymbols {SPADE, CLUB, DIAMOND, HEART};

struct card {
    int value;
    enum suitSymbols suit;
};

int calcHandValue(card *handList, int handListSize);
std::string printHand(card *handList, int handListSize);

class Deck {
    public:
        Deck();

        card cardDeck[52];

        card deal();
        void shuffle();

    private:
        card *topCard;
        void swap(card &a, card &b);
};

class Dealer {
    public:
        card hand[21];
        int handSize;
};

class Player: public Dealer {
    public:
        std::string name;
        int money = 500;
        card splitHand[21];
		int splitHandSize;
		bool split;
        
};
