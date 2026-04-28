#include "Player.hpp"
#include "Square.hpp"

Player::Player(Square (&board_ref)[44]) : current_square_(0), board_squares(board_ref)
{
    circle.setRadius(10.f); 
    circle.setFillColor(sf::Color::White);
    circle.setOutlineThickness(1.5f);
    circle.setOutlineColor(sf::Color::Black);

    update_position();
}

void Player::move(int steps) 
{
    current_square_ = (current_square_ + steps) % 44;

    update_position();
}

void Player::update_position() 
{
<<<<<<< HEAD
    sf::RectangleShape& currentShape = board_squares[current_square_].shape;
    
    sf::Vector2f basePos = currentShape.getPosition();
    sf::Vector2f size = currentShape.getSize(); // Obtenemos el tamaño real (80x80 o 50x80)

    sf::Vector2f centerPos = basePos + sf::Vector2f(size.x / 2.f, size.y / 2.f);
=======
    sf::Vector2f basePos = board_squares[current_square_].shape.getPosition();
    
    sf::Vector2f centerPos = basePos + sf::Vector2f(40.f, 40.f);
>>>>>>> 7dc7782560eabf7bc86104da79f534ca49187d00
    
    float radius = circle.getRadius();
    circle.setOrigin({radius, radius});

<<<<<<< HEAD
    float offsetX = size.x * 0.25f;
    float offsetY = size.y * 0.25f;
=======
    float offset = 20.0f;
>>>>>>> 7dc7782560eabf7bc86104da79f534ca49187d00
    
    sf::Color color = circle.getFillColor();
    if (color == sf::Color::Red) 
    {
<<<<<<< HEAD
        circle.setPosition({centerPos.x - offsetX, centerPos.y - offsetY});
    } 
    else if (color == sf::Color::Blue) 
    {
        circle.setPosition({centerPos.x + offsetX, centerPos.y - offsetY});
    } 
    else if (color == sf::Color::Green) 
    {
        circle.setPosition({centerPos.x - offsetX, centerPos.y + offsetY});
    } 
    else if (color == sf::Color::Yellow) 
    {
        circle.setPosition({centerPos.x + offsetX, centerPos.y + offsetY});
=======
        circle.setPosition({centerPos.x - offset, centerPos.y - offset});
    } 
    else if (color == sf::Color::Blue) 
    {
        circle.setPosition({centerPos.x - offset, centerPos.y - offset});
    } 
    else if (color == sf::Color::Green) 
    {
        circle.setPosition({centerPos.x - offset, centerPos.y - offset});
    } 
    else if (color == sf::Color::Yellow) 
    {
        circle.setPosition({centerPos.x - offset, centerPos.y - offset});
>>>>>>> 7dc7782560eabf7bc86104da79f534ca49187d00
    } 
    else 
    {
        circle.setPosition(centerPos);
    }
}

int Player::get_current_square()
{
    return current_square_;
}

void Player::set_current_square(int square_index)
{
    current_square_ = square_index;
    update_position();
}

void Player::set_color(sf::Color color)
{
    circle.setFillColor(color);
}

void Player::set_order(int o)
{
    order = o;
}   

int Player::get_order() const
{
    return order;
}

void Player::add_property(Square* property)
{
    properties.push_back(property);
}

void Player::set_name(std::string n)
{
    name = n;
}   

std::string Player::get_name() const
{
    return name;
}

void Player::draw_player(sf::RenderWindow &window) 
{
    window.draw(circle);
}
