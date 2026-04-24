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
    sf::Vector2f basePos = board_squares[current_square_].shape.getPosition();
    
    // 2. IMPORTANTE: Calculamos el centro real de la casilla (asumiendo que miden 80x80)
    // Si tus casillas tienen otro tamaño, cambia el 40 por (ancho/2)
    sf::Vector2f centerPos = basePos + sf::Vector2f(40.f, 40.f);
    
    // Esto hace que el "pin" del círculo sea su centro, no su esquina.
    float radius = circle.getRadius();
    circle.setOrigin({radius, radius});

    float offset = 15.0f;
    
    sf::Color color = circle.getFillColor();
    // 4. Posicionamos respecto al CENTRO de la casilla
    if (color == sf::Color::Red) {
        circle.setPosition({centerPos.x - offset, centerPos.y - offset});
    } 
    else if (color == sf::Color::Blue) {
        circle.setPosition({centerPos.x + offset, centerPos.y - offset});
    } 
    else if (color == sf::Color::Green) {
        circle.setPosition({centerPos.x - offset, centerPos.y + offset});
    } 
    else if (color == sf::Color::Yellow) {
        circle.setPosition({centerPos.x + offset, centerPos.y + offset});
    } 
    else {
        circle.setPosition(centerPos);
    }
}


/*int Player::get_current_square() 
{
    return current_square_;
} */  

void Player::draw_player(sf::RenderWindow &window) 
{
    window.draw(circle);
}