#ifndef PLANE_H
#define PLANE_H

#include <SFML/Graphics.hpp>

class LineSegment;  // Forward declaration

class Plane 
{
private:
    sf::Vector2f point;  // A point on the plane
    sf::Vector2f normal; // Normal vector to the plane

public:
    Plane();
    void setPlane(const sf::Vector2f& p, sf::Vector2f n);
    bool checkCollision(const LineSegment& segment) const;

    sf::Vector2f getPoint() const;  // Getter for point
    sf::Vector2f getNormal() const; // Getter for normal
};

static float dot(const sf::Vector2f& a, const sf::Vector2f& b);

#endif
