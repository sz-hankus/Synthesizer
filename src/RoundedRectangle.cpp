#include <cmath>
#include "../src/RoundedRectangle.h"

RoundedRectangleShape::RoundedRectangleShape(const sf::Vector2f size, float radius, unsigned int cornerPointCount) {
    m_size = size;
    m_radius = radius;
    m_cornerPointCount = cornerPointCount;
    update();
}

sf::Vector2f RoundedRectangleShape::getSize() {
    return m_size;
}

void RoundedRectangleShape::setSize(sf::Vector2f size) {
    m_size = size;
    update();
}

float RoundedRectangleShape::getRadius() {
    return m_radius;
}

void RoundedRectangleShape::setRadius(float radius) {
    m_radius = radius;
    update();
}

uint RoundedRectangleShape::getCornerPointCount() {
    return m_cornerPointCount;
};

void RoundedRectangleShape::setCornerPointCount(uint count) {
    m_cornerPointCount = count;
    update();
}

std::size_t RoundedRectangleShape::getPointCount() const {
    return m_cornerPointCount * 4;
}

float toRadians(float angle){
    return (angle/180)*M_PI;
}
sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const {
    uint corner = index / m_cornerPointCount; // which corner the index is in

    float deltaAngle = 90.0 / (m_cornerPointCount - 1);

    sf::Vector2f position;
    float angle;
    index = index % m_cornerPointCount;
    switch (corner) {
        case 0:
            angle = 180 - (index*deltaAngle);
            angle = toRadians(angle);
            position.x = m_radius + (cos(angle)*m_radius);
            position.y = m_radius - (sin(angle)*m_radius);
            break;
        case 1:
            angle = 90 - (index*deltaAngle);
            angle = toRadians(angle);
            position.x = m_size.x - m_radius + (cos(angle)*m_radius);
            position.y = m_radius - (sin(angle)*m_radius);
            break;
        case 2:
            angle = 0.0 - (index*deltaAngle);
            angle = toRadians(angle);
            position.x = m_size.x - m_radius + (cos(angle)*m_radius);
            position.y = m_size.y - m_radius + (-1*sin(angle)*m_radius);
            break;
        case 3:
            angle = -90.0 - (index*deltaAngle);
            angle = toRadians(angle);
            position.x = m_radius + (cos(angle)*m_radius);
            position.y = m_size.y - m_radius + (-1*sin(angle)*m_radius);
            break;
    }
    return position;
}