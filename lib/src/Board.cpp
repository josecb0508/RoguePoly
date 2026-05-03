#include "Board.hpp"

Board::Board() : 
    squares{
        Square(START, R_NONE, "SALIDA", nullptr, 0, 0),       // 0
        Square(TERRITORY, RED_ZONE, "D1", nullptr, 60, 2),        
        Square(TERRITORY, RED_ZONE, "D2", nullptr, 60, 4),      
        Square(TERRITORY, RED_ZONE, "D3", nullptr, 80, 4),          
        Square(TERRITORY, RED_ZONE, "D4", nullptr, 80, 6),            
        Square(TERRITORY, BLUE_ZONE, "D5", nullptr, 100, 6),           
        Square(TERRITORY, BLUE_ZONE, "D6", nullptr, 100, 8),           
        Square(TERRITORY, BLUE_ZONE, "D7", nullptr, 120, 8),           
        Square(TERRITORY, BLUE_ZONE, "D8", nullptr, 120, 10),         
        Square(TERRITORY, GREEN_ZONE, "D9", nullptr, 140, 10),           
        Square(TERRITORY, GREEN_ZONE, "D10", nullptr, 140, 12),           
        Square(FREE, R_NONE, "PARADA", nullptr, 0, 0),        // 11
        Square(TERRITORY, GREEN_ZONE, "L1", nullptr, 160, 12),            
        Square(TERRITORY, GREEN_ZONE, "L2", nullptr, 160, 14),            
        Square(TERRITORY, YELLOW_ZONE, "L3", nullptr, 180, 14),           
        Square(TERRITORY, YELLOW_ZONE, "L4", nullptr, 180, 16),         
        Square(TERRITORY, YELLOW_ZONE, "L5", nullptr, 200, 16),         
        Square(TERRITORY, YELLOW_ZONE, "L6", nullptr, 200, 18),         
        Square(TERRITORY, PURPLE_ZONE, "L7", nullptr, 220, 18),          
        Square(TERRITORY, PURPLE_ZONE, "L8", nullptr, 220, 20),            
        Square(TERRITORY, PURPLE_ZONE, "L9", nullptr, 240, 20),            
        Square(TERRITORY, PURPLE_ZONE, "L10", nullptr, 240, 22),         
        Square(FREE, R_NONE, "CARCEL", nullptr, 0, 0),        // 22
        Square(TERRITORY, RED_ZONE, "U1", nullptr, 260, 22),          
        Square(TERRITORY, RED_ZONE, "U2", nullptr, 260, 24),       
        Square(TERRITORY, RED_ZONE, "U3", nullptr, 280, 24),         
        Square(TERRITORY, RED_ZONE, "U4", nullptr, 280, 26),      
        Square(TERRITORY, RED_ZONE, "U5", nullptr, 300, 26),       
        Square(TERRITORY, RED_ZONE, "U6", nullptr, 300, 28),         
        Square(TERRITORY, RED_ZONE, "U7", nullptr, 320, 28),      
        Square(TERRITORY, RED_ZONE, "U8", nullptr, 320, 30),         
        Square(TERRITORY, RED_ZONE, "U9", nullptr, 350, 35),        
        Square(TERRITORY, RED_ZONE, "U10", nullptr, 400, 50),         
        Square(FREE, R_NONE, "PARADA", nullptr, 0, 0),        // 33
        Square(TERRITORY, R_NONE, "R1", nullptr, 150, 15), 
        Square(TERRITORY, R_NONE, "R2", nullptr, 150, 15),
        Square(TERRITORY, R_NONE, "R3", nullptr, 150, 15), 
        Square(TERRITORY, R_NONE, "R4", nullptr, 150, 15),
        Square(TERRITORY, R_NONE, "R5", nullptr, 150, 15), 
        Square(TERRITORY, R_NONE, "R6", nullptr, 150, 15),
        Square(TERRITORY, R_NONE, "R7", nullptr, 150, 15), 
        Square(TERRITORY, R_NONE, "R8", nullptr, 150, 15),
        Square(TERRITORY, R_NONE, "R9", nullptr, 150, 15),
        Square(TERRITORY, R_NONE, "R10", nullptr, 150, 15)
    },
    infoText(font),  
    actionText(font)
{
    if (!font.openFromFile("assets/arial.ttf")) {
        std::cerr << "Error cargando fuente arial.ttf" << std::endl;
    }

    sf::Color mundoFuego(255, 40, 40);            
    sf::Color mundoBosque(40, 255, 40);           
    sf::Color mundoHielo(40, 120, 255);           
    sf::Color mundoDesierto(255, 255, 40);        
    sf::Color azulFondo(10, 10, 30);

    for (int i = 0; i < 44; i++) {
        // Asignación de colores
        if (i == 0) squares[i].shape.setFillColor(sf::Color::Cyan);
        else if (i == 22) squares[i].shape.setFillColor(sf::Color(100, 100, 100));
        else if (i == 11 || i == 33) squares[i].shape.setFillColor(sf::Color(255, 255, 255, 220));
        else if (i > 0 && i < 11) squares[i].shape.setFillColor(mundoFuego);
        else if (i > 11 && i < 22) squares[i].shape.setFillColor(mundoBosque);
        else if (i > 22 && i < 33) squares[i].shape.setFillColor(mundoHielo);
        else if (i > 33 && i <= 43) squares[i].shape.setFillColor(mundoDesierto);

        squares[i].shape.setOutlineThickness(-1.0f); 
        squares[i].shape.setOutlineColor(azulFondo);

        // MODIFICACIÓN: Solo crear texto para SALIDA, PARADA y CARCEL[cite: 5, 14]
        if (squares[i].type != TERRITORY) {
            squares[i].label = std::make_unique<sf::Text>(font, squares[i].name, 10);
            squares[i].label->setFillColor(sf::Color::Black);
        } else {
            // Los territorios no tienen etiqueta visual[cite: 5, 6]
            squares[i].label = nullptr; 
        }
    }
    configure_coordinates();
}

void Board::configure_coordinates() 
{
    const float margin = 0.5f; 
    const float init_x = 300.f;   
    const float init_y = 700.f;  
    
    for (int i = 0; i <= 11; i++) squares[i].orientate(true);

    float width_row = 0;
    for (int i = 0; i <= 11; i++) width_row += squares[i].shape.getSize().x + margin;
    
    const float right = init_x + width_row - margin; 
    squares[0].shape.setPosition({right - squares[0].shape.getSize().x, init_y - squares[0].shape.getSize().y});
    
    for (int i = 1; i <= 11; i++) {
        float x = squares[i-1].shape.getPosition().x - squares[i].shape.getSize().x - margin;
        float y = init_y - squares[i].shape.getSize().y;
        squares[i].shape.setPosition({x, y}); 
    }

    for (int i = 12; i <= 21; i++) {
        squares[i].orientate(false); 
        float x = squares[11].shape.getPosition().x; 
        float y = squares[i-1].shape.getPosition().y - squares[i].shape.getSize().y - margin;
        squares[i].shape.setPosition({x, y });
    }

    squares[22].orientate(true);
    squares[22].shape.setPosition({squares[11].shape.getPosition().x, squares[21].shape.getPosition().y - squares[22].shape.getSize().y - margin});

    for (int i = 23; i <= 32; i++) {
        squares[i].orientate(true);
        float x = squares[i-1].shape.getPosition().x + squares[i-1].shape.getSize().x + margin;
        float y = squares[22].shape.getPosition().y;
        squares[i].shape.setPosition({x, y});
    }

    squares[33].orientate(true);
    squares[33].shape.setPosition({squares[32].shape.getPosition().x + squares[32].shape.getSize().x + margin, squares[22].shape.getPosition().y});

    for (int i = 34; i <= 43; i++) {
        squares[i].orientate(false);
        float x = squares[0].shape.getPosition().x; 
        float y = squares[i-1].shape.getPosition().y + squares[i-1].shape.getSize().y + margin;
        squares[i].shape.setPosition({x, y});
    }

    // Centrado de etiquetas (solo si el puntero existe)[cite: 5]
    for (int i = 0; i < 44; i++) {
        if (squares[i].label) {
            sf::FloatRect sB = squares[i].shape.getGlobalBounds();
            sf::FloatRect tB = squares[i].label->getLocalBounds();
            
            squares[i].label->setOrigin({tB.size.x / 2.f, tB.size.y / 2.f});
            squares[i].label->setPosition({
                sB.position.x + (sB.size.x / 2.f),
                sB.position.y + (sB.size.y / 2.f)
            });
        }
    }
}

Square& Board::get_square(int i) { return squares[i]; }

void Board::draw_board(sf::RenderWindow &window) {
    for (int i = 0; i < 44; ++i) {
        window.draw(squares[i].shape);
        // Solo intentamos dibujar si la etiqueta fue creada[cite: 5]
        if (squares[i].label) {
            window.draw(*(squares[i].label));
        }
    }
}

void Board::draw_square_info(sf::RenderWindow &window, int square_index) {
    Square& s = squares[square_index];
    std::string content = "--- PROPIEDAD ---\nNombre: " + s.name + "\n";
    if (s.type == TERRITORY) {
        content += "Precio: $" + std::to_string(s.value) + "\n";
        content += (s.propietary == nullptr) ? "Estado: Disponible" : "Duenio: " + s.propietary->get_name();
    } else {
        content += "Tipo: Especial\n";
    }
    infoText.setString(content);
    infoText.setCharacterSize(16);
    infoText.setFillColor(sf::Color::White);

    sf::RectangleShape bg({250.f, 140.f});
    bg.setFillColor(sf::Color(0, 0, 0, 150)); 
    bg.setOutlineThickness(2);
    bg.setOutlineColor(sf::Color::White); 
    bg.setPosition({20.f, 50.f}); 
    infoText.setPosition({35.f, 65.f});
    window.draw(bg);
    window.draw(infoText);
}

void Board::draw_player_action(sf::RenderWindow &window, std::string message) {
    actionText.setString(">>> EVENTO <<<\n" + message);
    actionText.setCharacterSize(20);
    actionText.setFillColor(sf::Color::White);
    sf::RectangleShape bg({250.f, 90.f});
    bg.setFillColor(sf::Color(0, 0, 0, 150));
    bg.setOutlineThickness(2);
    bg.setOutlineColor(sf::Color::White); 
    bg.setPosition({20.f, 205.f}); 
    actionText.setPosition({35.f, 220.f});
    window.draw(bg);
    window.draw(actionText);
}

void Board::draw_purchase_panel(sf::RenderWindow &window, std::string square_name, int price) {
    sf::RectangleShape bg({400.f, 200.f});
    bg.setFillColor(sf::Color(0, 0, 0, 200));
    bg.setOutlineThickness(3);
    bg.setOutlineColor(sf::Color::White);
    bg.setOrigin({200.f, 100.f});
    bg.setPosition({600.f, 400.f});

    sf::Text text(font, " Deseas adquirir " + square_name + "?\nPrecio: $" + std::to_string(price) + "\n\n[S] Si      [N] No", 20);
    text.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin({textBounds.size.x / 2.f, textBounds.size.y / 2.f}); 
    text.setPosition({600.f, 400.f});

    window.draw(bg);
    window.draw(text);
}