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

struct playerHandStruct: handStruct {
    bool doubleDown = false;
    bool surrender = false;
    bool stand = false;
    bool bust = false;
};

std::string obtainHandString(handStruct hand, bool hole);

class Deck {
    public:
        Deck();

        card cardDeck[52];

        void deal(handStruct *hand);
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
        bool go = false;

};

class Player {
    public:
        std::string name;
        int money = 500;
        playerHandStruct handList[4];
        playerHandStruct *handToDeal = &handList[0];
        int handListSize = 1;
        void printHand();
        void resetHand();
        bool go = false;
        
};
