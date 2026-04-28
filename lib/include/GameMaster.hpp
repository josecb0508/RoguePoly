#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP
#include "Board.hpp"
#include "Square.hpp"
#include "Player.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>

class GameMaster
{
    public:
        int roll_dice();
        int play_turn(Player& p);
        std::vector<Player> players;
        std::string set_turn_player(std::vector<Player>& players);
        void give_properties(Player&p, Square& s);
};

#endif