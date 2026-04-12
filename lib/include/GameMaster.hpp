#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP
#include "Board.hpp"
#include "Square.hpp"
#include "Player.hpp"
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>

class GameMaster
{
    public:
        int RollDice();
        void PlayTurn(Player& p);
};






#endif