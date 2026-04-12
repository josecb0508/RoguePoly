#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Player.hpp"
#include "GameMaster.hpp"

void process_events(sf::RenderWindow& window, Player& player, Board& board, GameMaster& game_master) 
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
            game_master.play_turn(player);            
            int i = player.get_current_square();
            board.squares[i].get_square(i);
        }
    }
}

void update_game() 
{

}

void render_game(sf::RenderWindow& window, Board& board, Player& player) 
{
    window.clear(sf::Color(80, 80, 80)); 

    board.draw_board(window);
    
    player.draw_player(window);

    window.display();
}

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Roguepoly");
    window.setFramerateLimit(60);

    Board board;
    Player player(board.squares); 
    GameMaster game_master;

    while (window.isOpen()) 
    {
        process_events(window, player, board, game_master);
        update_game();
        render_game(window, board, player);
    }

    return 0;
}