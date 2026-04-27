#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <SFML/Graphics.hpp>
#include <string>
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

class Player;

class Square
{
public:
    sf::RectangleShape shape;
    std::string name;
    Player* propietary = nullptr;
  
    int width;
    int height;
    int value;
    int level;

    SquareType type;
    Region region;

    //Constructores
    Square();
    Square(SquareType t, Region r, std::string n, Player* p, int v, int l);

    sf::Vector2f get_position() const;
    void orientate(bool horizontal);
    void set_size(int w, int h);
    void print_info_square(int position) const;
    
};

#endif