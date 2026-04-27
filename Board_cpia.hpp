#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include "Square.hpp"

class Board
{
public:
    Square squares[44];
    Board();

    void configure_coordinates();
    Square& get_square(int i);
    const Square& get_square(int i) const;
    void draw_board(sf::RenderWindow &window);
};

#endif