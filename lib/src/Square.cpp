#include "Square.hpp"

Square::Square() : width(0), height(0), type(NONE), region(R_NONE), name("Vacio") {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);
}

Square::Square(SquareType t, Region r, std::string n) : type(t), region(r), name(n) 
{
    
    if (type == START || type == FREE)  
    {
        width = 80;
        height = 80;
    } 
    else 
    {
        width = 50;
        height = 80;
    }

    shape.setSize(sf::Vector2f(width, height));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);

    switch (type)
    {
        case START:
            shape.setFillColor(sf::Color::Cyan);
            break;
        case FREE:
            shape.setFillColor(sf::Color(255, 165, 0));
            break;
        case NONE:
            shape.setFillColor(sf::Color::White);
            break;
        case TERRITORY:
            switch (region)
            {
                case RED_ZONE:    
                    shape.setFillColor(sf::Color::Red); 
                    break;
                case BLUE_ZONE:   
                    shape.setFillColor(sf::Color::Blue); 
                    break;
                case GREEN_ZONE:  
                    shape.setFillColor(sf::Color::Green); 
                    break;
                case YELLOW_ZONE: 
                    shape.setFillColor(sf::Color::Yellow); 
                    break;
                case PURPLE_ZONE: 
                    shape.setFillColor(sf::Color(128, 0, 128)); 
                    break;
                default:
                    shape.setFillColor(sf::Color::White);
                    break;
            }
        default:
            break;
    }

}

void Square::setSize(int w, int h) 
{
    width = w;
    height = h;
    shape.setSize(sf::Vector2f(width, height));
}

sf::Vector2f Square::getPosition()
{
    return shape.getPosition(); 
}

void Square::orientate(bool horizontal) 
{
    if (horizontal) 
    {
        shape.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
    } 
    else 
    {
        shape.setSize(sf::Vector2f(static_cast<float>(height), static_cast<float>(width)));
    }
}