#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SFML/Graphics.hpp>
#include "Plane.h"
#include "LineSegment.h"
#include "GraphicsHandler.h"

class InputHandler 
{
private:
    Plane& plane;
    LineSegment& lineSegment;
    GraphicsHandler& graphicsHandler;
    bool isSettingLine;       // Toggle between setting line and plane
    bool lineIsSet;           // Indicates if the line is fully set
    bool planeIsSet;          // Indicates if the plane is fully set

public:
    InputHandler(Plane& plane, LineSegment& lineSegment, GraphicsHandler& graphicsHandler);
    void handleEvent(const sf::Event& event);
    bool readyToCheckCollision() const;  // Check if both line and plane are set
    void resetState();
};

#endif
    