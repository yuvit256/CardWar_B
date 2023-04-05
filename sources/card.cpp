#include "card.hpp"
#include <iostream>
using namespace ariel;
using namespace std;

Card::Card(int val, shape shp)
{
    this->val = val;
    this->shp = shp;
}

Card::Card()
{
}

