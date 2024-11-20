#include "GraphicsHandler.h"
#include <iostream>

GraphicsHandler::GraphicsHandler(sf::RenderWindow& win, const Plane& p, const LineSegment& ls)
    : window(win), plane(p), lineSegment(ls) 
{
    if (!font.loadFromFile("dependencies/font.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
    }

    collisionText.setFont(font);
    collisionText.setCharacterSize(24);
    collisionText.setFillColor(sf::Color::White);
    collisionText.setPosition(10, window.getSize().y - 40);  // Bottom left of the screen

    instructionsText.setFont(font);
    instructionsText.setCharacterSize(20);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(10, 10);  // Top left of the screen
    instructionsText.setString("Instructions:\nLeft click to place the line segment,\nLeft click again to confirm its direction and length.\nRight click to place the plane,\nRight click again to decide its direction and properly place it.\nYou must place a line before placing a plane.");
}

void GraphicsHandler::updateCollisionText(bool isColliding) 
{
    collisionText.setString(isColliding ? "Collision Detected" : "No Collision");
}

void GraphicsHandler::draw() 
{
    window.clear(sf::Color::Black);

    // Draw the line segment
    sf::Vertex lineSegmentVertices[] =
    {
        sf::Vertex(lineSegment.getStartPoint(), sf::Color::Red),
        sf::Vertex(lineSegment.getEndPoint(), sf::Color::Red)
    };
    window.draw(lineSegmentVertices, 2, sf::Lines);

    // Calculate and draw the plane's normal line (for visualization)
    float lineLength = 1000.0f; 
    sf::Vector2f normalStart = plane.getPoint() - sf::Vector2f(plane.getNormal().y, -plane.getNormal().x) * lineLength;
    sf::Vector2f normalEnd = plane.getPoint() + sf::Vector2f(plane.getNormal().y, -plane.getNormal().x) * lineLength;
    sf::Vertex normalLine[] =
    {
        sf::Vertex(normalStart, sf::Color::Green),
        sf::Vertex(normalEnd, sf::Color::Green)
    };
    window.draw(normalLine, 2, sf::Lines);

    // Draw texts
    window.draw(instructionsText);
    window.draw(collisionText);

    window.display();
}

