#include "Point.h"

Point::Point(const sf::Vector2f& position) : position(position) {}

void Point::draw(sf::RenderWindow& window) 
{
    sf::CircleShape shape(5);
    shape.setPosition(position - sf::Vector2f(5, 5));  // Center the circle on the position
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);
}

sf::Vector2f Point::getPosition() const
{
    return position;
}
