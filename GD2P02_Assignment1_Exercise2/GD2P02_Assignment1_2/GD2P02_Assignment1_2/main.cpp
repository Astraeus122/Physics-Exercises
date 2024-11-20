#include <SFML/Graphics.hpp>
#include "Sphere.h"
#include <vector>
#include <cmath>

int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Euler Integration Demo");
    sf::Vector2f windowCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    std::vector<Sphere> spheres;
    spheres.emplace_back(30.0f, 10.0f, sf::Vector2f(100, 100));
    spheres.emplace_back(20.0f, 5.0f, sf::Vector2f(300, 300));
    spheres.emplace_back(40.0f, 15.0f, sf::Vector2f(500, 200));

    sf::Clock clock;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Apply wind force if left mouse button is held down
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
        {
            sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
            sf::Vector2f windDirection = mousePosition - windowCenter;
            float windStrength = std::sqrt(windDirection.x * windDirection.x + windDirection.y * windDirection.y) / 200.0f;
            windDirection /= std::sqrt(windDirection.x * windDirection.x + windDirection.y * windDirection.y);

            for (auto& sphere : spheres) 
            {
                sphere.applyForce(windDirection * windStrength * sphere.mass);
            }
        }

        // Update
        float dt = clock.restart().asSeconds();
        for (auto& sphere : spheres)
        {
            sphere.applyForce(sf::Vector2f(0, 9.8f * sphere.mass));  // Apply gravity
            sphere.update(dt);
            sphere.checkBounds(window);
        }

        // Render
        window.clear();
        for (const auto& sphere : spheres) 
        {
            window.draw(sphere.shape);
        }
        window.display();
    }

    return 0;
}
