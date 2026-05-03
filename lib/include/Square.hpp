#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"

enum SquareType
{
    NONE,
    START,
    TERRITORY,
    FREE
};

enum Region
{
    R_NONE,
    RED_ZONE,
    BLUE_ZONE,
    GREEN_ZONE,
    YELLOW_ZONE,
    PURPLE_ZONE
};

class Square
{
    public:
    int width;
    int height;
    SquareType type;
    Region region;
    std::string name;
    Player* propietary;
    int value;
    int level;
    sf::RectangleShape shape;
    sf::Vector2f get_position();
    void orientate(bool horizontal);
    void set_size(int w, int h);
    void print_info_square(int position);
    Square();
    Square(SquareType t, Region r, std::string n, Player* p, int v, int l);
};

#endif