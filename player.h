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

    bool split = false;
    int bet;
};

struct playerHandStruct: handStruct {
    bool doubleDown = false;
    bool surrender = false;
};

std::string obtainHandString(handStruct hand, bool hole);

class Deck {
    public:
        Deck();

        card cardDeck[52];

        void deal(handStruct &hand);
        void shuffle();

    private:
        card *topCard;
        void swap(card &a, card &b);
        int calcHandValue(handStruct &hand);
};

class Dealer {
    public:
        handStruct mainHand;
        void printHand(bool hideHole);

};

class Player {
    public:
        std::string name;
        int money = 500;
        handStruct handList[3];
        handStruct *handToDeal = &handList[0];
        int handListSize = 1;
        void printHand();
        
};
