#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Player.hpp"
#include "GameMaster.hpp"

int main() 
{
sf::RenderWindow window(sf::VideoMode(1200, 800), "Roguepoly");
    
    Board board;
    Player player(board.squares); 
    GameMaster gameMaster;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) 
            {
                gameMaster.PlayTurn(player);
                int i = player.get_currentSquare();
                board.squares[i].get_square(i);
            }
        }

        window.clear(sf::Color(80, 80, 80)); 

        board.drawboard(window);
        player.draw(window);

        window.display();
    }

    return 0;
}