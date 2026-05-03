#include "Square.hpp"

<<<<<<< HEAD
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
=======
Square::Square() : width(0), height(0), type(NONE), region(R_NONE), name("Vacio"), propietary(nullptr), value(0), level(0) 
{
    shape.setSize(sf::Vector2f(width, height));
>>>>>>> bace37cc8891b3722227d19888758f579e191370
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);
}

<<<<<<< HEAD
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
=======
Square::Square(SquareType t, Region r, std::string n, Player* p, int v, int l) : type(t), region(r), name(n), propietary(p), value(v), level(l)
{
    
    if (type == START || type == FREE)  
    {
        width = 80;
        height = 80;
        level = 0;
        value = 0;
>>>>>>> bace37cc8891b3722227d19888758f579e191370
    } 
    else 
    {
        width = 50;
        height = 80;
    }

<<<<<<< HEAD
    shape.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);

    // Asignación de colores según el tipo y zona[cite: 4]
=======
    shape.setSize(sf::Vector2f(width, height));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);

>>>>>>> bace37cc8891b3722227d19888758f579e191370
    switch (type)
    {
        case START:
            shape.setFillColor(sf::Color::Cyan);
            break;
        case FREE:
<<<<<<< HEAD
            shape.setFillColor(sf::Color(255, 165, 0)); // Naranja
=======
            shape.setFillColor(sf::Color(255, 165, 0));
            break;
        case NONE:
            shape.setFillColor(sf::Color::White);
>>>>>>> bace37cc8891b3722227d19888758f579e191370
            break;
        case TERRITORY:
            switch (region)
            {
<<<<<<< HEAD
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
=======
                case RED_ZONE:    
                    shape.setFillColor(sf::Color::Red); 
                    break;
                case BLUE_ZONE:   
                    shape.setFillColor(sf::Color::Blue); 
                    break;
                case GREEN_ZONE:  
                    shape.setFillColor(sf::Color::Green); 
                    break;
                case YELLOW_ZONE: 
                    shape.setFillColor(sf::Color::Yellow); 
                    break;
                case PURPLE_ZONE: 
                    shape.setFillColor(sf::Color(128, 0, 128)); 
                    break;
                default:
                    shape.setFillColor(sf::Color::White);
                    level = 0;
                    break;
            }
        default:
>>>>>>> bace37cc8891b3722227d19888758f579e191370
            break;
    }
}

void Square::set_size(int w, int h) 
{
    width = w;
    height = h;
<<<<<<< HEAD
    shape.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
=======
    shape.setSize(sf::Vector2f(width, height));
>>>>>>> bace37cc8891b3722227d19888758f579e191370
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
<<<<<<< HEAD
    std::cout << "Nombre: " << name << " | Posicion: " << position << std::endl;
    if (type == TERRITORY)
    {
        std::cout << " Valor: " << value;
        if (propietary != nullptr) 
            std::cout << " | Dueño: " << propietary->get_name();
        else 
            std::cout << " | Sin dueño";
        std::cout << std::endl;
=======
    std::cout <<"Nombre: " << name << std::endl;
    std::cout <<"Posicion: " << position << std::endl;
    if (type == TERRITORY)
    {
        switch (region)
        {
            case RED_ZONE:    
                std::cout <<"Zona: Roja" << std::endl; 
                break;
            case BLUE_ZONE:   
                std::cout <<"Zona: Azul" << std::endl; 
                break;
            case GREEN_ZONE:  
                std::cout <<"Zona: Verde" << std::endl; 
                break;
            case YELLOW_ZONE: 
                std::cout <<"Zona: Amarilla" << std::endl; 
                break;
            case PURPLE_ZONE: 
                std::cout <<"Zona: Morada" << std::endl; 
                break;
            default:
                std::cout <<"Zona: Ninguna" << std::endl;
                break;
        }
        std::cout <<"Valor: " << value << std::endl;
        if(propietary == nullptr)
        {
            std::cout <<"Sin Propietario" << std::endl;
        }
        else
        {
            std::cout << "Estado: PROPIEDAD DE " << propietary->get_name() << std::endl;
        }
    }
    else if(type == START)
    {
        std::cout <<"Casilla de inicio" << std::endl;
    }
    else if(type == FREE)
    {
        std::cout <<"Casilla free" << std::endl;
    }
    else
    {
        std::cout <<"Casilla nula" << std::endl;
>>>>>>> bace37cc8891b3722227d19888758f579e191370
    }
}