#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Player.hpp"
#include "GameMaster.hpp"
#include "Menu.hpp"

enum class GameState { MENU, SORTEO, PLAYING, OPTIONS };
=======
enum class GameState { MENU, PLAYING, OPTIONS };
>>>>>>> 7dc7782560eabf7bc86104da79f534ca49187d00

int main() 
{
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Roguepoly - Alpha");
    window.setFramerateLimit(60);


    sf::Font font;
    if (!font.openFromFile("assets/arial.ttf")) { 
    std::cout << "Error: No se pudo cargar la fuente del sorteo" << std::endl;
    }

    GameState currentState = GameState::MENU;
    Menu menu(1200, 800);
    Board board;
    GameMaster game_master;

    std::vector<Player> players;
    int current_turn_index = 0;
    int player_to_show = 0; 
    std::string last_action_msg = "¡Bienvenidos a Roguepoly!";

    while (window.isOpen()) 
    {
        // --- 1. BLOQUE DE EVENTOS (Lógica de Teclas) ---
        while (const std::optional event = window.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) 
            {
                if (currentState == GameState::MENU) 
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

                            if (selection == 0) menu.setSelectingPlayers(true); 
                            else if (selection == 2) window.close();
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
                           last_action_msg = game_master.set_turn_player(players); 
                           currentState = GameState::SORTEO; 
                        }
                    }
                }
                else if (currentState == GameState::SORTEO) 
                {
                    // Solo salimos del sorteo al presionar Enter
                    if (keyPressed->code == sf::Keyboard::Key::Enter) 
                    {
                        last_action_msg = "¡Inicia la partida!"; 
                        currentState = GameState::PLAYING;
                    }
                }
                else if (currentState == GameState::PLAYING) 
                                
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
                            int suma = game_master.play_turn(p_actual); //
                            p_actual.update_position();
                            player_to_show = current_turn_index;
                            
                            last_action_msg = "Jugador " + std::to_string(current_turn_index + 1) + 
                                              " saco un: " + std::to_string(suma);

                            game_master.give_properties(p_actual, board.get_square(p_actual.get_current_square()));
                            current_turn_index = (current_turn_index + 1) % players.size();
                        }

                     }  
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

        // --- 2. BLOQUE DE DIBUJO (Renderizado) ---
        window.clear(sf::Color(30, 30, 30));

        if (currentState == GameState::MENU) 
        {
            menu.draw(window);
        } 
        else if (currentState == GameState::SORTEO) 
        {
          window.clear(sf::Color(15, 15, 35)); 

          sf::Text title(font, "--- RESULTADOS DEL SORTEO ---", 50);
          title.setFillColor(sf::Color::Yellow);
          title.setPosition({300.f, 50.f});
          window.draw(title);

          sf::Text results(font, last_action_msg, 24); // Aquí se muestran los dados y el orden
          results.setFillColor(sf::Color::White);
          results.setPosition({300.f, 150.f});
          window.draw(results);

          sf::Text hint(font, "Presiona ENTER para ir al tablero", 20);
          hint.setFillColor(sf::Color::Cyan);
          hint.setPosition({450.f, 700.f});
          window.draw(hint);
        }
        else if (currentState == GameState::PLAYING) 
        {
            board.draw_board(window);
            for (auto& p : players) p.draw_player(window);
            
            if (!players.empty()) 
            {
                int idxMostrada = players[player_to_show].get_current_square();
                // El recuadro pequeño SOLO aparece aquí
                board.draw_info_panel(window, idxMostrada, last_action_msg);
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