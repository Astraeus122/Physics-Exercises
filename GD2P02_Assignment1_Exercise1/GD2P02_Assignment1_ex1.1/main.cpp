#include <SFML/Graphics.hpp>
#include "Plane.h"
#include "Point.h"
#include "Utility.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Plane vs Point Detection");
    sf::Font font;
    if (!font.loadFromFile("dependencies/font.ttf")) 
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    // Text for the current project
    sf::Text exerciseText("Exercise: Plane vs Point Function", font, 20);
    exerciseText.setPosition(10, 10);
    exerciseText.setFillColor(sf::Color::White);

    // Text for the point's position status
    sf::Text statusText("", font, 20);
    statusText.setPosition(10, 560);
    statusText.setFillColor(sf::Color::White);

    Plane plane(sf::Vector2f(400, 300), sf::Vector2f(1, 0));  // Default plane
    Point point(sf::Vector2f(350, 300));  // Default point

    sf::Clock clock; // Starts the clock
    sf::Time textDuration = sf::seconds(3);
    bool displayText = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                point = Point(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)));
                Position pos = findRelativePosition(plane, point);
                switch (pos)
                {
                case Position::OnPlane:
                    statusText.setString("Point is on the plane.");
                    break;
                case Position::InFront:
                    statusText.setString("Point is in front of the plane.");
                    break;
                case Position::Behind:
                    statusText.setString("Point is behind the plane.");
                    break;
                }
                clock.restart(); // Restart the timer
                displayText = true;
            }
        }

        window.clear();
        plane.draw(window);
        point.draw(window);

        // Display exercise text
        window.draw(exerciseText);

        // Display status text and clear it after 3 seconds
        if (displayText) 
        {
            window.draw(statusText);
            if (clock.getElapsedTime() >= textDuration) 
            {
                statusText.setString("");
                displayText = false;
            }
        }

        window.display();
    }

    return 0;
}
