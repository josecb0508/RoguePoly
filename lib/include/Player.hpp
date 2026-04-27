#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
//#include <vector>

class Square;

class Player 
{   
private:
    sf::CircleShape circle;
    int current_square_;
    //std::vector<Square>& board_ref;
    Square (&board_squares)[44];
        
public:
    //Player();
    int get_current_square() const;

    Player(Square (&board_ref)[44]);

    void move(int steps);
    void update_position();
    void draw_player(sf::RenderWindow &window) const;
};

#endif
