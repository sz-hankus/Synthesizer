#include <iostream>
#include <string>
#include "../include/DropdownMenu.h"


DropdownMenu::DropdownMenu(sf::Vector2f position, sf::Vector2f fieldDimensions, std::vector <std::string> items) {
    float unit = fieldDimensions.y; // unit = height of one field
    m_position = position;
    m_fieldDimensions = fieldDimensions;
    m_extended = false;
    // load font
    if( !m_font.loadFromFile("assets/VeraMono.ttf") ) {
        std::cerr << "Error loading font from file." <<  std::endl;
    }

    // load textures
    if ( !m_arrowDown_texture.loadFromFile("assets/arrowDown.png") ) {
        std::cerr << "Error loading texture from file." <<  std::endl;
    }
    if ( !m_checkMark_texture.loadFromFile("assets/checkMark.png") ) {
        std::cerr << "Error loading texture from file." <<  std::endl;
    }

    // init arrow down sprite
    m_arrowDown.setTexture(m_arrowDown_texture);
    m_arrowDown.setScale(sf::Vector2f(0.3,0.3));
    m_arrowDown.setPosition(position.x + 2*unit, position.y);

    // init all the items in the menu
    m_items.resize(items.size());
    m_fields.resize(items.size());
    for (int i = 0; i < items.size(); i++) {
        m_fields[i].setSize(fieldDimensions);
        m_fields[i].setPosition(position + sf::Vector2f(0, fieldDimensions.y * i));
        unHighlightField(i);
        m_fields[i].setOutlineThickness(2.0);

        m_items[i].setFont(m_font);
        m_items[i].setString(items[i]);
        m_items[i].setPosition(position + sf::Vector2f(0.8*unit, (fieldDimensions.y * i) + 0.25*unit));
        m_items[i].setFillColor(sf::Color(237, 237, 236));
        m_items[i].setCharacterSize(0.4*unit);
    }
     // init check mark sprite (when menu is extended)
    m_checkMark.setTexture(m_checkMark_texture);
    m_checkMark.setScale(sf::Vector2f(0.2,0.2));
    int indexOfChosen = indexOf(items[0]);
    m_checkMark.setPosition(position.x, position.y + (indexOfChosen * unit) + 0.2*unit);

    // init background (when extended)
    float radius = 0.3*unit;
    m_extendedBackground.setFillColor(sf::Color(50, 50, 51));
    m_extendedBackground.setSize(sf::Vector2f(fieldDimensions.x + 2*radius,
                                 items.size()*fieldDimensions.y + 2*radius));
    m_extendedBackground.setPosition(sf::Vector2f(position.x - radius, position.y - radius));
    m_extendedBackground.setRadius(radius);

    // init chosen item text (when menu is folded)
    sf::Text copy = m_items[0];
    m_chosenItem = copy;
    m_chosenItem.setPosition(sf::Vector2f(position.x + 0.3*unit, position.y + 0.25 * unit));
    m_chosenItem.setFillColor(sf::Color::Black);

    // init main field (when menu is folded)
    m_mainField.setSize(fieldDimensions);
    m_mainField.setPosition(position);
    m_mainField.setFillColor(sf::Color::White);
    m_mainField.setOutlineColor(sf::Color::Black);
    m_mainField.setOutlineThickness(2.0);
    m_mainField.setRadius(radius);
}

void DropdownMenu::extend() {
    m_extended = true;
}

void DropdownMenu::fold() {
    m_extended = false;
}

bool DropdownMenu::isExtended() {
    return m_extended;
}

std::string DropdownMenu::getChosenString() {
    return m_chosenItem.getString();
}

int DropdownMenu::indexOf(std::string item) {
    for (int i = 0; i < m_items.size(); i++) {
        if(m_items[i].getString() == item)
            return i;
    }
    return -1;
}

void DropdownMenu::highlightField(uint index) {
    m_fields[index].setFillColor(sf::Color(56, 116, 240, 120));
    m_fields[index].setOutlineColor(sf::Color(56, 116, 240, 255));
}

void DropdownMenu::unHighlightField(uint index) {
    m_fields[index].setFillColor(sf::Color(56, 116, 240, 0));
    m_fields[index].setOutlineColor(sf::Color(56, 116, 240, 0));
}

void DropdownMenu::draw(sf::RenderWindow &window) {
    if(m_extended) {
        window.draw(m_extendedBackground);
        for (int i = 0; i < m_items.size(); i++) {
            window.draw(m_fields[i]);
            window.draw(m_items[i]);
        }
        window.draw(m_checkMark);
    } else {
        window.draw(m_mainField);
        window.draw(m_chosenItem);
        window.draw(m_arrowDown);
    }
}

void DropdownMenu::handleMouseEvent(sf::Event event) {
    // A Rectangle encompassing all fields
    sf::Vector2f fieldsRectSize(m_fields[0].getSize().x,
                                m_fields[0].getSize().y * m_fields.size());
    sf::FloatRect fieldsRect(m_fields[0].getPosition(), fieldsRectSize);
    
    // HANDLE PRESS
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f coords(event.mouseButton.x, event.mouseButton.y);

            if(m_extended) {

                if (fieldsRect.contains(coords)) {
                    int selectedIndex = (coords.y - fieldsRect.top)/m_fieldDimensions.y;
                    sf::Text selectedItem = m_items[selectedIndex];
                    m_chosenItem.setString(selectedItem.getString());
                    float unit = m_fieldDimensions.y;
                    m_checkMark.setPosition(m_position.x, m_position.y + (selectedIndex * unit) + 0.2*unit);
                }
                fold();
            } else {
                sf::FloatRect mainFieldRect(m_mainField.getPosition(), m_mainField.getSize());
                if (mainFieldRect.contains(coords))
                    extend();
            }
        }
    }

    // HANDLE MOVE
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f coords(event.mouseMove.x, event.mouseMove.y);

        if(m_extended) {
            if (fieldsRect.contains(coords)) {
                int selectedIndex = (coords.y - fieldsRect.top)/m_fieldDimensions.y;
                highlightField(selectedIndex);

                if (selectedIndex != m_highlightedFieldIndex) {
                    unHighlightField(m_highlightedFieldIndex);
                    m_highlightedFieldIndex = selectedIndex;
                }
            } else {
                unHighlightField(m_highlightedFieldIndex);
            }
        }
    }
}