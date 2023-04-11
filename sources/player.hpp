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

        void addCardToDeck(Card &crd);

        void removeCard()
        {
            this->cardsDeck.pop_back();
        }

        Card getCard();

        void addCardToUDeck(Card &crd);

        void removeUCard()
        {
            this->usedCards.pop_back();
        }

        Card getUCard();

        int getCardsDeckSize() const
        {
            return (int)this->cardsDeck.size();
        }

        int getUsedCardsSize() const
        {
            return (int)this->usedCards.size();
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

        vector<Card> cardsDeck;

        vector<Card> usedCards;

        int cardsLost = 0;

        int cardsWon = 0;

        int wins = 0;

        int turns = 0;

        int draws = 0;
    };
};

#endif