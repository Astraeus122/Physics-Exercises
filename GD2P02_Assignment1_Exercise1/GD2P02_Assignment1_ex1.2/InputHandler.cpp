#include "InputHandler.h"

InputHandler::InputHandler(Plane& p, LineSegment& ls, GraphicsHandler& gh)
    : plane(p), lineSegment(ls), graphicsHandler(gh), isSettingLine(true), lineIsSet(false), planeIsSet(false) {}

void InputHandler::handleEvent(const sf::Event& event) 
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left && isSettingLine) 
        {
            static bool settingStart = true;
            if (settingStart) 
            {
                lineSegment.setStartPoint(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                settingStart = false;
            }
            else 
            {
                lineSegment.setEndPoint(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                settingStart = true;  // Reset for next line
                isSettingLine = false; // Switch to setting the plane
                lineIsSet = true;      // Line is now fully set
                if (planeIsSet) 
                {      
                    // Check collision if the plane is already set
                    bool isColliding = plane.checkCollision(lineSegment);
                    graphicsHandler.updateCollisionText(isColliding);
                }
            }
        }
        else if (event.mouseButton.button == sf::Mouse::Right && !isSettingLine)
        {
            static bool settingPoint = true;
            if (settingPoint)
            {
                plane.setPlane(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), sf::Vector2f(0, 0));  // First right-click sets the plane point
                settingPoint = false;
            }
            else 
            {
                sf::Vector2f normal = sf::Vector2f(event.mouseButton.x, event.mouseButton.y) - plane.getPoint();
                plane.setPlane(plane.getPoint(), normal);  // Second right-click calculates and sets the normal
                settingPoint = true;  // Reset for next plane
                isSettingLine = true; // Switch back to setting line
                planeIsSet = true;    // Plane is now fully set
                if (lineIsSet)
                {      // Check collision if the line segment is already set
                    bool isColliding = plane.checkCollision(lineSegment);
                    graphicsHandler.updateCollisionText(isColliding);
                }
            }
        }
    }
}

bool InputHandler::readyToCheckCollision() const 
{
    return lineIsSet && planeIsSet;  // Only true if both are fully defined
}

void InputHandler::resetState() {
    lineIsSet = false;
    planeIsSet = false;
}
