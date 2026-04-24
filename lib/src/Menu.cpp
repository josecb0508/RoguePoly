#include "Menu.hpp"

// Corregimos el warning de orden: primero el booleano, luego los floats
Menu::Menu(float width, float height) 
    : selectingPlayers(false), windowWidth(width), windowHeight(height) 
{
    if (!font.openFromFile("assets/arial.ttf")) {
        // Error al cargar fuente
    }
    selectedItemIndex = 0;
    updateMenuText();
}

void Menu::updateMenuText() {
    menuOptions.clear();
    std::vector<sf::String> names;
    
    if (!selectingPlayers) {
        names = {"Jugar", "Opciones", "Salir"};
    } else {
        names = {"1 Jugador", "2 Jugadores", "3 Jugadores", "4 Jugadores"};
    }

    for (size_t i = 0; i < names.size(); ++i) {
        // CORRECCIÓN SFML: Primero la fuente, luego el texto
        sf::Text text(font, names[i], 60);
        
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        
        // CORRECCIÓN SFML: En tu versión se usa .size.x en lugar de .width
        float x = windowWidth / 2.f - text.getLocalBounds().size.x / 2.f;
        float y = windowHeight / (names.size() + 1) * (i + 1);
        
        // CORRECCIÓN SFML: setPosition ahora necesita llaves {} o Vector2f
        text.setPosition({x, y}); 
        menuOptions.push_back(std::move(text));
    }
    selectedItemIndex = 0;
}

void Menu::setSelectingPlayers(bool select) {
    selectingPlayers = select;
    updateMenuText();
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& text : menuOptions) {
        window.draw(text);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuOptions[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < (int)menuOptions.size()) {
        menuOptions[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}