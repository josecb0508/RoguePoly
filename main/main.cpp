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

    // Lista dinámica de jugadores según la selección del menú
    std::vector<Player> players;
    
    while (window.isOpen()) {
        // 1. GESTIÓN DE EVENTOS
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                
                // --- LÓGICA DEL MENÚ ---
                if (currentState == GameState::MENU) {
                    if (keyPressed->code == sf::Keyboard::Key::Up) menu.moveUp();
                    if (keyPressed->code == sf::Keyboard::Key::Down) menu.moveDown();
                    
                    if (keyPressed->code == sf::Keyboard::Key::Enter) {
                        // Si estamos en el menú principal y pulsamos "Jugar"
                        if (!menu.isSelectingPlayers()) {
                            int selection = menu.getPressedItem();
                            if (selection == 0) {
                                menu.setSelectingPlayers(true); // Activa sub-menú 1-4
                            } else if (selection == 2) {
                                window.close();
                            }
                        } 
                        // Si ya estamos eligiendo la cantidad de jugadores
                        else {
                            int numPlayers = menu.getPressedItem() + 1; // 0->1, 1->2...
                            players.clear();
                            
                            for (int i = 0; i < numPlayers; ++i) {
                               Player p(board.squares);
                                
                                // 1. Asignar un color distinto según el índice i
                                if (i == 0) p.set_color(sf::Color::Red);
                                else if (i == 1) p.set_color(sf::Color::Blue);
                                else if (i == 2) p.set_color(sf::Color::Green);
                                else if (i == 3) p.set_color(sf::Color::Yellow);
                                
                                // Regla: Todos inician en la Puerta del Héroe (Casilla 0)
                                p.set_current_square(0);
                                players.push_back(p);
                            }
                            currentState = GameState::PLAYING;
                        }
                    }
                }

                // --- LÓGICA DEL JUEGO (TECLA ESPACIO) ---
                if (currentState == GameState::PLAYING) {
                    if (keyPressed->code == sf::Keyboard::Key::Space) {
                        // Por ahora, movemos al primer jugador como prueba
                        if (!players.empty()) {
                            game_master.play_turn(players[0]);
                            int i = players[0].get_current_square();
                            board.get_square(i).print_info_square(i);
                        }
                    }
                    
                    if (keyPressed->code == sf::Keyboard::Key::Escape) {
                        currentState = GameState::MENU;
                        menu.setSelectingPlayers(false);
                    }
                }
            }
        }

        // 2. ACTUALIZACIÓN Y DIBUJO
        window.clear(sf::Color(30, 30, 30));

        if (currentState == GameState::MENU) {
            menu.draw(window);
        } 
        else if (currentState == GameState::PLAYING) {
            board.draw_board(window);
            
            // Dibujamos a todos los jugadores que se crearon
            for (auto& p : players) {
                p.draw_player(window);
            }
        }

        window.display();
    }
    return 0;
}