#include "LineSegment.h"

LineSegment::LineSegment() : startPoint(sf::Vector2f(0, 0)), endPoint(sf::Vector2f(0, 0)) {}

void LineSegment::setStartPoint(const sf::Vector2f& start)
{
    startPoint = start;
}

void LineSegment::setEndPoint(const sf::Vector2f& end)
{
    endPoint = end;
}

sf::Vector2f LineSegment::getStartPoint() const
{
    return startPoint;
}

sf::Vector2f LineSegment::getEndPoint() const 
{
    return endPoint;
}
