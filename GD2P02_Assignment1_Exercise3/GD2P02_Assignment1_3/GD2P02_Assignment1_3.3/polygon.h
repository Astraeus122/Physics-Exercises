#ifndef POLYGON_H
#define POLYGON_H

#include <SFML/Graphics.hpp>
#include <vector>

class Polygon 
{
public:
    sf::ConvexShape shape;
    sf::Vector2f velocity;
    float mass;

    Polygon(const std::vector<sf::Vector2f>& points, const sf::Vector2f& position, const sf::Vector2f& initialVelocity, float m)
        : velocity(initialVelocity), mass(m)
    {
        shape.setPointCount(points.size());
        for (size_t i = 0; i < points.size(); ++i) 
        {
            shape.setPoint(i, points[i]);
        }
        shape.setPosition(position);
        shape.setFillColor(sf::Color(255, 0, 0, 100));  // Red with some transparency
    }

    void update(float dt) 
    {
        shape.move(velocity * dt);  // Update position based on velocity
    }

    void checkBounds(const sf::RenderWindow& window)
    {
        sf::FloatRect bounds = shape.getGlobalBounds();
        float bounceDamping = 0.99f;

        if (bounds.left < 0 || bounds.left + bounds.width > window.getSize().x) 
        {
            velocity.x *= -bounceDamping;
            if (bounds.left < 0) shape.setPosition(0, shape.getPosition().y);
            else shape.setPosition(window.getSize().x - bounds.width, shape.getPosition().y);
        }
        if (bounds.top < 0 || bounds.top + bounds.height > window.getSize().y) 
        {
            velocity.y *= -bounceDamping;
            if (bounds.top < 0) shape.setPosition(shape.getPosition().x, 0);
            else shape.setPosition(shape.getPosition().x, window.getSize().y - bounds.height);
        }
    }

    std::vector<sf::Vector2f> getAxes() const
    {
        std::vector<sf::Vector2f> axes;
        for (size_t i = 0; i < shape.getPointCount(); ++i) 
        {
            sf::Vector2f p1 = shape.getTransform().transformPoint(shape.getPoint(i));
            sf::Vector2f p2 = shape.getTransform().transformPoint(shape.getPoint((i + 1) % shape.getPointCount()));
            sf::Vector2f edge = p2 - p1;
            sf::Vector2f axis(-edge.y, edge.x);  // Perpendicular to the edge
            float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
            if (length != 0) axis /= length;  // Normalize axis
            axes.push_back(axis);
        }
        return axes;
    }

    sf::Vector2f projectOntoAxis(const sf::Vector2f& axis) const
    {
        float min = (shape.getTransform().transformPoint(shape.getPoint(0)).x * axis.x + shape.getTransform().transformPoint(shape.getPoint(0)).y * axis.y);
        float max = min;

        for (size_t i = 1; i < shape.getPointCount(); ++i)
        {
            float projection = (shape.getTransform().transformPoint(shape.getPoint(i)).x * axis.x + shape.getTransform().transformPoint(shape.getPoint(i)).y * axis.y);
            if (projection < min) min = projection;
            if (projection > max) max = projection;
        }
        return sf::Vector2f(min, max);
    }

    void applyForce(const sf::Vector2f& force) 
    {
        velocity += force / mass;
    }
};

bool checkSATCollision(const Polygon& poly1, const Polygon& poly2)
{
    std::vector<sf::Vector2f> axes1 = poly1.getAxes();
    std::vector<sf::Vector2f> axes2 = poly2.getAxes();

    // Check all axes of poly1
    for (const auto& axis : axes1)
    {
        sf::Vector2f projection1 = poly1.projectOntoAxis(axis);
        sf::Vector2f projection2 = poly2.projectOntoAxis(axis);

        if (projection1.y < projection2.x || projection2.y < projection1.x) 
        {
            return false;  // No overlap, so no collision
        }
    }

    // Check all axes of poly2
    for (const auto& axis : axes2)
    {
        sf::Vector2f projection1 = poly1.projectOntoAxis(axis);
        sf::Vector2f projection2 = poly2.projectOntoAxis(axis);

        if (projection1.y < projection2.x || projection2.y < projection1.x)
        {
            return false;  // No overlap, so no collision
        }
    }

    return true;  // Collision found
}


#endif // POLYGON_H
