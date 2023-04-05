#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

namespace ariel
{
    enum shape
    {
        Spades,
        Hearts,
        Diamonds,
        Clubs
    };
    class Card
    {
    public:
        Card(int val, shape shp);

        Card();

        int getVal() const
        {
            return this->val;
        }

        shape getShape()
        {
            return this->shp;
        }

        void setVal(int val)
        {
            this->val = val;
        }

        void setShape(shape shp)
        {
            this->shp = shp;
        }

    private:
        int val;

        shape shp;
    };
};

#endif