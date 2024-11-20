#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <SFML/Graphics.hpp>
#include "sphere.h"

class Triangle 
{
public:
    sf::ConvexShape shape;
    sf::Vector2f center;

    Triangle(const sf::Vector2f& point1, const sf::Vector2f& point2, const sf::Vector2f& point3)
    {
        shape.setPointCount(3);
        shape.setPoint(0, point1);
        shape.setPoint(1, point2);
        shape.setPoint(2, point3);
        shape.setFillColor(sf::Color(255, 0, 0, 100));  // Light red

        // Calculate the center of the triangle (centroid)
        center = (point1 + point2 + point3) / 3.0f;
    }

    bool contains(const Sphere& sphere) const 
    {
        // Check if the sphere's position is inside the triangle using barycentric coordinates
        sf::Vector2f p = sphere.shape.getPosition();

        sf::Vector2f v0 = shape.getPoint(1) - shape.getPoint(0);
        sf::Vector2f v1 = shape.getPoint(2) - shape.getPoint(0);
        sf::Vector2f v2 = p - shape.getPoint(0);

        float d00 = v0.x * v0.x + v0.y * v0.y;
        float d01 = v0.x * v1.x + v0.y * v1.y;
        float d11 = v1.x * v1.x + v1.y * v1.y;
        float d20 = v2.x * v0.x + v2.y * v0.y;
        float d21 = v2.x * v1.x + v2.y * v1.y;

        float denom = d00 * d11 - d01 * d01;
        float v = (d11 * d20 - d01 * d21) / denom;
        float w = (d00 * d21 - d01 * d20) / denom;
        float u = 1.0f - v - w;

        return (v >= 0) && (w >= 0) && (u >= 0);
    }

    void applyForceToSphere(Sphere& sphere) const
    {
        // Apply a force away from the center of the triangle
        sf::Vector2f forceDirection = sphere.shape.getPosition() - center;
        float distance = std::sqrt(forceDirection.x * forceDirection.x + forceDirection.y * forceDirection.y);
        if (distance > 0) {
            forceDirection /= distance;  // Normalize the force direction
        }

        // Apply a small force to move the sphere away from the triangle
        sphere.applyForce(forceDirection * 100.f);
    }
};

#endif // TRIANGLE_H
