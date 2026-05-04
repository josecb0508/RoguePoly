#include "Player.hpp"
#include "Square.hpp"

Player::Player(Square (&board_ref)[44]) : current_square_(0), board_squares(board_ref), money(1500), health_points(100), power_points(50), attack(10), defense(5), velocity(5), selected_element(NEUTRAL)
{
    circle.setRadius(10.f); 
    circle.setFillColor(sf::Color::White);
    circle.setOutlineThickness(1.5f);
    circle.setOutlineColor(sf::Color::Black);
    for(int i = 0; i < 4; ++i)
    {
        moves[i] = MoveFactory::get_move().create_move(0);
    }
    moves[0] = MoveFactory::get_move().create_move(1);
    elements_player[0] = NEUTRAL;
    for(int i = 1; i < 5; ++i)
    { 
        elements_player[i] = NEUTRAL;
    }
    selected_element = NEUTRAL;
    update_position();
}

void Player::move(int steps) 
{
    current_square_ = (current_square_ + steps) % 44;
    update_position();
}

void Player::update_position() 
{
    sf::RectangleShape& currentShape = board_squares[current_square_].shape;
    
    sf::Vector2f basePos = currentShape.getPosition();
    sf::Vector2f size = currentShape.getSize();

    sf::Vector2f centerPos = basePos + sf::Vector2f(size.x / 2.f, size.y / 2.f);
    
    float radius = circle.getRadius();
    circle.setOrigin({radius, radius});

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

void Player::change_element(Element element)
{
    bool has_element = false;
    for (int i = 0; i < 5; ++i) 
    {
        if (elements_player[i] == element) 
        {
            has_element = true;
            break;
        }
    }

    if (has_element) 
    {
        selected_element = element;
    }
}

float Player::damage_multiplicator(Element attacker, Element defender) 
{

    if (attacker == FIRE && defender == ICE) 
    {
        return 2.0f;
    }
    if (attacker == ICE && defender == WIND) 
    {
        return 2.0f;
    }
    if (attacker == WIND && defender == FIRE) 
    {
        return 2.0f;
    }
    if (attacker == THUNDER && defender == WIND) 
    {
        return 2.0f;
    }

    if (attacker == defender && attacker != NEUTRAL) 
    {
        return 0.5f;
    }

    return 1.0f;
}

void Player::add_move(Moves move) 
{
    for (int i = 0; i < 4; ++i) 
    {
        if (moves[i].name == "None" || moves[i].name == "Move not valid") 
        {
            moves[i] = move;
            return;
        }
    }

}

void Player::draw_player(sf::RenderWindow &window) 
{
    window.draw(circle);
}
