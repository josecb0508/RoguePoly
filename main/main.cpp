#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Player.hpp"
#include "GameMaster.hpp"
#include "Menu.hpp"
#include "Element.hpp"

enum class GameState { MENU, SORTEO, PLAYING, OPTIONS, BATTLE_TEST};

void draw_hp_bar(sf::RenderWindow& window, sf::Font& font, Player& p, sf::Vector2f pos) 
{
    sf::RectangleShape back(sf::Vector2f(250.f, 25.f));
    back.setFillColor(sf::Color(100, 0, 0));
    back.setOutlineThickness(2);
    back.setOutlineColor(sf::Color::White);
    back.setPosition(pos);
    
    float hpPercent = std::clamp(static_cast<float>(p.health_points) / 100.f, 0.0f, 1.0f);
    sf::RectangleShape front(sf::Vector2f(250.f * hpPercent, 25.f));
    front.setFillColor(sf::Color::Green);
    front.setPosition(pos);

    std::string elementStr = (p.selected_element == FIRE) ? "FUEGO" : (p.selected_element == ICE) ? "HIELO" : (p.selected_element == WIND) ? "VIENTO" : (p.selected_element == THUNDER) ? "RAYO" : "NEUTRAL";

    sf::Text info(font, p.get_name() + " | ELEMENTO: " + elementStr, 18);
    info.setFillColor(sf::Color::White);
    info.setPosition({pos.x, pos.y - 35.f});

    sf::Text hpText(font, std::to_string(p.health_points) + " / 100", 16);
    hpText.setPosition({pos.x + 90.f, pos.y + 2.f});
    hpText.setFillColor(sf::Color::Black);
    window.draw(back);
    window.draw(front);
    window.draw(info);
    window.draw(hpText);
}

void draw_move_slots(sf::RenderWindow& window, sf::Font& font, Player& p, sf::Vector2f pos, bool isPlayer1) 
{
    for (int i = 0; i < 4; ++i) {
        sf::RectangleShape box(sf::Vector2f(280.f, 45.f));
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color(150, 150, 150));
        box.setFillColor(sf::Color(40, 40, 40));
        box.setPosition({pos.x, pos.y + (i * 55.f)});

        std::string keyHint = isPlayer1 ? std::to_string(i + 1) : std::to_string(i + 7);
        if (i == 3 && !isPlayer1) keyHint = "0";

        std::string moveName = (p.moves[i].name == "None") ? "--- VACIO ---" : p.moves[i].name;
        sf::Text txt(font, "[" + keyHint + "] " + moveName + " (Pwr: " + std::to_string(p.moves[i].power) + ")", 16);
        txt.setPosition({pos.x + 10.f, pos.y + (i * 55.f) + 10.f});

        window.draw(box);
        window.draw(txt);
    }
}


int main() 
{
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Roguepoly - Alpha");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("assets/arial.ttf")) { 
        std::cerr << "Error: No se pudo cargar assets/arial.ttf" << std::endl;
    }

    GameState currentState = GameState::MENU;
    Menu menu(1200.f, 800.f);
    Board board;
    GameMaster game_master;
    MoveFactory factory;

    std::vector<Player> players;
    int current_turn_index = 0;
    int player_to_show = 0; 
    std::string last_action_msg = "¡Bienvenidos a Roguepoly!";

    bool waitingForPurchase = false;
    int squareToBuyIdx = -1;

    while (window.isOpen()) 
    {
        while (const std::optional event = window.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>()) window.close();

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
                        } 
                        else 
                        {
                            int numPlayers = menu.getPressedItem() + 1; 
                            players.clear();
                            for (int i = 0; i < numPlayers; ++i) 
                            {
                                Player p(board.squares); 
                                p.set_name("Jugador " + std::to_string(i+1));
                                p.elements_player[0] = NEUTRAL;
                                p.elements_player[1] = FIRE;
                                p.elements_player[2] = ICE;
                                p.elements_player[3] = WIND;
                                p.elements_player[4] = THUNDER;
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
                    if (keyPressed->code == sf::Keyboard::Key::Enter) 
                    {
                        last_action_msg = "¡Que comience el juego!";
                        currentState = GameState::PLAYING;
                    }
                }
                else if (currentState == GameState::PLAYING) 
                {
                    if (keyPressed->code == sf::Keyboard::Key::T && players.size() >= 2) 
                    {
                        players[0].add_move(factory.create_move(2));
                        players[0].add_move(factory.create_move(3));
                        players[0].add_move(factory.create_move(4));
                        players[0].add_move(factory.create_move(5)); 

                        players[1].add_move(factory.create_move(2)); 
                        players[1].add_move(factory.create_move(3));
                        players[1].add_move(factory.create_move(4));
                        players[1].add_move(factory.create_move(5));

                        last_action_msg = "Prueba de Pelea";
                        currentState = GameState::BATTLE_TEST;
                    }
                    if (waitingForPurchase) 
                    {
                        Player& p_actual = players[current_turn_index];
                        Square& s = board.get_square(squareToBuyIdx);

                        if (keyPressed->code == sf::Keyboard::Key::S) 
                        {
                            s.propietary = &p_actual; 
                            p_actual.add_property(&s); 
                            last_action_msg = p_actual.get_name() + " compro " + s.name;
                            waitingForPurchase = false;
                            current_turn_index = (current_turn_index + 1) % (int)players.size();
                        }
                        else if (keyPressed->code == sf::Keyboard::Key::N)
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
                else if(currentState == GameState::BATTLE_TEST)
                {
                    if (keyPressed->code == sf::Keyboard::Key::Escape) currentState = GameState::PLAYING;

                    if (keyPressed->code == sf::Keyboard::Key::Num1) last_action_msg = game_master.resolve_attack(players[0], 0, players[1]).message;
                    if (keyPressed->code == sf::Keyboard::Key::Num2) last_action_msg = game_master.resolve_attack(players[0], 1, players[1]).message;
                    if (keyPressed->code == sf::Keyboard::Key::Num3) last_action_msg = game_master.resolve_attack(players[0], 2, players[1]).message;
                    if (keyPressed->code == sf::Keyboard::Key::Num4) last_action_msg = game_master.resolve_attack(players[0], 3, players[1]).message;
                    
                    if (keyPressed->code == sf::Keyboard::Key::F1) players[0].change_element(FIRE);
                    if (keyPressed->code == sf::Keyboard::Key::F2) players[0].change_element(ICE);
                    if (keyPressed->code == sf::Keyboard::Key::F3) players[0].change_element(WIND);
                    if (keyPressed->code == sf::Keyboard::Key::F4) players[0].change_element(THUNDER);

                    if (keyPressed->code == sf::Keyboard::Key::Num7) last_action_msg = game_master.resolve_attack(players[1], 0, players[0]).message;
                    if (keyPressed->code == sf::Keyboard::Key::Num8) last_action_msg = game_master.resolve_attack(players[1], 1, players[0]).message;
                    if (keyPressed->code == sf::Keyboard::Key::Num9) last_action_msg = game_master.resolve_attack(players[1], 2, players[0]).message;
                    if (keyPressed->code == sf::Keyboard::Key::Num0) last_action_msg = game_master.resolve_attack(players[1], 3, players[0]).message;
                    
                    if (keyPressed->code == sf::Keyboard::Key::F5) players[1].change_element(FIRE);
                    if (keyPressed->code == sf::Keyboard::Key::F6) players[1].change_element(ICE);
                    if (keyPressed->code == sf::Keyboard::Key::F7) players[1].change_element(WIND);
                    if (keyPressed->code == sf::Keyboard::Key::F8) players[1].change_element(THUNDER);
                }
            }
        }

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
                
                board.draw_square_info(window, idxMostrada); 
                board.draw_player_action(window, last_action_msg); 

                if (waitingForPurchase) 
                {
                    Square& s = board.get_square(squareToBuyIdx);
                    board.draw_purchase_panel(window, s.name, s.value);
                }
            }
        }
        else if (currentState == GameState::BATTLE_TEST) 
        {
            draw_hp_bar(window, font, players[0], {100.f, 300.f});
            draw_hp_bar(window, font, players[1], {850.f, 300.f});
            draw_move_slots(window, font, players[0], {50.f, 550.f}, true);
            draw_move_slots(window, font, players[1], {870.f, 550.f}, false);
            
            sf::Text logText(font, last_action_msg, 24);
            logText.setFillColor(sf::Color::Yellow);
            logText.setPosition({350, 100});
            window.draw(logText);
        }

        window.display();
    }
    return 0;
}