#ifndef ROUNDED_RECTANGLE_H
#define ROUNDED_RECTANGLE_H

#include <SFML/Graphics.hpp>

class RoundedRectangleShape : public sf::Shape{
    private:
        sf::Vector2f m_size;
        float m_radius;
        uint m_cornerPointCount;
    public:
        explicit RoundedRectangleShape(const sf::Vector2f size = sf::Vector2f(100,  100), float radius = 10, unsigned int cornerPointCount = 30);
        // Override functions inherited from sf::Shape 
        virtual std::size_t getPointCount() const;
        virtual sf::Vector2f getPoint(std::size_t index) const;

        void setSize(sf::Vector2f size);
        sf::Vector2f getSize();
        
        void setRadius(float radius);
        float getRadius();

        void setCornerPointCount(uint count);
        uint getCornerPointCount();
};

#endif