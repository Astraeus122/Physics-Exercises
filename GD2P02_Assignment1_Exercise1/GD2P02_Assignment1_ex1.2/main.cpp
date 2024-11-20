#include <SFML/Graphics.hpp>
#include "Plane.h"
#include "LineSegment.h"
#include "GraphicsHandler.h"
#include "InputHandler.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Line Segment vs Plane Collision");

    // Create the geometrical objects
    Plane plane;
    LineSegment lineSegment;

    // Initialize handlers
    GraphicsHandler graphicsHandler(window, plane, lineSegment);
    InputHandler inputHandler(plane, lineSegment, graphicsHandler);

    // Start the game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            inputHandler.handleEvent(event);
        }

        // Clear window, draw current state of line and plane, and display
        graphicsHandler.draw();
    }

    return 0;
}
