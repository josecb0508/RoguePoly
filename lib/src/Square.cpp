#include "Square.hpp"

// Constructor por defecto: Inicializa una casilla vacía
Square::Square() : 
    width(0), 
    height(0), 
    type(NONE), 
    region(R_NONE), 
    name("Vacio"), 
    propietary(nullptr), 
    value(0), 
    level(0) 
{
    // El puntero 'label' se inicializa automáticamente como nullptr[cite: 6]
    shape.setSize(sf::Vector2f(0.f, 0.f));
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);
}

// Constructor parametrizado: Configura la casilla según su tipo y región
Square::Square(SquareType t, Region r, std::string n, Player* p, int v, int l) : 
    type(t), 
    region(r), 
    name(n), 
    propietary(p), 
    value(v), 
    level(l) 
{
    // Definición de dimensiones básicas[cite: 4]
    if (type == START || type == FREE) 
    {
        width = 80;
        height = 80;
    } 
    else 
    {
        width = 50;
        height = 80;
    }

    shape.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);

    // Asignación de colores según el tipo y zona[cite: 4]
    switch (type)
    {
        case START:
            shape.setFillColor(sf::Color::Cyan);
            break;
        case FREE:
            shape.setFillColor(sf::Color(255, 165, 0)); // Naranja
            break;
        case TERRITORY:
            switch (region)
            {
                case RED_ZONE:    shape.setFillColor(sf::Color::Red); break;
                case BLUE_ZONE:   shape.setFillColor(sf::Color::Blue); break;
                case GREEN_ZONE:  shape.setFillColor(sf::Color::Green); break;
                case YELLOW_ZONE: shape.setFillColor(sf::Color::Yellow); break;
                case PURPLE_ZONE: shape.setFillColor(sf::Color(128, 0, 128)); break;
                default:          shape.setFillColor(sf::Color::White); break;
            }
            break;
        default:
            shape.setFillColor(sf::Color::White);
            break;
    }
}

void Square::set_size(int w, int h) 
{
    width = w;
    height = h;
    shape.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
}

sf::Vector2f Square::get_position()
{
    return shape.getPosition(); 
}

void Square::orientate(bool horizontal) 
{
    if (horizontal) 
    {
        shape.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
    } 
    else 
    {
        shape.setSize(sf::Vector2f(static_cast<float>(height), static_cast<float>(width)));
    }
}

void Square::print_info_square(int position)
{
    std::cout << "Nombre: " << name << " | Posicion: " << position << std::endl;
    if (type == TERRITORY)
    {
        std::cout << " Valor: " << value;
        if (propietary != nullptr) 
            std::cout << " | Dueño: " << propietary->get_name();
        else 
            std::cout << " | Sin dueño";
        std::cout << std::endl;
    }
}