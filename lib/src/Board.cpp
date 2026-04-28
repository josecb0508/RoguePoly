#include "Board.hpp"

Board::Board() : squares 
{
    Square(START, R_NONE, "START", nullptr, 0, 0),       
    Square(TERRITORY, RED_ZONE, "D1", nullptr, 0, 0),        
    Square(TERRITORY, RED_ZONE, "D2", nullptr, 0, 0),      
    Square(TERRITORY, RED_ZONE, "D3", nullptr, 0, 0),          
    Square(TERRITORY, RED_ZONE, "D4", nullptr, 0, 0),            
    Square(TERRITORY, BLUE_ZONE, "D5", nullptr, 0, 0),           
    Square(TERRITORY, BLUE_ZONE, "D6", nullptr, 0, 0),           
    Square(TERRITORY, BLUE_ZONE, "D7", nullptr, 0, 0),           
    Square(TERRITORY, BLUE_ZONE, "D8", nullptr, 0, 0),         
    Square(TERRITORY, GREEN_ZONE, "D9", nullptr, 0, 0),           
    Square(TERRITORY, GREEN_ZONE, "D10", nullptr, 0, 0),            

    Square(FREE, R_NONE, "Bottom left corner", nullptr, 0, 0),  

    Square(TERRITORY, GREEN_ZONE, "L1", nullptr, 0, 0),            
    Square(TERRITORY, GREEN_ZONE, "L2", nullptr, 0, 0),            
    Square(TERRITORY, YELLOW_ZONE, "L3", nullptr, 0, 0),           
    Square(TERRITORY, YELLOW_ZONE, "L4", nullptr, 0, 0),         
    Square(TERRITORY, YELLOW_ZONE, "L5", nullptr, 0, 0),         
    Square(TERRITORY, YELLOW_ZONE, "L6", nullptr, 0, 0),         
    Square(TERRITORY, PURPLE_ZONE, "L7", nullptr, 0, 0),          
    Square(TERRITORY, PURPLE_ZONE, "L8", nullptr, 0, 0),            
    Square(TERRITORY, PURPLE_ZONE, "L9", nullptr, 0, 0),            
    Square(TERRITORY, PURPLE_ZONE, "L10", nullptr, 0, 0),         

    Square(FREE, R_NONE, "Upper left corner", nullptr, 0, 0),   

    Square(TERRITORY, RED_ZONE, "U1", nullptr, 0, 0),          
    Square(TERRITORY, RED_ZONE, "U2", nullptr, 0, 0),       
    Square(TERRITORY, RED_ZONE, "U3", nullptr, 0, 0),         
    Square(TERRITORY, RED_ZONE, "U4", nullptr, 0, 0),      
    Square(TERRITORY, RED_ZONE, "U5", nullptr, 0, 0),       
    Square(TERRITORY, RED_ZONE, "U6", nullptr, 0, 0),         
    Square(TERRITORY, RED_ZONE, "U7", nullptr, 0, 0),      
    Square(TERRITORY, RED_ZONE, "U8", nullptr, 0, 0),         
    Square(TERRITORY, RED_ZONE, "U9", nullptr, 0, 0),        
    Square(TERRITORY, RED_ZONE, "U10", nullptr, 0, 0),         

    Square(FREE, R_NONE, "Upper left corner", nullptr, 0, 0),

    Square(TERRITORY, R_NONE, "R1", nullptr, 0, 0), 
    Square(TERRITORY, R_NONE, "R2", nullptr, 0, 0),
    Square(TERRITORY, R_NONE, "R3", nullptr, 0, 0), 
    Square(TERRITORY, R_NONE, "R4", nullptr, 0, 0),
    Square(TERRITORY, R_NONE, "R5", nullptr, 0, 0), 
    Square(TERRITORY, R_NONE, "R6", nullptr, 0, 0),
    Square(TERRITORY, R_NONE, "R7", nullptr, 0, 0), 
    Square(TERRITORY, R_NONE, "R8", nullptr, 0, 0),
    Square(TERRITORY, R_NONE, "R9", nullptr, 0, 0),
    Square(TERRITORY, R_NONE, "R10", nullptr, 0, 0)
},
infoText(font)
{
    // Carga de recursos
    if (!font.openFromFile("assets/arial.ttf")) {
        std::cerr << "Error: No se pudo cargar assets/arial.ttf" << std::endl;
    }

    // Configuración del estilo del panel
    infoText.setFont(font);
    infoText.setCharacterSize(18);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition({20.f, 20.f}); 
    
    // Configuración física de las casillas
    configure_coordinates(); 
}

void Board::configure_coordinates() 
{
    const float margin = 2.f;
    const float init_x = 300.f;   
    const float init_y = 700.f;  
    
    for (int i = 0; i <= 11; i++) 
    {
        squares[i].orientate(true);
    }

    float width_row = 0;
    for (int i = 0; i <= 11; i++)
    { 
        width_row += squares[i].shape.getSize().x + margin;
    }
    
    const float right = init_x + width_row - margin; 

    squares[0].shape.setPosition({right - squares[0].shape.getSize().x, init_y - squares[0].shape.getSize().y});
    
    for (int i = 1; i <= 11; i++) 
    {
        float x = squares[i-1].shape.getPosition().x - squares[i].shape.getSize().x - margin;
        float y = init_y - squares[i].shape.getSize().y;
        squares[i].shape.setPosition({x, y}); 
    }

    for (int i = 12; i <= 21; i++) 
    {
        squares[i].orientate(false); 
        float x = squares[11].shape.getPosition().x; 
        float y = squares[i-1].shape.getPosition().y - squares[i].shape.getSize().y - margin;
        squares[i].shape.setPosition({x, y });
    }

    squares[22].orientate(true);
    squares[22].shape.setPosition({squares[11].shape.getPosition().x,squares[21].shape.getPosition().y - squares[22].shape.getSize().y - margin});

    for (int i = 23; i <= 32; i++) 
    {
        squares[i].orientate(true);
        float x = squares[i-1].shape.getPosition().x + squares[i-1].shape.getSize().x + margin;
        float y = squares[22].shape.getPosition().y;
        squares[i].shape.setPosition({x, y});
    }

    squares[33].orientate(true);
    squares[33].shape.setPosition({squares[32].shape.getPosition().x + squares[32].shape.getSize().x + margin, squares[22].shape.getPosition().y});

    for (int i = 34; i <= 43; i++) 
    {
        squares[i].orientate(false);
        float x = squares[0].shape.getPosition().x; 
        float y = squares[i-1].shape.getPosition().y + squares[i-1].shape.getSize().y + margin;
        squares[i].shape.setPosition({x, y});
    }
}

Square& Board::get_square(int i)
{
    return squares[i];
}

void Board::draw_board(sf::RenderWindow &window) 
{
    for (int i = 0; i < 44; ++i) 
    {
        window.draw(squares[i].shape);
    }
}

// Función auxiliar para convertir el Enum a Texto
std::string get_name_of_region(Region r) {
    switch (r) {
        case RED_ZONE:    return "Roja";
        case BLUE_ZONE:   return "Azul";
        case GREEN_ZONE:  return "Verde";
        case YELLOW_ZONE: return "Amarilla";
        case PURPLE_ZONE: return "Morada";
        default:          return "Ninguna";
    }
}

void Board::draw_info_panel(sf::RenderWindow &window, int square_index, std::string message) {
 Square& s = squares[square_index];
    
    // --- SECCIÓN SUPERIOR: ACCIONES Y DADOS ---
    std::string header = ">>> EVENTO ACTUAL <<<\n";
    header += message + "\n"; // Aquí saldrá "Jugador X sacó un: Y"
    header += "----------------------\n";

    // --- SECCIÓN INFERIOR: INFO DE CASILLA ---
    std::string body = "CASILLA: " + s.name + "\n";
    if (s.type == TERRITORY) {
        body += "Zona: " + get_name_of_region(s.region) + "\n";
        body += "Precio: $" + std::to_string(s.value) + "\n";
        body += (s.propietary == nullptr) ? "Estado: Disponible" : "Duenio: " + s.propietary->get_name();
    } else {
        body += "Tipo: Especial\n";
    }

    infoText.setString(header + body);

    // Ajustamos el tamaño del fondo para que se vea ordenado
    sf::RectangleShape bg({350.f, 280.f});
    bg.setFillColor(sf::Color(0, 0, 0, 220)); // Más oscuro para que resalte
    bg.setOutlineThickness(2);
    bg.setOutlineColor(sf::Color::Cyan); // Un color neón para darle estilo
    
    // Lo posicionamos en una esquina que no tape el tablero (ej. arriba a la derecha)
    bg.setPosition({820, 50}); 
    infoText.setPosition({835, 65});

    window.draw(bg);
    window.draw(infoText);
}