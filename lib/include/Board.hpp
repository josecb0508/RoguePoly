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
        void draw_square_info(sf::RenderWindow &window, int square_index);
        void draw_player_action(sf::RenderWindow &window, std::string message);
        void draw_purchase_panel(sf::RenderWindow &window, std::string square_name, int price);

    private:
        sf::Font font;       
        sf::Text infoText; 
        sf::Text actionText;

};
#endif