#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Particle
{
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f force;
    float mass;
    bool isLocked;

    Particle(sf::Vector2f pos, float m, bool locked = false)
        : position(pos), velocity(0, 0), force(0, 0), mass(m), isLocked(locked) {}

    void update(float dt) 
    {
        if (!isLocked) {
            velocity += force / mass * dt;
            position += velocity * dt;
            velocity *= 0.97f; // Slight damping
        }
        force = sf::Vector2f(0, 0);
    }

    void constrain(sf::FloatRect bounds) 
    {
        if (!isLocked) 
        {
            if (position.x < bounds.left) 
            {
                position.x = bounds.left;
                velocity.x = 0;
            }
            else if (position.x > bounds.left + bounds.width) 
            {
                position.x = bounds.left + bounds.width;
                velocity.x = 0;
            }
            if (position.y < bounds.top)
            {
                position.y = bounds.top;
                velocity.y = 0;
            }
            else if (position.y > bounds.top + bounds.height)
            {
                position.y = bounds.top + bounds.height;
                velocity.y = 0;
            }
        }
    }
};

#endif // !PARTICLE_H
