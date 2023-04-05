#include <iostream>
#include "game.hpp"
#include "player.hpp"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <stack>
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

void distributeCards(Card deck[], int n, stack<Card> &player1, stack<Card> &player2, int m)
{
    shuffleDeck(deck, n);
    for (int i = 0; i < m; i++)
    {
        player1.push(deck[i]);
        player2.push(deck[i + m]);
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
    stack<Card> player1C, player2C;
    distributeCards(deck, 52, player1C, player2C, 26);
    this->player1.setCardsDeck(&player1C);
    this->player2.setCardsDeck(&player2C);
    this->player1.setStackSize(26);
    this->player2.setStackSize(26);
}

void Game::playTurn()
{
    stack<Card> *player1UC;
    stack<Card> *player2UC;
    player1UC = this->player1.getUsedCards();
    player2UC = this->player2.getUsedCards();
    if (this->player1.getCardsDeck()->empty())
    {
        throw invalid_argument("Can't play you have empty stack of cards");
    }
    else
    {
        Card c1p = this->player1.getCardsDeck()->top();
        this->player1.getCardsDeck()->pop();
        int ss1 = this->player1.getStackSize(); // we took 1 card from player1
        this->player1.setStackSize(--ss1);
        if (this->player2.getCardsDeck()->empty())
        {
            throw invalid_argument("Can't play you have empty stack of cards");
        }
        else
        {
            Card c2p = this->player2.getCardsDeck()->top();
            this->player2.getCardsDeck()->pop();
            int ss2 = this->player2.getStackSize(); // we took 1 card from player2
            this->player2.setStackSize(--ss2);
            if (c1p.getVal() > c2p.getVal())
            {
                player1UC->push(c1p);
                player2UC->push(c2p);
                int p1w = this->player1.getWins();      // Player 1 won so we up by 1 the wins
                int p1cw = this->player1.getCardsWon(); // Player1 won so he won 1 another card
                this->player1.setWins(++p1w);
                this->player1.setCardsWon(++p1cw);
                int cl2 = this->player2.getCardsLost(); // Player 2 lost so we up by 1 the lost cards
                this->player2.setCardsLost(++cl2);
            }
            else if (c1p.getVal() < c2p.getVal())
            {
                player1UC->push(c1p);
                player2UC->push(c2p);
                int p2w = this->player2.getWins();      // Player 2 won so we up by 1 the wins
                int p2cw = this->player2.getCardsWon(); // Player2 won so he won 1 another card
                this->player2.setWins(++p2w);
                this->player2.setCardsWon(++p2cw);
                int cl1 = this->player1.getCardsLost(); // Player 1 lost so we up by 1 the lost cards
                this->player1.setCardsLost(++cl1);
            }
            else if (c1p.getVal() == c2p.getVal())
            {
                player1UC->push(c1p);
                player2UC->push(c2p);
                int p1d = this->player1.getDraws(); // the number of draws for player 1
                int p2d = this->player2.getDraws(); // the number of draws for player 2
                this->player1.setDraws(++p1d);
                this->player2.setDraws(++p2d);
                this->player1.getUsedCards()->push(this->player1.getCardsDeck()->top());
                this->player2.getUsedCards()->push(this->player2.getCardsDeck()->top());
                this->player1.getCardsDeck()->pop(); // The upside down card of player1
                this->player2.getCardsDeck()->pop(); // The upside down card of player2
            }
        }
    }
    this->player1.setCardsDeck(player1UC);
    this->player2.setCardsDeck(player2UC);
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
