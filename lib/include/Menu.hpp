#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getPressedItem() const { return selectedItemIndex; }
    
    // Control de pantallas del menú
    bool isSelectingPlayers() const { return selectingPlayers; }
    void setSelectingPlayers(bool select);
    
private:
    void updateMenuText();
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuOptions;
    bool selectingPlayers;
    float windowWidth, windowHeight;
};
#endif