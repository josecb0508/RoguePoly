#ifndef BOARD_HPP
#define BOARD_HPP
#include <SFML/Graphics.hpp>
#include "Square.hpp"

class Board
{
    public:
       // Atributos y Métodos Públicos
       Square squares[44];
       void configure_coordinates();
       Square& get_square(int i);
       Board();
       void draw_board(sf::RenderWindow &window);
       
       // NUEVOS PANELES SEPARADOS
       void draw_square_info(sf::RenderWindow &window, int square_index);
       void draw_player_action(sf::RenderWindow &window, std::string message);
       void draw_purchase_panel(sf::RenderWindow &window, std::string square_name, int price);

    private:
      sf::Font font;       // Primero la fuente
      sf::Text infoText;   // Luego los textos que la usan
      sf::Text actionText;
};
#endif