#include <iostream>
#include <cstdlib>
#include <ctime>

std::string printHand(int *handList, int handListSize);
int calcHandValue(int *handList, int handListSize);

class Deck {
    public:
        Deck();
    
        int cardDeck[52] = {
            1,2,3,4,
            5,6,7,8,
            9,10,11,12,
            13,14,15,16,
            17,18,19,20,
            21,22,23,24,
            25,26,27,28,
            29,30,31,32,
            33,34,35,36,
            37,38,39,40,
            41,42,43,44,
            45,46,47,48,
            49,50,51,52
        };

        int deal();
        void shuffle();

    private:
        int *topCard;
        void swap(int &a, int &b);
};

class Dealer {
    public:
        int hand[21];
        int handSize;
		int handValue = 0;
};

class Player: public Dealer {
    public:
        std::string name;
        int money = 500;
        int splitHand[21];
        int move;
		int calcSplitHandValue();
        
};
