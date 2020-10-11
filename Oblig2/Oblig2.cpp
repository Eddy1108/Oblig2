// Oblig2.cpp

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <thread>
#include <chrono>

char input = ' ';
int valueTemp{ 0 };
int ace1or10{ 0 };      //variable where you store what you want the ace to be
int gameState{ 0 };     //0 = playing, 1 = betting, 2 = houses turn, 3 = loss, 4 = win

int playerMoney{ 100 };
int houseMoney{ 100 };
int currentBet{ 0 };


int drawCard() 
{
    return rand() % 10 + 1;
}

int calcHand(std::vector<int> temp) 
{
    int total{ 0 };
    for (int i = 0; i < temp.size(); i++)
    {
        total += temp.at(i);
    }
    return total;
}

void printHand(std::vector<int> handArray) 
{
    std::cout << "Cards: ";
    for (int i = 0; i < handArray.size(); i++)
    {
        std::cout << handArray.at(i) << " ";
    }
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    while (true) //Loop everything
    {
        system("cls");
        gameState = 0;
        currentBet = 0;
        std::vector<int> playerHand{};      //initialize player and house hands at the start to "restart" or "empthy" them.
        std::vector<int> houseHand{};

        std::cout << "-------- Welcome to Blackjack! -------- \n\t    Your Money: " << playerMoney << "$\n\t   House Money: " << houseMoney << "$\n   Press any Key to begin (Costs 10$)";
        _getch();

        playerMoney -= 10;
        currentBet += 10;
        while (true) {  //the game
            system("cls");
            input = ' ';        //reset the input so nothing loops
            std::cout << "-----Player Turn-----\n";
            printHand(playerHand);
            std::cout << "\nTotal: " << calcHand(playerHand) << std::endl;
            std::cout << "\n---Press D to draw \n---Press F to finish---" << std::endl;

            if (calcHand(playerHand) > 21) {
                std::cout << "Your hand went over 21! You Lose!\n";
                gameState = 3;
                system("pause");
                break;
            }

            //Ending the player turn, if you press 'F'
            if (gameState == 1) {     
                break;
            }

            //Player Input.
            input = _getch();
            switch (input) {
            case 'd':
            case 'D':
                valueTemp = drawCard();     //Store the random card so we can check if its an ace
                if (valueTemp == 1) 
                {
                    std::cout << "\nYou got an Ace, do you want [1] or [11]? (type 1 or 11): ";
                    while (ace1or10 != 1 && ace1or10 != 11) 
                    {
                        std::cin >> ace1or10;
                    }
                    valueTemp = ace1or10;
                    ace1or10 = 0;
                }

                playerHand.push_back(valueTemp);    //add the draw to the player hand.
                break;
            case 'f':
            case 'F':
                if (playerHand.size() != 0) 
                {
                    gameState = 1; //switch to betting
                }
                break;
            }
        }

        while (gameState == 1)      //Betting
        {
            std::cout << "-----Betting-----\n";
            std::cout << "Your money: " << playerMoney << "\nHow much would you like to bet? \n(The house will always match your bet if they can)";
            std::cin >> valueTemp;
            if (valueTemp >= houseMoney)
            gameState = 2;
        }

        //the House's turn:
        while (gameState == 2) {
            system("cls");
            std::cout << "-----The Houses turn----- \nYour total: " << calcHand(playerHand) << "\n\nThe House will now draw...";
            std::cout << "\nHouse ";
            printHand(houseHand);
            std::cout << "\nHouse Total: " << calcHand(houseHand);

            if (calcHand(houseHand) > 21) 
            {
                std::cout << "\n\nThe House busts! You win!\n";
                system("pause");
                break;
            }

            if (calcHand(houseHand) == calcHand(playerHand))
            {
                std::cout << "\n\nIts a Match! Game Tied!\n";
                system("pause");
                break;
            }

            if (calcHand(houseHand) > calcHand(playerHand) && calcHand(houseHand) <= 21) //More than the player, less than 21
            {
                if (calcHand(houseHand) == 21) 
                {
                    std::cout << "\n\nBlackjack!";
                }
                std::cout << "\nThe House got higher cards! You Lose!\n";
                system("pause");
                break;
            }

            std::chrono::milliseconds houseWait(2000);
            std::this_thread::sleep_for(houseWait);         //wait a little, for added suspense

            valueTemp = drawCard();
            if (valueTemp == 1) 
            {
                if ((calcHand(houseHand) + 11) > 21) {
                    valueTemp = 1;
                }
                else
                {
                    valueTemp = 11;
                }
            }
            houseHand.push_back(valueTemp);
        }
    }
}


//Add tie condition
//Clean code
//Make functions
//Add betting
