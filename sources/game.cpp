#include <iostream>
#include "game.hpp"
#include "player.hpp"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace ariel;
using namespace std;

void shuffleDeck(Card deck[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int j = rand() % (n - i) + i;
        swap(deck[i], deck[j]);
    }
}

void distributeCards(Card deck[], int n, vector<Card> player1, vector<Card> player2, int m)
{
    shuffleDeck(deck, n);
    for (int i = 0; i < m; i++)
    {
        player1.push_back(deck[i]);
        player2.push_back(deck[i + m]);
    }
}

Game::Game(Player &player1, Player &player2) : player1(player1), player2(player2)
{
    Card deck[52];
    for (int i = 0; i < 52; i++)
    {
        if ((i >= 0) && (i <= 12))
        {
            Card c;
            c.setShape(Spades);
            c.setVal(i % 13);
            deck[i] = c;
        }
        if ((i >= 13) && (i <= 25))
        {
            Card c;
            c.setShape(Hearts);
            c.setVal(i % 13);
            deck[i] = c;
        }
        if ((i >= 26) && (i <= 38))
        {
            Card c;
            c.setShape(Diamonds);
            c.setVal(i % 13);
            deck[i] = c;
        }
        if ((i >= 39) && (i <= 51))
        {
            Card c;
            c.setShape(Clubs);
            c.setVal(i % 13);
            deck[i] = c;
        }
    }
    srand(time(NULL));
    shuffleDeck(deck, 52);
    for (int i = 0; i < 26; i++)
    {
        player1.addCardToDeck(deck[i]);
        player2.addCardToDeck(deck[i + 26]);
    }
}

void Game::playTurn()
{
    vector<Card> player1CD;
    vector<Card> player2CD;
    vector<Card> player1UC;
    vector<Card> player2UC;
    if (this->player1.getName() == this->player2.getName())
    {
        throw invalid_argument("Same player can't play the game alone");
    }
    if (this->player1.getCardsDeckSize() == 0)
    {
        throw invalid_argument("Can't play you have empty stack of cards for player1");
    }
    else
    {
        if (this->player2.getCardsDeckSize() == 0)
        {
            throw invalid_argument("Can't play you have empty stack of cards for player2");
        }
        else
        {
            Card c1p = this->player1.getCard();
            this->player1.removeCard();
            Card c2p = this->player2.getCard();
            this->player2.removeCard();
            this->player1.addCardToUDeck(c1p);
            this->player2.addCardToUDeck(c2p);
            if (c1p.getVal() == c2p.getVal())
            {
                int p1d = this->player1.getDraws(); // the number of draws for player 1
                int p2d = this->player2.getDraws(); // the number of draws for player 2
                this->player1.setDraws(++p1d);
                this->player2.setDraws(++p2d);
                Card c11p = this->player1.getCard();
                Card c22p = this->player2.getCard();
                this->player1.addCardToUDeck(c11p);
                this->player2.addCardToUDeck(c22p);
                int p1cw = this->player1.getCardsWon() + 2;
                int p2cw = this->player2.getCardsWon() + 2;
                this->player1.setCardsWon(p1cw);
                this->player2.setCardsWon(p2cw);
                this->player1.removeCard(); // The upside down card of player1
                this->player2.removeCard(); // The upside down card of player2
            }
            else if ((c1p.getVal() > c2p.getVal()))
            {
                if (c1p.getVal() == 1 && c2p.getVal() == 0)
                {
                    int p1w = this->player1.getWins();          // Player 1 won so we up by 1 the wins
                    int p1cw = this->player1.getCardsWon() + 2; // Player1 won so he won 1 another card
                    this->player1.setWins(++p1w);
                    this->player1.setCardsWon(p1cw);
                    int cl2 = this->player2.getCardsLost(); // Player 2 lost so we up by 1 the lost cards
                    this->player2.setCardsLost(++cl2);
                }
                else if (c1p.getVal() != 1 && c2p.getVal() == 0)
                {
                    int p2w = this->player2.getWins();          // Player 2 won so we up by 1 the wins
                    int p2cw = this->player2.getCardsWon() + 2; // Player2 won so he won 1 another card
                    this->player2.setWins(++p2w);
                    this->player2.setCardsWon(p2cw);
                    int cl1 = this->player1.getCardsLost(); // Player 1 lost so we up by 1 the lost cards
                    this->player1.setCardsLost(++cl1);
                }
                else
                {
                    int p1w = this->player1.getWins();          // Player 1 won so we up by 1 the wins
                    int p1cw = this->player1.getCardsWon() + 2; // Player1 won so he won 1 another card
                    this->player1.setWins(++p1w);
                    this->player1.setCardsWon(p1cw);
                    int cl2 = this->player2.getCardsLost(); // Player 2 lost so we up by 1 the lost cards
                    this->player2.setCardsLost(++cl2);
                }
            }
            else if ((c2p.getVal() > c1p.getVal()))
            {
                if (c2p.getVal() == 1 && c1p.getVal() == 0)
                {
                    int p2w = this->player2.getWins();          // Player 2 won so we up by 1 the wins
                    int p2cw = this->player2.getCardsWon() + 2; // Player2 won so he won 1 another card
                    this->player2.setWins(++p2w);
                    this->player2.setCardsWon(p2cw);
                    int cl1 = this->player1.getCardsLost(); // Player 1 lost so we up by 1 the lost cards
                    this->player1.setCardsLost(++cl1);
                }
                else if (c1p.getVal() == 0 && c2p.getVal() != 1)
                {
                    int p1w = this->player1.getWins();          // Player 1 won so we up by 1 the wins
                    int p1cw = this->player1.getCardsWon() + 2; // Player1 won so he won 1 another card
                    this->player1.setWins(++p1w);
                    this->player1.setCardsWon(p1cw);
                    int cl2 = this->player2.getCardsLost(); // Player 2 lost so we up by 1 the lost cards
                    this->player2.setCardsLost(++cl2);
                }
                else
                {
                    int p2w = this->player2.getWins();          // Player 2 won so we up by 1 the wins
                    int p2cw = this->player2.getCardsWon() + 2; // Player2 won so he won 1 another card
                    this->player2.setWins(++p2w);
                    this->player2.setCardsWon(p2cw);
                    int cl1 = this->player1.getCardsLost(); // Player 1 lost so we up by 1 the lost cards
                    this->player1.setCardsLost(++cl1);
                }
            }
        }
    }
    int p1t = this->player1.getTurns(); // the number of turns for player 1
    int p2t = this->player2.getTurns(); // the number of turns for player 2
    if (p1t > 26)
    {
        throw invalid_argument("The game ends after 26 turns");
    }
    else
    {
        this->player1.setTurns(++p1t);
        this->player2.setTurns(++p2t);
    }
}

void Game::printLastTurn()
{
    string shape[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string value[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    Card p1c = this->player1.getUCard();
    Card p2c = this->player2.getUCard();
    int val1 = p1c.getVal();
    int shp1 = p1c.getShape();
    cout << this->player1.getName() << " played " << value[val1] << " of " << shape[shp1] << "\n";
    int val2 = p2c.getVal();
    int shp2 = p2c.getShape();
    cout << this->player2.getName() << " played " << value[val2] << " of " << shape[shp2] << "\n";
    if (p1c.getVal() == p2c.getVal())
    {
        cout << "Its a tie\n";
    }
    else if ((p1c.getVal() > p2c.getVal()))
    {
        if (p1c.getVal() == 1 && p2c.getVal() == 0)
        {
            cout << this->player1.getName() << " wins\n";
        }
        else if (p1c.getVal() != 1 && p2c.getVal() == 0)
        {
            cout << this->player2.getName() << " wins\n";
        }
        else
        {
            cout << this->player1.getName() << " wins\n";
        }
    }
    else if ((p2c.getVal() > p1c.getVal()))
    {
        if (p2c.getVal() == 1 && p1c.getVal() == 0)
        {
            cout << this->player2.getName() << " wins\n";
        }
        else if (p2c.getVal() != 1 && p1c.getVal() == 0)
        {
            cout << this->player1.getName() << " wins\n";
        }
        else
        {
            cout << this->player2.getName() << " wins\n";
        }
    }
}

void Game::playAll()
{
    while ((this->player1.stacksize() != 0) && (this->player2.stacksize() != 0))
    {
        playTurn();
    }
}

void Game::printWiner()
{
    if (this->player1.stacksize() == 0 && this->player2.stacksize() == 0)
    {
        if (this->player1.cardesTaken() > this->player2.stacksize())
        {
            cout << this->player1.getName() << " wins\n";
        }
        else if (this->player2.cardesTaken() < this->player1.cardesTaken())
        {
            cout << this->player2.getName() << " wins\n";
        }
    }
}

void Game::printLog()
{
    int i = this->player1.getTurns();
    cout << "Turns = " << i << "\n";
    while (i > 0)
    {
        this->printLastTurn();
        this->player1.removeUCard();
        this->player2.removeUCard();
        i--;
    }
}

void Game::printStats()
{
    cout << this->player1.getName() << ": \n";
    cout << "Win rate = " << this->player1.getWins() * 100 / this->player1.getTurns() << "%\n";
    cout << "Cards won = " << this->player1.getCardsWon() << " Cards \n";
    cout << "Draw rate = " << this->player1.getDraws() * 100 / this->player1.getTurns() << "%\n";
    cout << "Draws = " << this->player1.getDraws() << " Draws\n";
    cout << this->player2.getName() << ": \n";
    cout << "Win rate = " << this->player2.getWins() * 100 / this->player2.getTurns() << "%\n";
    cout << "Cards won = " << this->player2.getCardsWon() << " Cards \n";
    cout << "Draw rate = " << this->player2.getDraws() * 100 / this->player2.getTurns() << "%\n";
    cout << "Draws = " << this->player2.getDraws() << " Draws\n";
}
