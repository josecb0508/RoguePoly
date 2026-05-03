#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"

<<<<<<< HEAD
class Player; // Forward declaration

enum SquareType { NONE, START, TERRITORY, FREE };
enum Region { R_NONE, RED_ZONE, BLUE_ZONE, GREEN_ZONE, YELLOW_ZONE, PURPLE_ZONE };

class Square {
public:
    int width, height;
=======
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
>>>>>>> bace37cc8891b3722227d19888758f579e191370
    SquareType type;
    Region region;
    std::string name;
    Player* propietary;
    int value;
    int level;
<<<<<<< HEAD

    sf::RectangleShape shape;
    std::unique_ptr<sf::Text> label; // Puntero inteligente para SFML 3

    Square();
    Square(SquareType t, Region r, std::string n, Player* p, int v, int l);
    
=======
    sf::RectangleShape shape;
>>>>>>> bace37cc8891b3722227d19888758f579e191370
    sf::Vector2f get_position();
    void orientate(bool horizontal);
    void set_size(int w, int h);
    void print_info_square(int position);
<<<<<<< HEAD
=======
    Square();
    Square(SquareType t, Region r, std::string n, Player* p, int v, int l);
>>>>>>> bace37cc8891b3722227d19888758f579e191370
};

#endif