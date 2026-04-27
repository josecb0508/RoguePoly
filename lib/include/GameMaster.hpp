#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

#include <SFML/Graphics.hpp>
#include <random>
#include "Board.hpp"
#include "Player.hpp"

class GameMaster
{
    private:
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;

    public:
        GameMaster();
        int roll_dice();
        void play_turn(Player& p/*, Board& board*/);
};

#endif