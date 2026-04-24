#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Square;

class Player 
{   
    private:
        int current_square_;
        sf::CircleShape circle;
        Square (&board_squares)[44];
    public:

    Player(Square (&board_ref)[44]);
    void move(int steps);
    void update_position();
    void draw_player(sf::RenderWindow &window);
    
    int get_current_square() { return current_square_;}
    
    void set_current_square(int square_index) {
    current_square_ = square_index;
    update_position();} // Para que el círculo se mueva visualmente a la casilla

    void set_color(sf::Color color) {
    circle.setFillColor(color);}
};

#endif
