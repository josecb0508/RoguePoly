#ifndef BOARD_HPP
#define BOARD_HPP
#include <SFML/Graphics.hpp>
#include "Square.hpp"

class Board
{
    Square squares[44];
    void configureCoordinates();
    public:
    Board();
    void drawboard(sf::RenderWindow &window);
};

#endif