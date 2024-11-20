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

        // Check for collision with the window boundaries
        if (pos.x - radius < 0 || pos.x + radius > window.getSize().x) 
        {
            velocity.x *= -1;  // Reverse the horizontal velocity
            if (pos.x - radius < 0) shape.setPosition(radius, pos.y);
            else shape.setPosition(window.getSize().x - radius, pos.y);
        }
        if (pos.y - radius < 0 || pos.y + radius > window.getSize().y)
        {
            velocity.y *= -1;  // Reverse the vertical velocity
            if (pos.y - radius < 0) shape.setPosition(pos.x, radius);
            else shape.setPosition(pos.x, window.getSize().y - radius);
        }
    }
};

#endif
