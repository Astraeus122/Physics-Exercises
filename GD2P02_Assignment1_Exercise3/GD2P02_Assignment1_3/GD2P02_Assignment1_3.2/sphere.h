#ifndef SPHERE_H
#define SPHERE_H

#include <SFML/Graphics.hpp>

class Sphere
{
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float mass;

    Sphere(float radius, float m, sf::Vector2f position) : mass(m)
    {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);  // Set origin to center for easy positioning
        shape.setPosition(position);
    }

    void applyForce(const sf::Vector2f& force)
    {
        sf::Vector2f acceleration = force / mass;
        velocity += acceleration;  // Update velocity based on the force applied
    }

    void update(float dt)
    {
        shape.move(velocity * dt);  // Update position based on velocity
    }

    void checkBounds(const sf::RenderWindow& window)
    {
        sf::Vector2f pos = shape.getPosition();
        float radius = shape.getRadius();
        float bounceDamping = 0.99f;  // Coefficient to simulate energy loss on bounce

        if (pos.x - radius < 0 || pos.x + radius > window.getSize().x)
        {
            velocity.x *= -bounceDamping;  // Dampen the horizontal velocity
            if (pos.x - radius < 0) shape.setPosition(radius, pos.y);
            else shape.setPosition(window.getSize().x - radius, pos.y);
        }
        if (pos.y - radius < 0 || pos.y + radius > window.getSize().y)
        {
            velocity.y *= -bounceDamping;  // Dampen the vertical velocity
            if (pos.y - radius < 0) shape.setPosition(pos.x, radius);
            else shape.setPosition(pos.x, window.getSize().y - radius);
        }
    }


    void applyFriction(float dt)
    {
        float frictionCoefficient = 0.05f;
        float normalForce = mass * 9.8f;
        float frictionMagnitude = frictionCoefficient * normalForce * dt;

        if (std::abs(velocity.x) > frictionMagnitude)
        {
            velocity.x -= frictionMagnitude * (velocity.x > 0 ? 1 : -1);
        }
        else
        {
            velocity.x = 0;  // Stop the sphere if the friction force exceeds remaining velocity
        }
    }

};

#endif
