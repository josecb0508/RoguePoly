#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Player.hpp"
#include "GameMaster.hpp"
#include "Menu.hpp"

enum class GameState { MENU, SORTEO, PLAYING, OPTIONS };

int main() 
{
    // Creación de la ventana con SFML 3
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Roguepoly - Alpha");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("assets/arial.ttf")) { 
        std::cerr << "Error: No se pudo cargar assets/arial.ttf" << std::endl;
    }

    // Inicialización de componentes[cite: 8]
    GameState currentState = GameState::MENU;
    Menu menu(1200.f, 800.f);
    Board board;
    GameMaster game_master;

    std::vector<Player> players;
    int current_turn_index = 0;
    int player_to_show = 0; 
    std::string last_action_msg = "¡Bienvenidos a Roguepoly!";

    // Lógica para el sistema de adquisición de propiedades
    bool waitingForPurchase = false;
    int squareToBuyIdx = -1;

    while (window.isOpen()) 
    {
        // --- 1. PROCESAMIENTO DE EVENTOS ---
        while (const std::optional event = window.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) 
            {
                // LÓGICA DEL MENÚ
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
                            // Realizar sorteo e ir a pantalla de resultados[cite: 9]
                            last_action_msg = game_master.set_turn_player(players); 
                            currentState = GameState::SORTEO; 
                        }
                    }
                }
                // LÓGICA DEL SORTEO
                else if (currentState == GameState::SORTEO) 
                {
                    if (keyPressed->code == sf::Keyboard::Key::Enter) 
                    {
                        last_action_msg = "¡Que comience el juego!";
                        currentState = GameState::PLAYING;
                    }
                }
                // LÓGICA DEL JUEGO
                else if (currentState == GameState::PLAYING) 
                {
                    // Si estamos esperando decisión de compra, bloqueamos movimiento
                    if (waitingForPurchase) 
                    {
                        Player& p_actual = players[current_turn_index];
                        Square& s = board.get_square(squareToBuyIdx);

                        if (keyPressed->code == sf::Keyboard::Key::S) // SI compra
                        {
                            s.propietary = &p_actual; 
                            p_actual.add_property(&s); 
                            last_action_msg = p_actual.get_name() + " compro " + s.name;
                            waitingForPurchase = false;
                            current_turn_index = (current_turn_index + 1) % (int)players.size();
                        }
                        else if (keyPressed->code == sf::Keyboard::Key::N) // NO compra
                        {
                            last_action_msg = "Compra rechazada.";
                            waitingForPurchase = false;
                            current_turn_index = (current_turn_index + 1) % (int)players.size();
                        }
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Space) 
                    {
                        if (!players.empty()) 
                        {
                            Player& p_actual = players[current_turn_index];
                            int suma = game_master.play_turn(p_actual);
                            p_actual.update_position(); 
                            player_to_show = current_turn_index;
                            
                            last_action_msg = p_actual.get_name() + " saco un: " + std::to_string(suma);

                            int idx = p_actual.get_current_square();
                            Square& s = board.get_square(idx);

                            // Verificar si la casilla es comprable[cite: 7]
                            if (s.type == SquareType::TERRITORY && s.propietary == nullptr) 
                            {
                                waitingForPurchase = true;
                                squareToBuyIdx = idx;
                            } 
                            else 
                            {
                                current_turn_index = (current_turn_index + 1) % (int)players.size();
                            }
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

        // --- 2. RENDERIZADO ---
        window.clear(sf::Color(20, 20, 45));

        if (currentState == GameState::MENU) 
        {
            menu.draw(window);
        } 
        else if (currentState == GameState::SORTEO) 
        {
            window.clear(sf::Color(20, 20, 45)); // Fondo azul oscuro
            
            sf::Text title(font, "--- RESULTADOS DEL SORTEO ---", 45);
            title.setFillColor(sf::Color::Yellow);
            title.setPosition({280.f, 50.f});
            window.draw(title);

            // Muestra el log detallado del sorteo[cite: 9]
            sf::Text results(font, last_action_msg, 24);
            results.setFillColor(sf::Color::White);
            results.setPosition({300.f, 180.f});
            window.draw(results);

            sf::Text hint(font, "Presiona ENTER para entrar al tablero", 20);
            hint.setFillColor(sf::Color::Yellow);
            hint.setPosition({420.f, 700.f});
            window.draw(hint);
        }
        else if (currentState == GameState::PLAYING) 
        {
            board.draw_board(window);
            for (auto& p : players) p.draw_player(window);
            
            if (!players.empty()) 
            {
                int idxMostrada = players[player_to_show].get_current_square();
                
                // Paneles laterales a la izquierda (Blancos)[cite: 8]
                board.draw_square_info(window, idxMostrada); 
                board.draw_player_action(window, last_action_msg); 

                // Si hay compra pendiente, dibujar panel central[cite: 8]
                if (waitingForPurchase) 
                {
                    Square& s = board.get_square(squareToBuyIdx);
                    board.draw_purchase_panel(window, s.name, s.value);
                }
            }
        }

        window.display();
    }
    return 0;
}