#ifndef OCTAVE_SELECTOR_H
#define OCTAVE_SELECTOR_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "RoundedRectangle.h"

const uint OCTAVES = 5;

class OctaveSelector {
    
    private:
        sf::Vector2f m_position;
        sf::Vector2f m_dimensions;

        sf::RectangleShape m_keys[12*OCTAVES + 6];
        RoundedRectangleShape m_selector;
        uint m_selectorOct;

        void initKeys();
        void initSelector();
    public:
        OctaveSelector(sf::Vector2f position, sf::Vector2f dimensions, uint selectorOct = 5);
        void setSelectorOct(uint oct);

        void draw(sf::RenderWindow &window);
        void highlightKey(uint index);
        void unHighlightKey(uint index);
};

#endif