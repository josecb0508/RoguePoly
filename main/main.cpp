#include <SFML/Graphics.hpp>
#include "Board.hpp"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "RoguePoly");
    window.setFramerateLimit(60);

    Board tablero;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(50, 50, 50)); 
        
        tablero.drawboard(window);
        
        window.display();
    }

    return 0;
}