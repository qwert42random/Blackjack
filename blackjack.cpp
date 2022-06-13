#include "player.h"
#include <limits>

enum playerMoves{hit, split, doubleDown, stand, surrender};

int main() {
    Deck deck;
    Player player;
    Dealer dealer;

    std::cout << "Blackjack C++ Edition" << std::endl;
    std::cout << "EARLY ACCESS EDITION" << std::endl;
    std::cout << "Enter Name: ";
    std::cin >> player.name;

    // While player still has money.
    while(player.money > 0) {
        
        bool validBet = false;
        int playerBet;

        // Prompt player for bet amount.
        while (validBet == false) {
            std::cout << "Enter bet amount (max: " << player.money << "): ";
            std::cin >> playerBet;

            if (std::cin.fail()) {
                std::cout << "Invalid: Input not recognized." << std::endl;

				// Flush buffer to allow another input.
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else if (playerBet < 0 || playerBet > player.money) {
				std::cout << "Invalid amount" << std::endl;

				// Flush buffer to allow another input.
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} else {
                validBet = true;
                std::cout << player.name  << " entered: " << playerBet << std::endl;
            }

        }

		deck.shuffle();

        // Reset hands.
		dealer.mainHand.handSize = 0;
		player.handList[0].handSize = 0;
        player.resetHand();

        // Set hand to be dealt to player's first hand.
        player.handToDeal = &player.handList[0];

		// Deal the initial hand.
		for (int i = 0; i < 2; i++) {
			deck.deal(&dealer.mainHand);
			deck.deal(player.handToDeal);
		}

		std::string move;
        bool finishMove = false;
        bool allowSplit, allowDoubleDown;
        int totalBetAmount = playerBet;

        if (player.handToDeal->value == 21) {
            player.go = false;
        } else {
            player.go = true;
        }

        while (player.go) {
            
            // Check if splitting is allowed.
            if (player.handToDeal->handList[0].value == player.handToDeal->handList[1].value && player.handToDeal->handSize == 2 && totalBetAmount + playerBet <= player.money) {
                 allowSplit = true;
            } else {
                allowSplit = false;
            }

            // Check if doubling down is allowed.
            if (player.handToDeal->handSize == 2 && totalBetAmount + playerBet <= player.money) {
                allowDoubleDown = true;
            } else {
                allowDoubleDown = false;
            }

            // Print hands for dealer and player.
            player.printHand();
            dealer.printHand(true);

            // Print move prompt for player.
            std::cout << player.name << "'s Move (hit, ";
            if (allowSplit) std::cout << "split, ";
            if (allowDoubleDown) std::cout << "doubleDown, ";
            std::cout << "stand, surrender): ";

            // Take in player move.
            std::cin >> move;
            std::transform(move.begin(), move.end(), move.begin(), ::toupper);
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "Move: " << move << std::endl;

			// Progress according to player move input.
			if (move.compare("HIT") == 0) {

                deck.deal(player.handToDeal);

			} else if (move.compare("SPLIT") == 0 && allowSplit) {

                player.handListSize++;
                playerHandStruct *splitHand = &player.handList[1];

                // Reset the size of hand.
                player.handToDeal->handSize = 1;
                splitHand->handSize = 1;

                // Set first card in split hand to second card in hand being dealt to.
                splitHand->handList[0] = player.handToDeal->handList[1];

                // Deal a card to both hands.
                deck.deal(player.handToDeal);
                deck.deal(splitHand);

                totalBetAmount += playerBet;

			} else if (move.compare("DOUBLEDOWN") == 0 && allowDoubleDown) {

                deck.deal(player.handToDeal);
                totalBetAmount += playerBet;
                player.handToDeal->doubleDown = true;
                finishMove = true;

			} else if (move.compare("STAND") == 0) {

                player.handToDeal->stand = true;
                finishMove = true;

            } else if (move.compare("SURRENDER") == 0) {

                totalBetAmount -= playerBet / 2;
                player.handToDeal->surrender = true;
                finishMove = true;

			} else {
                std::cout << "Unrecognised Move" << std::endl;
			}


            // Check if hand is bust or 21.
            if (player.handToDeal->value >= 21) {
                if (player.handToDeal->value > 21) player.handToDeal->bust = true;
                finishMove = true;
            }


            // Switch hand to split hand if move finished.
            if (finishMove == true) {
                std::cout << "Move Finished" << std::endl;

                // Move to next split hand.
                if (player.handListSize > 1 && player.handToDeal != &player.handList[player.handListSize - 1]) {
                    player.handToDeal++;
                    finishMove = false;
                } else {
                    player.go = false;
                    dealer.go = true;
                    break;
                }
            }

        }


        std::cout << "----------Dealer Turn----------" << std::endl;
        // Print hands for dealer and player.
        player.printHand();
        dealer.printHand(false);

        // Check how many hands were surrendered or bust.
        int handsLost = 0;
        for (int i = 0; i < player.handListSize; i++) {

            if (player.handList[i].bust == true || player.handList[i].surrender) {
                handsLost++;
            }

        }

        // If all player hands were either bust or surrendered.
        if (handsLost == player.handListSize) {

            std::cout << "Remaining money: ";

            // Deduct money based on bust or surrender.
            for (int i = 0; i < player.handListSize; i++) {
                
                if (player.handList[i].bust == true) {
                    std::cout << player.money << " - " << playerBet;
                    player.money -= playerBet;
                } else if (player.handList[i].surrender) {
                    std::cout << player.money << " - " << playerBet / 2;
                    player.money -= playerBet / 2;
                } else if (player.handList[i].doubleDown) {
                    std::cout << player.money << " - " << playerBet * 2;
                    player.money -= playerBet * 2;
                }

                std::cout << " = " << player.money << std::endl;

            }

            std::cout << "Dealer wins!" << std::endl;
            continue;

        }

        std::cout << "\nDealing to dealer...\n" << std::endl;

        // Deal to dealer until hand has value of at least 17.
        while (dealer.mainHand.value < 17) {
            deck.deal(&dealer.mainHand);
        }

        signed int moneyEarnt = 0;
        bool dealerBust = dealer.mainHand.value > 21;

        // Compare hands to dealer and update money accordingly.
        for (int i = 0; i < player.handListSize; i++) {

            if (player.handList[i].surrender) {

                // If hand has been surrendered.
                moneyEarnt -= playerBet / 2;

            } else if (player.handList[i].bust || (dealer.mainHand.value > player.handList[i].value && !dealerBust)) {

                // If hand has been lost.
                if (player.handList[i].doubleDown == true) {
                    moneyEarnt -= playerBet * 2;
                } else {
                    moneyEarnt -= playerBet;
                }
                
            } else if (dealerBust || (dealer.mainHand.value < player.handList[i].value && !player.handList[i].bust)) {

                // If hand has been won.
                if (player.handList[i].doubleDown == true) {
                    moneyEarnt += playerBet * 2;
                } else {
                    moneyEarnt += playerBet;
                }

            }

        }

        player.printHand();
        dealer.printHand(false);

        std::cout << "Remaining money: " << player.money;
        if (moneyEarnt > 0) {
            std::cout << " + " << moneyEarnt;
        } else if (moneyEarnt < 0) {
            std::cout << " - " << abs(moneyEarnt); 
        } else if (moneyEarnt == 0) {
            std::cout << " + 0";
        }
        player.money += moneyEarnt;
        std::cout << " = " << player.money << std::endl;

	}


	return 0;
}
