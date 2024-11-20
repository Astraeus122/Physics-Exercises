#ifndef PLANE_H
#define PLANE_H

#include <SFML/Graphics.hpp>

class Plane 
{
public:
    Plane(const sf::Vector2f& point, const sf::Vector2f& normal);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPoint() const;
    sf::Vector2f getNormal() const;

private:
    sf::Vector2f point;
    sf::Vector2f normal;
};

#endif // PLANE_H