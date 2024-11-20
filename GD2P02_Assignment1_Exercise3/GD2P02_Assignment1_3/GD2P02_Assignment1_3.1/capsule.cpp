#include "Capsule.h"
#include <cmath>

Capsule::Capsule(const sf::Vector2f& pointA, const sf::Vector2f& pointB, float radius)
    : pointA(pointA), pointB(pointB), radius(radius), velocity(150.0f, 50.f)
{
}

void Capsule::update(float dt) 
{
    pointA += velocity * dt;
    pointB += velocity * dt;
}

void Capsule::draw(sf::RenderWindow& window) 
{
    sf::CircleShape circleA(radius);
    sf::CircleShape circleB(radius);
    circleA.setOutlineColor(sf::Color::Red);
    circleA.setOutlineThickness(2.f);
    circleB.setOutlineColor(sf::Color::Red);
    circleB.setOutlineThickness(2.f);

    circleA.setPosition(pointA - sf::Vector2f(radius, radius));
    circleB.setPosition(pointB - sf::Vector2f(radius, radius));

    window.draw(circleA);
    window.draw(circleB);

    // Draw the line segment between the two points as the capsule's body
    sf::Vertex line[] = 
    {
        sf::Vertex(pointA),
        sf::Vertex(pointB)
    };
    window.draw(line, 2, sf::Lines);

    // Draw the capsule border as a rectangle around the line
    sf::RectangleShape capsuleBorder;
    sf::Vector2f direction = pointB - pointA;
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

    capsuleBorder.setSize(sf::Vector2f(length, radius * 2));
    capsuleBorder.setOrigin(0, radius);  // Set origin to align with the endpoints
    capsuleBorder.setPosition(pointA);
    capsuleBorder.setRotation(atan2f(direction.y, direction.x) * 180 / 3.14159f); // Rotate the rectangle to match the capsule's axis
    capsuleBorder.setOutlineColor(sf::Color::Red);
    capsuleBorder.setOutlineThickness(2.f);
    capsuleBorder.setFillColor(sf::Color::Transparent);

    window.draw(capsuleBorder);
}



bool Capsule::checkWallCollision(const sf::Vector2u& windowSize)
{
    bool collision = false;

    if (pointA.x - radius < 0 || pointA.x + radius > windowSize.x ||
        pointB.x - radius < 0 || pointB.x + radius > windowSize.x)
    {
        velocity.x = -velocity.x;
        collision = true;
    }

    if (pointA.y - radius < 0 || pointA.y + radius > windowSize.y ||
        pointB.y - radius < 0 || pointB.y + radius > windowSize.y)
    {
        velocity.y = -velocity.y;
        collision = true;
    }

    return collision;
}

sf::Vector2f Capsule::getPosition() const 
{
    return (pointA + pointB) / 2.0f; // Midpoint of the capsule
}

float Capsule::getRadius() const 
{
    return radius;
}

sf::Vector2f Capsule::getVelocity() const 
{
    return velocity;
}

// Apply force to resolve collision
void Capsule::applyForce(const sf::Vector2f& force) 
{
    velocity += force * 0.1f;  // Scale the force down to avoid large speed changes
}


float Capsule::shortestDistanceBetweenSegments(const sf::Vector2f& p1, const sf::Vector2f& q1,
    const sf::Vector2f& p2, const sf::Vector2f& q2) const 
{
    // Helper function to calculate the squared distance between two points
    auto sqrDist = [](const sf::Vector2f& a, const sf::Vector2f& b)
        {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
        };

    // Use a line-segment distance algorithm to find the shortest distance between the two segments

    float dist1 = sqrDist(p1, p2);
    float dist2 = sqrDist(p1, q2);
    float dist3 = sqrDist(q1, p2);
    float dist4 = sqrDist(q1, q2);

    // Return the shortest squared distance
    return sqrtf(std::min({ dist1, dist2, dist3, dist4 }));
}

bool Capsule::checkCollision(const Capsule& other) const
{
    // Get the shortest distance between the two line segments (capsules' axes)
    float distance = shortestDistanceBetweenSegments(this->pointA, this->pointB, other.pointA, other.pointB);

    // Check if the distance is less than the sum of their radii
    if (distance < (this->radius + other.radius))
    {
        return true;
    }
    return false;
}
