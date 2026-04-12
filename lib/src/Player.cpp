#include "Player.hpp"
#include "Square.hpp"

Player::Player(Square (&boardRef)[44]) : boardSquares(boardRef), currentSquareIndex(0) 
{
    circle.setRadius(10.f); 
    circle.setFillColor(sf::Color::White);
    circle.setOutlineThickness(1.5f);
    circle.setOutlineColor(sf::Color::Black);

    UpdatePosition();
}

void Player::move(int steps) 
{
    currentSquareIndex = (currentSquareIndex + steps) % 44;
    
    UpdatePosition();
}

void Player::UpdatePosition() 
{
    sf::Vector2f squarePos = boardSquares[currentSquareIndex].getPosition();
    
    float margin_offset = 5.f;

    circle.setPosition(squarePos.x + margin_offset, squarePos.y + margin_offset);
}

int Player::get_currentSquare() 
{
    return currentSquareIndex;
}   

void Player::draw(sf::RenderWindow &window) 
{
    window.draw(circle);
}