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
    // Obtenemos la referencia a la casilla actual
    sf::RectangleShape& currentShape = board_squares[current_square_].shape;
    
    sf::Vector2f basePos = currentShape.getPosition();
    sf::Vector2f size = currentShape.getSize(); // Soporta tamaños 80x80 o 50x80

    // Centro dinámico basado en el tamaño de la casilla
    sf::Vector2f centerPos = basePos + sf::Vector2f(size.x / 2.f, size.y / 2.f);
    
    float radius = circle.getRadius();
    circle.setOrigin({radius, radius});

    // Desplazamiento para que los 4 colores se repartan en las esquinas
    float offsetX = size.x * 0.25f;
    float offsetY = size.y * 0.25f;

    sf::Color color = circle.getFillColor();

    if (color == sf::Color::Red) 
    {
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
    update_position();
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
