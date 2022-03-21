#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "../src/RoundedRectangle.h"
#include "string"

// Class used for the octave switching buttons (left and right arrows)
class Button {
    private:
        sf::Vector2f m_position;
        sf::Vector2f m_dimensions; 

        RoundedRectangleShape m_field;
        sf::Sprite m_iconSprite;
        sf::Texture m_iconTexture;

    public:
        Button(sf::Vector2f position, sf::Vector2f dimensions, std::string iconTexturePath);
        void highlight();
        void unhighlight();
        void draw(sf::RenderWindow &window);
};

#endif