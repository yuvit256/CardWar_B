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

void distributeCards(Card deck[], int n, vector<Card> &player1, vector<Card> &player2, int m)
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
    this->player1 = player1;
    this->player2 = player2;
    if (this->player1.getName() == this->player2.getName())
    {
        throw invalid_argument("Same player can't play the game alone");
    }
    Card deck[52];
    for (int i = 0; i < 52; i++)
    {
        if ((i >= 0) && (i <= 12))
        {
            Card c;
            c.setShape(Spades);
            c.setVal((i % 13) + 1);
            deck[i] = c;
        }
        if ((i >= 13) && (i <= 25))
        {
            Card c;
            c.setShape(Hearts);
            c.setVal((i % 13) + 1);
            deck[i] = c;
        }
        if ((i >= 26) && (i <= 38))
        {
            Card c;
            c.setShape(Diamonds);
            c.setVal((i % 13) + 1);
            deck[i] = c;
        }
        if ((i >= 39) && (i <= 51))
        {
            Card c;
            c.setShape(Clubs);
            c.setVal((i % 13) + 1);
            deck[i] = c;
        }
    }
    srand(time(NULL));
    vector<Card> player1C, player2C;
    distributeCards(deck, 52, player1C, player2C, 26);
    this->player1.setCardsDeck(&player1C);
    this->player2.setCardsDeck(&player2C);
    this->player1.setStackSize(26);
    this->player2.setStackSize(26);
}

void Game::playTurn()
{
    vector<Card> *player1CD;
    vector<Card> *player2CD;
    vector<Card> *player1UC;
    vector<Card> *player2UC;
    player1CD = this->player1.getCardsDeck();
    player2CD = this->player2.getCardsDeck();
    player1UC = this->player1.getUsedCards();
    player2UC = this->player2.getUsedCards();
    if (player1CD->empty())
    {
        throw invalid_argument("Can't play you have empty stack of cards");
    }
    else
    {
        Card c1p = player1CD->back(); //
        player1CD->pop_back();
        int ss1 = this->player1.getStackSize(); // we took 1 card from player1
        this->player1.setStackSize(--ss1);
        if (player2CD->empty())
        {
            throw invalid_argument("Can't play you have empty stack of cards");
        }
        else
        {
            Card c2p = player2CD->back();
            player2CD->pop_back();
            int ss2 = this->player2.getStackSize(); // we took 1 card from player2
            this->player2.setStackSize(--ss2);
            cout << "Player1 card value is " << c1p.getVal() << " of " << c1p.getShape() << "\n";
            cout << "Player2 card value is " << c2p.getVal() << " of " << c2p.getShape() << "\n";
            cout << "the addres is " << &c1p << "\n";
            cout << "the addres is " << &c2p << "\n";
            player1UC->push_back(c1p);
            player2UC->push_back(c2p);
            if (c1p.getVal() > c2p.getVal())
            {
                int p1w = this->player1.getWins();      // Player 1 won so we up by 1 the wins
                int p1cw = this->player1.getCardsWon(); // Player1 won so he won 1 another card
                this->player1.setWins(++p1w);
                this->player1.setCardsWon(++p1cw);
                int cl2 = this->player2.getCardsLost(); // Player 2 lost so we up by 1 the lost cards
                this->player2.setCardsLost(++cl2);
                int ssp1 = this->player1.getCardsDeckSize() - 1;
                int ssp2 = this->player2.getCardsDeckSize() - 1;
                this->player1.setStackSize(ssp1);
                this->player2.setStackSize(ssp2);
            }
            else if (c1p.getVal() < c2p.getVal())
            {
                int p2w = this->player2.getWins();      // Player 2 won so we up by 1 the wins
                int p2cw = this->player2.getCardsWon(); // Player2 won so he won 1 another card
                this->player2.setWins(++p2w);
                this->player2.setCardsWon(++p2cw);
                int cl1 = this->player1.getCardsLost(); // Player 1 lost so we up by 1 the lost cards
                this->player1.setCardsLost(++cl1);
                int ssp1 = this->player1.getCardsDeckSize() - 1;
                int ssp2 = this->player2.getCardsDeckSize() - 1;
                this->player1.setStackSize(ssp1);
                this->player2.setStackSize(ssp2);
            }
            else if (c1p.getVal() == c2p.getVal())
            {
                int p1d = this->player1.getDraws(); // the number of draws for player 1
                int p2d = this->player2.getDraws(); // the number of draws for player 2
                this->player1.setDraws(++p1d);
                this->player2.setDraws(++p2d);
                player1UC->push_back(player1CD->back());
                player2UC->push_back(player2CD->back());
                player1CD->pop_back(); // The upside down card of player1
                player2CD->pop_back(); // The upside down card of player2
                int ssp1 = this->player1.getCardsDeckSize() - 2;
                int ssp2 = this->player2.getCardsDeckSize() - 2;
                this->player1.setStackSize(ssp1);
                this->player2.setStackSize(ssp2);
            }
        }
    }
    this->player1.setCardsDeck(player1CD);
    this->player2.setCardsDeck(player2CD);
    this->player1.setUsedCards(player1UC);
    this->player2.setUsedCards(player2UC);
    int p1t = this->player1.getTurns(); // the number of turns for player 1
    int p2t = this->player2.getTurns(); // the number of turns for player 2
    if (p1t == 26)
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
}

void Game::playAll()
{
    for (int i = this->player1.getTurns(); i <= 26; i++)
    {
        playTurn();
    }
}

void Game::printWiner()
{
}

void Game::printLog()
{
}

void Game::printStats()
{
}
