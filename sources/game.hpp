#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "player.hpp"
#include "card.hpp"
#include <cstdlib>
namespace ariel
{
    class Game
    {
    public:
        Game(Player &player1, Player &player2);

        void playTurn();

        void printLastTurn();

        void playAll();

        void printWiner();

        void printLog();

        void printStats();

    private:
        Player &player1;

        Player &player2;
    };
};

#endif