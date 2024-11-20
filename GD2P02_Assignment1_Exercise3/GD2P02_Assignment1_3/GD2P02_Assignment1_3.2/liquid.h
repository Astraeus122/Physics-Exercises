#pragma once
#ifndef LIQUID_H
#define LIQUID_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Liquid
{
public:
    sf::RectangleShape shape;

    Liquid(float x, float y, float width, float height)
    {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
        // Set the fill color to a light blue
        shape.setFillColor(sf::Color(27, 120, 255, 100));  // Light blue but not really light blue because it doesnt seem to want to go to light blue
    }

    bool contains(const Sphere& sphere) const
    {
        sf::Vector2f pos = sphere.shape.getPosition();
        float radius = sphere.shape.getRadius();
        sf::FloatRect bounds = shape.getGlobalBounds();

        return bounds.contains(pos.x, pos.y) || bounds.contains(pos.x + radius, pos.y)
            || bounds.contains(pos.x - radius, pos.y) || bounds.contains(pos.x, pos.y + radius)
            || bounds.contains(pos.x, pos.y - radius);
    }

    void applyDrag(Sphere& sphere) const
    {
        float dragCoefficient = 0.005f; 
        sf::Vector2f velocity = sphere.velocity;
        float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        float dragMagnitude = dragCoefficient * speed * speed / (1 + speed * 0.1); 

        if (speed != 0)
        {
            sf::Vector2f dragForce = -dragMagnitude * (velocity / speed);
            sphere.applyForce(dragForce);
        }
    }
};

#endif
