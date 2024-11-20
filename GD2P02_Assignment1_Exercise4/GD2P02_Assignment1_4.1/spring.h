#ifndef SPRING_H
#define SPRING_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "particle.h"

class Spring 
{
public:
    Particle* p1;
    Particle* p2;
    float restLength;
    float stiffness;

    Spring(Particle* a, Particle* b, float rest, float k)
        : p1(a), p2(b), restLength(rest), stiffness(k) {}

    void applyForce()
    {
        sf::Vector2f diff = p1->position - p2->position;
        float currentLength = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        sf::Vector2f force = stiffness * (currentLength - restLength) * (diff / currentLength);

        if (!p1->isLocked) p1->force -= force;
        if (!p2->isLocked) p2->force += force;
    }
};

#endif // !SPRING_H