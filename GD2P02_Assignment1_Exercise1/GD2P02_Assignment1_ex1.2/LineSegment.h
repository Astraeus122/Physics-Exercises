#ifndef LINE_SEGMENT_H
#define LINE_SEGMENT_H

#include <SFML/Graphics.hpp>

class LineSegment
{
private:
    sf::Vector2f startPoint;  // Start point of the line segment
    sf::Vector2f endPoint;    // End point of the line segment

public:
    LineSegment();
    void setStartPoint(const sf::Vector2f& start);
    void setEndPoint(const sf::Vector2f& end);
    sf::Vector2f getStartPoint() const;  // Getter for startPoint
    sf::Vector2f getEndPoint() const;    // Getter for endPoint
};

#endif
