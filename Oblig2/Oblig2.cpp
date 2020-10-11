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
int gameState{ 0 };     //0 = playing, 1 = house turn, 2 = loss, 3 = win

int playerMoney{ 100 };
int houseMoney{ 100 };

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

    while (true) //Loop the whole game
    {
        system("cls");
        gameState = 0;
        std::vector<int> playerHand{};      //initialize player and house hands at the start to "restart" or "empthy" them.
        std::vector<int> houseHand{};

        std::cout << "-------- Welcome to Blackjack! -------- \n\tPress any Key to begin";
        _getch();


        while (true) {  //the game
            system("cls");
            input = ' ';        //reset the input so nothing loops
            std::cout << "-----Player Turn-----\n";
            printHand(playerHand);
            std::cout << "\nTotal: " << calcHand(playerHand) << std::endl;
            std::cout << "\n---Press D to draw \n---Press F to finish---" << std::endl;

            if (calcHand(playerHand) > 21) {
                std::cout << "Your hand went over 21! You Lose!\n";
                gameState = 2;
                system("pause");
                break;
            }
            //Ending the player turn, if you press 'F', or you hit 21
            if (gameState == 1) {     
                break;
            }

            //Player Input.
            input = _getch();
            switch (input) {
            case 'd':
            case 'D':
                valueTemp = drawCard();     //Store the random card so we can check if its an ace
                if (valueTemp == 1) {
                    std::cout << "\nYou got an Ace, do you want [1] or [11]? (type 1 or 11): ";
                    while (ace1or10 != 1 && ace1or10 != 11) {
                        std::cin >> ace1or10;
                    }
                    valueTemp = ace1or10;
                    ace1or10 = 0;
                }
                playerHand.push_back(valueTemp);    //add the draw to the player hand.
                break;
            case 'f':
            case 'F':
                if (playerHand.size() != 0) {
                    gameState = 1; //switch to house turn
                }
                break;
            }
        }

        //the House's turn:
        while (gameState == 1) {
            system("cls");
            std::cout << "---The Houses turn--- \nYour total: " << calcHand(playerHand) << "\n\nThe House will now draw...";
            std::cout << "\nHouse ";
            printHand(houseHand);
            std::cout << "\nHouse Total: " << calcHand(houseHand);

            if (calcHand(houseHand) > 21) {
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

            std::chrono::milliseconds houseWait(2500);
            std::this_thread::sleep_for(houseWait);         //wait a little, for added suspense

            valueTemp = drawCard();
            if (valueTemp == 1) {
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
