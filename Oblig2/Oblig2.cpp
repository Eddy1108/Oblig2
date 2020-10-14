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
int ace1or11{ 0 };      //variable where you store what you want the ace to be
int gameState{ 0 };     //0 = playing, 1 = betting, 2 = houses turn

int playerMoney{ 100 };
int houseMoney{ 100 };
int playerBet{ 0 };
int houseBet{ 0 };


int drawCard() 
{
    int cardValue = rand() % 13 + 1;
    if (cardValue > 10) 
    {
        cardValue = 10;
    }
    return cardValue;
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

void drawMenu(std::vector<int> &playerHand, std::vector<int> &houseHand)
{
    system("cls");
    input = ' ';        //reset the input so nothing loops by accident
    std::cout << "-----Player Turn-----\n";
    printHand(playerHand);
    std::cout << "\nTotal: " << calcHand(playerHand) << std::endl;
    std::cout << "\n---Press D to draw \n---Press F to finish---" << std::endl;

    if (calcHand(playerHand) > 21)      //Loss
    {
        std::cout << "\nYour hand went over 21! You Lose!\n";
        houseMoney += playerBet;
        gameState = 3;  //Restart
        system("pause");
        return;
    }

    //Player Input.
    input = _getch();
    switch (input) {
    case 'd':
    case 'D':
        valueTemp = drawCard();     //Store the random card so we can check if its an Ace
        if (valueTemp == 1)
        {
            std::cout << "\nYou got an Ace, do you want [1] or [11]? (type 1 or 11): ";
            while (ace1or11 != 1 && ace1or11 != 11)     //Make sure you can only choose 1 or 11 when you get an Ace.
            {
                std::cin >> ace1or11;
            }
            valueTemp = ace1or11;
            ace1or11 = 0;
        }

        playerHand.push_back(valueTemp);    //add the draw to the player hand.
        break;
    case 'f':
    case 'F':
        if (playerHand.size() != 0)
        {
            gameState = 1; //switch to betting
            return;
        }
        break;
    }
}

void bettingMenu(std::vector<int> &playerHand, std::vector<int> &houseHand)
{
    system("cls");
    std::cout << "-----Betting-----\n";
    std::cout << "Your money: $" << playerMoney << "\n" << "House Money: $" << houseMoney << "\nHow much would you like to bet? \n(The house will always match your bet if they can)";
    std::cout << "\nBet: $";
    std::cin >> valueTemp;
    if (valueTemp > playerMoney)
    {
        std::cout << "\nYou do not have that much money...\n";
        system("pause");
    }
    else if (valueTemp > houseMoney)
    {
        std::cout << "\nThe House cannot match your bet...\n";
        system("pause");
    }
    else
    {
        playerMoney -= valueTemp;   //remove bet from player
        playerBet += valueTemp;     //add bet to separate bet variable

        if (valueTemp == 0 && playerMoney == 0)         //The House is generous, if you can only afford the minimum fee and no bet, the house will match the fee.
        {
            houseMoney -= 10;       
            houseBet += 10;
        }
        else
        {
            houseMoney -= valueTemp;    //remove bet from house
            houseBet += valueTemp;      //add bet to separate bet variable
        }
        gameState = 2;  // change to house round
    }
}

void houseMenu(std::vector<int> &playerHand, std::vector<int> &houseHand)
{
    system("cls");
    std::cout << "-----The Houses turn----- \nYour total: " << calcHand(playerHand) << "\nThe Pot: $" << (playerBet + houseBet) << "\n\nThe House will now draw...";
    std::cout << "\nHouse ";
    printHand(houseHand);
    std::cout << "\nHouse Total: " << calcHand(houseHand);

    if (calcHand(houseHand) > 21)                           //Win
    {
        playerMoney += (playerBet + houseBet);
        std::cout << "\n\nThe House busts! You win!\n";
        gameState = 0;
        system("pause");
        return;
    }

    if (calcHand(houseHand) == calcHand(playerHand))        //Tie
    {
        playerMoney += playerBet;
        houseMoney += houseBet;
        std::cout << "\n\nIts a Match! Game Tied!\n";
        gameState = 0;
        system("pause");
        return;
    }

    if (calcHand(houseHand) > calcHand(playerHand) && calcHand(houseHand) <= 21)        //Loss
    {
        if (calcHand(houseHand) == 21)
        {
            std::cout << "\n\nBlackjack!";
        }
        houseMoney += (playerBet + houseBet);
        std::cout << "\n\nThe House got higher cards! You Lose!\n";
        gameState = 0;
        system("pause");
        return;
    }

    std::chrono::milliseconds houseWait(1500);
    std::this_thread::sleep_for(houseWait);         //wait a little, for added suspense

    valueTemp = drawCard();
    if (valueTemp == 1)     //Ace check
    {
        if ((calcHand(houseHand) + 11) > 21) {  //if adding 11 to the hand would bust the house, add 1 instead.
            valueTemp = 1;
        }
        else
        {
            valueTemp = 11;
        }
    }
    houseHand.push_back(valueTemp);  //add the draw to the hand
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));      //make the rand() function actually give random values

    while (true) //Loop everything
    {
        system("cls");
        gameState = 0;
        playerBet = 0;
        houseBet = 0;
        std::vector<int> playerHand{};      //initialize player and house hands at the start to "restart" or "empty" them.
        std::vector<int> houseHand{};

        //Main Menu
        std::cout << "-------- Welcome to Blackjack! -------- \n\t    Your Money: $" << playerMoney << "\n\t   House Money: $" << houseMoney << "\n   Press any Key to begin (Costs $10)";
        _getch();

        if (houseMoney == 0) 
        {
            std::cout << "\n\nThe house is out of money, Leave!\n\n";
            exit(0);
        }
        if (playerMoney < 10) 
        {
            std::cout << "\n\nYou can no longer afford the minimum fee, please leave.\n\n";
            exit(0);
        }
        playerMoney -= 10;
        playerBet += 10;

        while (gameState == 0)      //draw menu
        {     
            drawMenu(playerHand, houseHand);
        }

        while (gameState == 1)      //Betting
        {
            bettingMenu(playerHand, houseHand);
        }

        while (gameState == 2)      //the House's turn:
        {
            houseMenu(playerHand, houseHand);
        }
    }
}
