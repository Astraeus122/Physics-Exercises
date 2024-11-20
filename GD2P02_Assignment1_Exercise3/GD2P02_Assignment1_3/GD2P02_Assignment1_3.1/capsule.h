#ifndef CAPSULE_H
#define CAPSULE_H

#include <SFML/Graphics.hpp>

class Capsule
{
public:
    Capsule(const sf::Vector2f& pointA, const sf::Vector2f& pointB, float radius);

    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool checkWallCollision(const sf::Vector2u& windowSize);
    sf::Vector2f getPosition() const;
    float getRadius() const;
    sf::Vector2f getVelocity() const;

    void applyForce(const sf::Vector2f& force);

    float shortestDistanceBetweenSegments(const sf::Vector2f& p1, const sf::Vector2f& q1, const sf::Vector2f& p2, const sf::Vector2f& q2) const;

    bool checkCollision(const Capsule& other) const;

private:
    sf::Vector2f pointA;
    sf::Vector2f pointB;
    float radius;
    sf::Vector2f velocity;
};

#endif // CAPSULE_H
