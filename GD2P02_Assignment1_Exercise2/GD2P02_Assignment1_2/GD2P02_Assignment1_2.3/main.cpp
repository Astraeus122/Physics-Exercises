#include <SFML/Graphics.hpp>
#include "Sphere.h"
#include "Liquid.h"
#include <vector>
#include <cmath>

int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Euler Integration Demo");
    sf::Vector2f windowCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    std::vector<Sphere> spheres;
    spheres.emplace_back(30.0f, 10.0f, sf::Vector2f(100, 200));
    spheres.emplace_back(20.0f, 5.0f, sf::Vector2f(400, 300)); 
    spheres.emplace_back(40.0f, 15.0f, sf::Vector2f(300, 200));

    Liquid liquid(200, 300, 400, 150); 

    sf::Clock clock;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check for mouse button presses
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
                sf::Vector2f windDirection = mousePosition - windowCenter;
                float windStrength = std::sqrt(windDirection.x * windDirection.x + windDirection.y * windDirection.y) / 200.0f;
                windStrength = windStrength * 4;
                windDirection /= std::sqrt(windDirection.x * windDirection.x + windDirection.y * windDirection.y);

                for (auto& sphere : spheres)
                {
                    sphere.applyForce(windDirection * windStrength * sphere.mass);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                for (auto& sphere : spheres)
                {
                    std::cout << "Jumping Force Applied" << std::endl;
                    sphere.applyForce(sf::Vector2f(0, -150000));  // One-off upward force
                }
            }
        }

        // Time step reduced to stabilize simulation
        float dt = clock.restart().asSeconds() * 0.1; 

        for (auto& sphere : spheres) 
        {
            sphere.applyForce(sf::Vector2f(0, 9.8f * sphere.mass));  // Apply gravity

            if (liquid.contains(sphere))
            {
                liquid.applyDrag(sphere);
            }

            if (sphere.shape.getPosition().y + sphere.shape.getRadius() >= window.getSize().y) 
            {
                sphere.applyFriction(dt);
            }

            sphere.update(dt);
            sphere.checkBounds(window);
        }

        // Render
        window.clear();
        window.draw(liquid.shape);  // Draw the liquid
        for (const auto& sphere : spheres) 
        {
            window.draw(sphere.shape);
        }
        window.display();
    }

    return 0;
}
