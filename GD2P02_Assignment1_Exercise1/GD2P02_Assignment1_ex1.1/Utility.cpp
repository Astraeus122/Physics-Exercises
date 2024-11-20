#include "Utility.h"
#include <cmath>

Position findRelativePosition(const Plane& plane, const Point& point) 
{
    sf::Vector2f pointOnPlane = plane.getPoint();
    sf::Vector2f normal = plane.getNormal();
    sf::Vector2f testPoint = point.getPosition();

    // Line equation ax + by + c = 0 derived from normal and point on the plane
    float a = normal.y;
    float b = -normal.x;
    float c = -(a * pointOnPlane.x + b * pointOnPlane.y);

    // Calculate the perpendicular distance from the point to the line
    float distance = std::abs(a * testPoint.x + b * testPoint.y + c) / std::sqrt(a * a + b * b);

    // Determine the relationship based on the distance
    if (fabs(distance) < 0.001)
    {  
        // Using a small threshold for precision issues
        return Position::OnPlane;
    }

    // Determining the side of the line (cross product method simplified)
    float d = (testPoint.x - pointOnPlane.x) * normal.x + (testPoint.y - pointOnPlane.y) * normal.y;
    if (d > 0) 
    {
        return Position::InFront;
    }
    else 
    {
        return Position::Behind;
    }
}
