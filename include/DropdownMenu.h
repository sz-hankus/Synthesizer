#ifndef DROPDOWNMENU_H
#define DROPDOWNMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "RoundedRectangle.h"


class DropdownMenu {
    private:
        bool m_extended; // is the menu extended 

        sf::Vector2f m_position;
        sf::Vector2f m_fieldDimensions; // dimensions of ONE field
        sf::Font m_font;

        sf::Text m_chosenItem; // currently selected Item
        RoundedRectangleShape m_mainField; // Field displayed when menu is folded (closed)
        
        // sprites and textures
        sf::Sprite m_arrowDown;
        sf::Texture m_arrowDown_texture;
        sf::Sprite m_checkMark;
        sf::Texture m_checkMark_texture;

        std::vector <sf::Text> m_items; // vector of all items (sf::texts)
        uint m_highlightedFieldIndex = 0; 
        std::vector <RoundedRectangleShape> m_fields; // vector of fields when menu is extended
        RoundedRectangleShape m_extendedBackground; // background when menu is extended
    public:
        DropdownMenu(sf::Vector2f position, sf::Vector2f fieldDimensions, std::vector <std::string> items);

        void extend();
        void fold();
        bool isExtended();

        std::string getChosenItem();
        int indexOf(std::string item);
        void highlightField(uint index);
        void unHighlightField(uint index);

        void draw(sf::RenderWindow &window);
        void handleMouseEvent(sf::Event event);
};

#endif