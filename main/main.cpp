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
                gameMaster.play_turn(player);
                int i = player.get_current_square();
                board.squares[i].get_square(i);
            }
        }

        window.clear(sf::Color(80, 80, 80)); 

        board.draw_board(window);
        player.draw_player(window);

        window.display();
    }

    return 0;
}