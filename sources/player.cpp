#include "player.hpp"
#include "card.hpp"
#include <stack>
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
    return this->getStackSize();
}

int Player::cardesTaken()
{
    return this->getCardsWon();
}

string Player::getName()
{
    return this->name;
}
