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
    int value;
};

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
        void printHand(bool hideHole);
        void updateHandValue(handStruct &hand, bool hole);

    protected:
        std::string obtainHandString(handStruct hand, bool hole);

};

class Player: public Dealer {
    public:
        std::string name;
        int money = 500;
		bool split;
        handStruct splitHand;
        void printHand();

        bool dealToSplit = false;
        
};
