#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>

class Point
{
public:
    Point(const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;

private:
    sf::Vector2f position;
};

#endif