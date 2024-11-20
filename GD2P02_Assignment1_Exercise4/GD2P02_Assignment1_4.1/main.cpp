#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "rope_simulation.h"


int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rope Simulation");
    window.setFramerateLimit(60);
    RopeSimulation simulation(window);

    sf::Clock clock;
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
            simulation.handleInput(event);
        }

        float dt = clock.restart().asSeconds();
        simulation.update(dt);

        window.clear(sf::Color::Black);
        simulation.draw();
        window.display();
    }

    return 0;
}