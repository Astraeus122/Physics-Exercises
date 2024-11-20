#ifndef GRAPHICS_HANDLER_H
#define GRAPHICS_HANDLER_H

#include <SFML/Graphics.hpp>
#include "Plane.h"
#include "LineSegment.h"

class GraphicsHandler 
{
private:
    sf::RenderWindow& window;
    const Plane& plane;
    const LineSegment& lineSegment;
    sf::Font font;             // Font for displaying text
    sf::Text collisionText;    // Text object to display collision status
    sf::Text instructionsText; // Text object to display instructions

public:
    GraphicsHandler(sf::RenderWindow& window, const Plane& plane, const LineSegment& lineSegment);
    void draw();
    void updateCollisionText(bool isColliding);  // Update the text based on collision
};

#endif
