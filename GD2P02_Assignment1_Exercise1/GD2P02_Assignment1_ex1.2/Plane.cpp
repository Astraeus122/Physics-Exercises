#include "Plane.h"
#include "LineSegment.h"
#include <iostream>
#include <cmath>

Plane::Plane() : point(sf::Vector2f(0, 0)), normal(sf::Vector2f(0, 1)) {}

void Plane::setPlane(const sf::Vector2f& p, sf::Vector2f n) 
{
    float length = std::sqrt(n.x * n.x + n.y * n.y);
    normal = (length != 0) ? n / length : sf::Vector2f(0, 1);  // Normalize the vector
    point = p;
}

bool Plane::checkCollision(const LineSegment& segment) const
{
    sf::Vector2f start = segment.getStartPoint();
    sf::Vector2f end = segment.getEndPoint();
    sf::Vector2f planePoint = point;
    sf::Vector2f planeNormal = normal;

    // Calculate distances of the start and end points from the plane
    float distStart = dot(start - planePoint, planeNormal);
    float distEnd = dot(end - planePoint, planeNormal);

    // Check if the line segment straddles the plane (crosses from one side to the other)
    if ((distStart > 0 && distEnd < 0) || (distStart < 0 && distEnd > 0)) 
    {
        return true;  // There is a collision
    }

    // Check if the line segment is lying directly on the plane
    if (distStart == 0 || distEnd == 0) 
    {
        return true;  // The line is on the plane
    }

    return false;  // No collision
}


float dot(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return a.x * b.x + a.y * b.y;
}

sf::Vector2f Plane::getPoint() const
{
    return point;
}

sf::Vector2f Plane::getNormal() const
{
    return normal;
}
