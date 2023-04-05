#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "card.hpp"
using namespace std;

namespace ariel
{
    class Player
    {
    public:
        Player(string name);

        Player();

        int stacksize();

        int cardesTaken();

        string getName();

        vector<Card> *getCardsDeck()
        {
            return this->cardsDeck;
        }

        vector<Card> *getUsedCards()
        {
            return this->usedCards;
        }

        void setCardsDeck(vector<Card> *cardsDeck)
        {
            this->cardsDeck = cardsDeck;
        }

        void setUsedCards(vector<Card> *usedCards)
        {
            this->usedCards = usedCards;
        }

        int getCardsDeckSize() const
        {
            return (int)this->cardsDeck->size();
        }

        int getUsedCardsSize() const
        {
            return (int)this->usedCards->size();
        }

        int getCardsLost() const
        {
            return this->cardsLost;
        }

        void setCardsLost(int newLost)
        {
            this->cardsLost = newLost;
        }

        int getWins() const
        {
            return this->wins;
        }

        void setWins(int newWin)
        {
            this->wins = newWin;
        }

        int getTurns() const
        {
            return this->turns;
        }

        void setTurns(int newTurns)
        {
            this->turns = newTurns;
        }

        int getDraws() const
        {
            return this->draws;
        }

        void setDraws(int newDraws)
        {
            this->draws = newDraws;
        }

        int getStackSize() const
        {
            return this->stackSize;
        }

        void setStackSize(int newSize)
        {
            this->stackSize = newSize;
        }

        int getCardsWon() const
        {
            return this->cardsWon;
        }

        void setCardsWon(int amount)
        {
            this->cardsWon = amount;
        }

    private:
        string name;

        vector<Card> *cardsDeck;

        vector<Card> *usedCards;

        int cardsLost = 0;

        int cardsWon = 0;

        int stackSize = 0;

        int wins = 0;

        int turns = 0;

        int draws = 0;
    };
};

#endif