#include "player.hpp"
#include "card.hpp"
#include <vector>
#include <iostream>
using namespace ariel;
using namespace std;

Player::Player(string name)
{
    this->name = name;
}

Player::Player()
{
}

int Player::stacksize()
{
    if (this->cardsDeck.empty())
    {
        return 0;
    }
    return this->cardsDeck.size();
}

void Player::addCardToDeck(Card &crd)
{
    this->cardsDeck.push_back(crd);
}

Card Player::getCard()
{
    return this->cardsDeck.back();
}

void Player::addCardToUDeck(Card &crd)
{
    this->usedCards.push_back(crd);
}

Card Player::getUCard()
{
    return this->usedCards.back();
}


int Player::cardesTaken()
{
    return this->getCardsWon();
}

string Player::getName()
{
    return this->name;
}
