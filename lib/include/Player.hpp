#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Square;

class Player 
{   
    private:
        int currentSquareIndex;
        sf::CircleShape circle;
        Square (&boardSquares)[44];
    public:

    Player(Square (&boardRef)[44]);
    void move(int steps);

    void UpdatePosition();

    int get_currentSquare();

    void draw(sf::RenderWindow &window);
};

#endif
