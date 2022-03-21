#include <iostream>
#include "../include/Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f dimensions, std::string iconTexturePath) {
    m_field.setPosition(position);
    m_field.setSize(dimensions);
    m_field.setFillColor(sf::Color::White);
    m_field.setOutlineThickness(2.0);
    m_field.setOutlineColor(sf::Color::Black);

    if (!m_iconTexture.loadFromFile(iconTexturePath)) {
        std::cerr << "Could not load button texture from path: " << iconTexturePath;
    }
    m_iconSprite.setPosition(position);
    m_iconSprite.setTexture(m_iconTexture);
    float scaling = dimensions.x/m_iconTexture.getSize().x;
    m_iconSprite.setScale(sf::Vector2f(scaling, scaling));


}

void Button::highlight() {
    m_field.setFillColor(sf::Color(107,107,107));
}

void Button::unhighlight() {
    m_field.setFillColor(sf::Color::White);
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(m_field);
    window.draw(m_iconSprite);
} 