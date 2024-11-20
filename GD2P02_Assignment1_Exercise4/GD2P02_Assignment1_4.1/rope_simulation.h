#ifndef ROPE_SIMULATION_H
#define ROPE_SIMULATION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "particle.h"
#include "spring.h"

class RopeSimulation 
{
private:
    std::vector<Particle> particles;
    std::vector<Spring> springs;
    sf::RenderWindow& window;
    bool isDragging;
    int draggedParticleIndex;

    const float PARTICLE_MASS = 1.0f;
    const float SPRING_STIFFNESS = 700.0f; 
    const float SPRING_REST_LENGTH = 20.0f;
    const int NUM_PARTICLES = 20;
    const sf::Vector2f GRAVITY = sf::Vector2f(0, 9.81f * 15);

public:
    RopeSimulation(sf::RenderWindow& win) : window(win), isDragging(false), draggedParticleIndex(-1) 
    {
        particles.emplace_back(sf::Vector2f(400, 100), PARTICLE_MASS, true); // First particle starts locked
        for (int i = 1; i < NUM_PARTICLES; ++i) 
        {
            particles.emplace_back(sf::Vector2f(400 + i * SPRING_REST_LENGTH, 100), PARTICLE_MASS);
        }

        for (size_t i = 0; i < particles.size() - 1; ++i) 
        {
            springs.emplace_back(&particles[i], &particles[i + 1], SPRING_REST_LENGTH, SPRING_STIFFNESS);
        }
    }

    void update(float dt) 
    {

        for (auto& particle : particles) {
            if (!particle.isLocked) 
            {
                particle.force += GRAVITY * particle.mass;
            }
        }

        for (auto& spring : springs) 
        {
            spring.applyForce();
        }

        sf::FloatRect bounds(0, 0, window.getSize().x, window.getSize().y);
        for (auto& particle : particles) 
        {
            particle.update(dt);
            particle.constrain(bounds);
        }
    }

    void draw() {
        for (const auto& spring : springs) 
        {
            sf::Vertex line[] = {
                sf::Vertex(spring.p1->position, sf::Color::White),
                sf::Vertex(spring.p2->position, sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
        }

        for (const auto& particle : particles)
        {
            sf::CircleShape circle(3);
            circle.setFillColor(particle.isLocked ? sf::Color::Red : sf::Color::White);
            circle.setPosition(particle.position - sf::Vector2f(3, 3));
            window.draw(circle);
        }
    }

    void handleInput(sf::Event event) 
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
        {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            for (size_t i = 0; i < particles.size(); ++i) {
                if (std::sqrt(std::pow(mousePos.x - particles[i].position.x, 2) +
                    std::pow(mousePos.y - particles[i].position.y, 2)) < 10) {
                    isDragging = true;
                    draggedParticleIndex = i;
                    particles[i].isLocked = false; // Unlock the particle for dragging
                    break;
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) 
        {
            if (isDragging) 
            {
                particles[draggedParticleIndex].isLocked = true; // Lock the particle in place when released
                particles[draggedParticleIndex].velocity = sf::Vector2f(0, 0);
            }
            isDragging = false;
            draggedParticleIndex = -1;
        }
        else if (event.type == sf::Event::MouseMoved && isDragging) 
        {
            sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
            particles[draggedParticleIndex].position = mousePos;
            particles[draggedParticleIndex].velocity = sf::Vector2f(0, 0);
        }
    }
};

#endif // !ROPE_SIMULATION_H