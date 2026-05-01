#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Square;

class Player 
{   
    private:
        int current_square_;
        sf::CircleShape circle;
        Square (*board_squares);
        int order;
        std::vector<Square*> properties;
        std::string name;
    public:

    Player(Square (&board_ref)[44]);

    void move(int steps);
    void update_position();
    void draw_player(sf::RenderWindow &window);
    int get_current_square(); 
    void set_current_square(int square_index);
    void set_color(sf::Color color);
    void set_order(int o);
    int get_order() const; 
    void add_property(Square* property);
    void set_name(std::string n);
    std::string get_name() const;
};

#endif
