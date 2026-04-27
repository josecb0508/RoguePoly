#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Player.hpp"
#include "GameMaster.hpp"
#include "Menu.hpp"

enum class GameState { MENU, PLAYING, OPTIONS };

int main() 
{
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Roguepoly - Alpha");
    window.setFramerateLimit(60);

    GameState currentState = GameState::MENU;
    Menu menu(1200, 800);
    Board board;
    GameMaster game_master;

    std::vector<Player> players;
    int current_turn_index = 0;
    while (window.isOpen()) 
    {
        while (const std::optional event = window.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>()) 
            {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) 
            {
                                if (currentState == GameState::MENU) 
                {
                    if (keyPressed->code == sf::Keyboard::Key::Up) menu.moveUp();
                    if (keyPressed->code == sf::Keyboard::Key::Down) menu.moveDown();
                    
                    if (keyPressed->code == sf::Keyboard::Key::Enter) 
                    {
                        if (!menu.isSelectingPlayers()) 
                        {
                            int selection = menu.getPressedItem();
                            if (selection == 0) 
                            {
                                menu.setSelectingPlayers(true); 
                            } else if (selection == 2) 
                            {
                                window.close();
                            }
                        } 
                        else 
                        {
                            int numPlayers = menu.getPressedItem() + 1; 
                            players.clear();
                            
                            for (int i = 0; i < numPlayers; ++i) 
                            {
                               Player p(board.squares);
                                
                                if (i == 0) p.set_color(sf::Color::Red);
                                else if (i == 1) p.set_color(sf::Color::Blue);
                                else if (i == 2) p.set_color(sf::Color::Green);
                                else if (i == 3) p.set_color(sf::Color::Yellow);
                                
                                p.set_current_square(0);
                                players.push_back(p);
                            }
                            game_master.set_turn_player(players);
                            current_turn_index = 0;
                            currentState = GameState::PLAYING;
                        }
                    }
                }

                if (currentState == GameState::PLAYING) 
                {
                    if (keyPressed->code == sf::Keyboard::Key::Space) 
                    {
                        if (!players.empty()) 
                        {
                            Player& p_actual = players[current_turn_index];
    
                            game_master.play_turn(p_actual);
                            p_actual.update_position(); 
                             board.draw_board(window);
                             for(auto& p : players) p.draw_player(window);
                             window.display(); 

                            int idx = p_actual.get_current_square();
                            Square& casilla_actual = board.get_square(idx);
                            casilla_actual.print_info_square(idx);
                            game_master.give_properties(p_actual, casilla_actual);

                            current_turn_index = (current_turn_index + 1) % players.size();
                        }
                    }
                    
                    if (keyPressed->code == sf::Keyboard::Key::Escape) 
                    {
                        currentState = GameState::MENU;
                        menu.setSelectingPlayers(false);
                    }
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));

        if (currentState == GameState::MENU) 
        {
            menu.draw(window);
        } 
        else if (currentState == GameState::PLAYING) 
        {
            board.draw_board(window);
            
            for (auto& p : players) {
                p.draw_player(window);
            }
        }

        window.display();
    }
    return 0;
}