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
    sf::Vector2f square_position = board_squares[current_square_].get_position();

    float margin_offset = 5.f;

    circle.setPosition(square_position.x + margin_offset, square_position.y + margin_offset);
}

int Player::get_current_square() const
{
    return current_square_;
}   

void Player::draw_player(sf::RenderWindow &window) const
{
    window.draw(circle);
}