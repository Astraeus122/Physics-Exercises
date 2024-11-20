#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <vector>
#include "Vector3.h"
#include "Plane.h"
#include "Triangle.h"
#include "Collision.h"

void drawPlane(sf::RenderWindow& window, const Plane& plane);
void drawTriangle(sf::RenderWindow& window, const Triangle& triangle, const sf::Color& color);
void drawInstructions(sf::RenderWindow& window, const sf::Font& font);

#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <vector>
#include "Vector3.h"
#include "Plane.h"
#include "Triangle.h"
#include "Collision.h"

void drawPlane(sf::RenderWindow& window, const Plane& plane);
void drawTriangle(sf::RenderWindow& window, const Triangle& triangle, const sf::Color& color);
void drawInstructions(sf::RenderWindow& window, const sf::Font& font);

int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle Cutter");
    sf::Font font;
    if (!font.loadFromFile("dependencies/font.ttf")) 
    {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    Plane plane;
    Triangle triangle;
    std::vector<Triangle> triangles;
    bool planePlaced = false;
    bool trianglePlaced = false;

    int trianglePointsPlaced = 0;
    Vector3 tempTrianglePoints[3];
    Vector3 tempPlanePoint;
    Vector3 tempPlaneNormal;

    auto startTime = std::chrono::system_clock::now();

    bool placingPlaneOrigin = false;
    bool placingPlaneNormal = false;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (trianglePlaced) 
                    {
                        trianglePointsPlaced = 0;
                        trianglePlaced = false;
                    }
                    tempTrianglePoints[trianglePointsPlaced] = Vector3(event.mouseButton.x, event.mouseButton.y, 0);
                    trianglePointsPlaced++;
                    if (trianglePointsPlaced == 3)
                    {
                        triangle = Triangle(tempTrianglePoints[0], tempTrianglePoints[1], tempTrianglePoints[2]);
                        trianglePlaced = true;
                        if (planePlaced)
                        {
                            triangles = triangle.split(plane);
                        }
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) 
                {
                    if (!placingPlaneOrigin)
                    {
                        placingPlaneOrigin = true;
                        tempPlanePoint = Vector3(event.mouseButton.x, event.mouseButton.y, 0);
                    }
                    else if (!placingPlaneNormal) 
                    {
                        placingPlaneNormal = true;
                        tempPlaneNormal = Vector3(event.mouseButton.x - tempPlanePoint.x, event.mouseButton.y - tempPlanePoint.y, 0).normalize();
                        plane = Plane(tempPlanePoint, tempPlaneNormal);
                        planePlaced = true;
                        placingPlaneOrigin = false;
                        placingPlaneNormal = false;
                        if (trianglePlaced) 
                        {
                            triangles = triangle.split(plane);
                        }
                    }
                }
            }
        }

        window.clear();

        // Render triangle points and lines during placement
        if (trianglePointsPlaced > 0) 
        {
            for (int i = 0; i < trianglePointsPlaced - 1; ++i) 
            {
                sf::Vertex line[] = 
                {
                    sf::Vertex(sf::Vector2f(tempTrianglePoints[i].x, tempTrianglePoints[i].y)),
                    sf::Vertex(sf::Vector2f(tempTrianglePoints[i + 1].x, tempTrianglePoints[i + 1].y))
                };
                window.draw(line, 2, sf::Lines);
            }
            if (trianglePointsPlaced == 3) 
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(tempTrianglePoints[2].x, tempTrianglePoints[2].y)),
                    sf::Vertex(sf::Vector2f(tempTrianglePoints[0].x, tempTrianglePoints[0].y))
                };
                window.draw(line, 2, sf::Lines);
            }
        }

        if (placingPlaneOrigin) 
        {
            sf::Vertex point(sf::Vector2f(tempPlanePoint.x, tempPlanePoint.y), sf::Color::Red);
            window.draw(&point, 1, sf::Points);
        }

        if (placingPlaneNormal) 
        {
            sf::Vertex planeLine[] = 
            {
                sf::Vertex(sf::Vector2f(tempPlanePoint.x, tempPlanePoint.y), sf::Color::Red),
                sf::Vertex(sf::Vector2f(tempPlanePoint.x + tempPlaneNormal.x * 1000, tempPlanePoint.y + tempPlaneNormal.y * 1000), sf::Color::Red)
            };
            window.draw(planeLine, 2, sf::Lines);
        }

        if (planePlaced) 
        {
            drawPlane(window, plane);
        }

        sf::Color colors[] = { sf::Color::Green, sf::Color::Blue, sf::Color::Yellow };
        for (size_t i = 0; i < triangles.size(); ++i)
        {
            drawTriangle(window, triangles[i], colors[i % 3]);
        }

        auto currentTime = std::chrono::system_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        if (elapsedTime < 20) 
        {
            drawInstructions(window, font);
        }

        window.display();
    }

    return 0;
}

void drawPlane(sf::RenderWindow& window, const Plane& plane) 
{
    sf::Vertex planeLine[] = 
    {
        sf::Vertex(sf::Vector2f(plane.point.x - plane.normal.y * 1000, plane.point.y + plane.normal.x * 1000), sf::Color::Red),
        sf::Vertex(sf::Vector2f(plane.point.x + plane.normal.y * 1000, plane.point.y - plane.normal.x * 1000), sf::Color::Red)
    };
    window.draw(planeLine, 2, sf::Lines);
}

void drawTriangle(sf::RenderWindow& window, const Triangle& triangle, const sf::Color& color) 
{
    sf::ConvexShape triangleShape;
    triangleShape.setPointCount(3);
    triangleShape.setPoint(0, sf::Vector2f(triangle.v0.x, triangle.v0.y));
    triangleShape.setPoint(1, sf::Vector2f(triangle.v1.x, triangle.v1.y));
    triangleShape.setPoint(2, sf::Vector2f(triangle.v2.x, triangle.v2.y));
    triangleShape.setFillColor(color);
    window.draw(triangleShape);
}

void drawInstructions(sf::RenderWindow& window, const sf::Font& font)
{
    sf::Text text;
    text.setFont(font);
    text.setString("Left click to place triangle points\nRight click to place plane origin and normal\nClick again to replace\n");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);
    window.draw(text);
}
