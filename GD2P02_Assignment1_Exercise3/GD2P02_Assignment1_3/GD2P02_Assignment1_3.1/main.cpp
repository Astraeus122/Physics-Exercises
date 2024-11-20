#include <SFML/Graphics.hpp>
#include "Capsule.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Capsule Collision");

    Capsule capsule1(sf::Vector2f(100.f, 300.f), sf::Vector2f(200.f, 300.f), 20.f);
    Capsule capsule2(sf::Vector2f(400.f, 300.f), sf::Vector2f(500.f, 300.f), 20.f);

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

        // Update capsules
        capsule1.update(dt);
        capsule2.update(dt);

        // Check for wall collisions
        capsule1.checkWallCollision(window.getSize());
        capsule2.checkWallCollision(window.getSize());

        // Check for collision between capsules
        if (capsule1.checkCollision(capsule2))
        {
            sf::Vector2f overlapDirection = capsule2.getPosition() - capsule1.getPosition();
            float overlapMagnitude = sqrtf(overlapDirection.x * overlapDirection.x + overlapDirection.y * overlapDirection.y);
            if (overlapMagnitude > 0) 
            {
                overlapDirection /= overlapMagnitude;  // Normalize direction
            }

            // Apply a small force proportional to overlap magnitude to both capsules
            sf::Vector2f force = overlapDirection * 10.f;  // Scale down the force to avoid excessive speedup
            capsule1.applyForce(-force);
            capsule2.applyForce(force);
        }

        window.clear();
        capsule1.draw(window);
        capsule2.draw(window);
        window.display();
    }

    return 0;
}
