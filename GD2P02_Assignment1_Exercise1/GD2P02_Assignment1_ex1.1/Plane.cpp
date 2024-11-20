#include "Plane.h"

Plane::Plane(const sf::Vector2f& point, const sf::Vector2f& normal) : point(point), normal(normal) {}

void Plane::draw(sf::RenderWindow& window)
{
    sf::Vertex line[] = 
    {
        sf::Vertex(point),
        sf::Vertex(point + 100.f * normal)  // Extends the line in the direction of the normal
    };
    window.draw(line, 2, sf::Lines);
}

sf::Vector2f Plane::getPoint() const 
{
    return point;
}

sf::Vector2f Plane::getNormal() const 
{
    return normal;
}
