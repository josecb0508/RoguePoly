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

    int get_current_square();

    void draw_player(sf::RenderWindow &window);
};

#endif
