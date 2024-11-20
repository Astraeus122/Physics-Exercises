#include <SFML/Graphics.hpp>
#include "Polygon.h"
#include <vector>
#include <cmath>

sf::Vector2f normalize(const sf::Vector2f& v)
{
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length != 0) return v / length;
    return sf::Vector2f(0, 0);
}

float dot(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float magnitude(const sf::Vector2f& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

// Get the Minimum Translation Vector (MTV) to resolve collision
sf::Vector2f getMTV(const Polygon& poly1, const Polygon& poly2)
{
    float overlap = std::numeric_limits<float>::max();
    sf::Vector2f smallestAxis;

    // Check all axes from poly1
    for (const auto& axis : poly1.getAxes())
    {
        sf::Vector2f proj1 = poly1.projectOntoAxis(axis);
        sf::Vector2f proj2 = poly2.projectOntoAxis(axis);

        float o = std::min(proj1.y, proj2.y) - std::max(proj1.x, proj2.x);

        if (o < 0) return sf::Vector2f(0, 0); // No collision
        if (o < overlap)
        {
            overlap = o;
            smallestAxis = axis;
        }
    }

    // Check all axes from poly2
    for (const auto& axis : poly2.getAxes())
    {
        sf::Vector2f proj1 = poly1.projectOntoAxis(axis);
        sf::Vector2f proj2 = poly2.projectOntoAxis(axis);

        float o = std::min(proj1.y, proj2.y) - std::max(proj1.x, proj2.x);

        if (o < 0) return sf::Vector2f(0, 0); // No collision
        if (o < overlap)
        {
            overlap = o;
            smallestAxis = axis;
        }
    }

    return normalize(smallestAxis) * overlap;
}

// Resolve collision by separating polygons and applying an impulse
void resolveCollision(Polygon& poly1, Polygon& poly2, const sf::Vector2f& mtv)
{
    sf::Vector2f normal = normalize(mtv);

    // Separate polygons by pushing them apart fully based on the MTV
    poly1.shape.move(-normal * mtv.x * 0.5f); // Move each shape half the distance of MTV
    poly2.shape.move(normal * mtv.x * 0.5f);

    // Relative velocity between the two polygons
    sf::Vector2f relativeVelocity = poly2.velocity - poly1.velocity;

    // Velocity along the normal (collision axis)
    float velocityAlongNormal = dot(relativeVelocity, normal);

    // If the polygons are moving apart, no need to resolve
    if (velocityAlongNormal > 0)
        return;

    // Coefficient of restitution (1 = perfectly elastic collision, 0 = inelastic)
    float e = 0.8f;

    // Calculate the impulse scalar
    float j = -(1 + e) * velocityAlongNormal;
    j /= (1 / poly1.mass + 1 / poly2.mass);

    // Apply impulse to both polygons
    sf::Vector2f impulse = j * normal;
    poly1.velocity -= impulse / poly1.mass;
    poly2.velocity += impulse / poly2.mass;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Separating Axis Theorem");

    std::vector<sf::Vector2f> pentagonPoints =
    {
        sf::Vector2f(0.f, 50.f), sf::Vector2f(50.f, 0.f), sf::Vector2f(100.f, 50.f),
        sf::Vector2f(75.f, 100.f), sf::Vector2f(25.f, 100.f)
    };

    std::vector<sf::Vector2f> hexagonPoints =
    {
        sf::Vector2f(0.f, 30.f), sf::Vector2f(30.f, 0.f), sf::Vector2f(60.f, 30.f),
        sf::Vector2f(60.f, 60.f), sf::Vector2f(30.f, 90.f), sf::Vector2f(0.f, 60.f)
    };

    // Increased the initial velocity for faster movement
    Polygon pentagon(pentagonPoints, sf::Vector2f(150, 150), sf::Vector2f(200, 200), 20.f);
    Polygon hexagon(hexagonPoints, sf::Vector2f(300, 300), sf::Vector2f(-200, -150), 25.f);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        // Update polygons
        pentagon.update(dt);
        hexagon.update(dt);

        // Check for wall collisions
        pentagon.checkBounds(window);
        hexagon.checkBounds(window);

        // Check for SAT collision and resolve
        if (checkSATCollision(pentagon, hexagon))
        {
            sf::Vector2f mtv = getMTV(pentagon, hexagon);

            // Resolve collision using impulse-based method
            resolveCollision(pentagon, hexagon, mtv);
        }

        window.clear();
        window.draw(pentagon.shape);
        window.draw(hexagon.shape);
        window.display();
    }

    return 0;
}
