#ifndef BOARD_HPP
#define BOARD_HPP
#include <SFML/Graphics.hpp>
#include "Square.hpp"

class Board
{
    public:

       Square squares[44];
       void configure_coordinates();
       Square& get_square(int i);
       Board();
       void draw_board(sf::RenderWindow &window);
       void draw_info_panel(sf::RenderWindow &window, int square_index, std::string message);

        sf::Font font;
        sf::Text infoText;
        std::string gameLog; // Nueva variable para mensajes del juego

    Square squares[44];
    void configure_coordinates();
    Square& get_square(int i);
    public:
    Board();
    void draw_board(sf::RenderWindow &window);

};

#endif