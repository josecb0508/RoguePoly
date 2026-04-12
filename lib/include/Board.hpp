#ifndef BOARD_HPP
#define BOARD_HPP
#include <SFML/Graphics.hpp>
#include "Square.hpp"

class Board
{
    public:
    Square squares[44];
    void configure_coordinates();
    public:
    Board();
    void draw_board(sf::RenderWindow &window);
};

#endif