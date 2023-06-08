#pragma once
#include <SFML/Graphics/Transform.hpp>
#include "Transformations.h"

namespace McRenderer
{
    struct Particle
    {
        Particle()
        {
            m_position = sf::Vector2f();
            m_radius = 1.0f;
            m_velocity = sf::Vector2f();
        }

        Particle(sf::Vector2f p_position, float p_radius, sf::Vector2f p_velocity = sf::Vector2f())
        {
            m_position = p_position;
            m_radius = p_radius;
            m_velocity = p_velocity;
        }

        void update(float p_deltaTime)
        {
            m_position += m_velocity * p_deltaTime;
        }

        sf::Vector2f Particle::collision(const Particle& point)
        {
            sf::Vector2f dir = m_position - point.m_position;
            auto distance = Transformations::length(dir);
            if (distance <= (m_radius + point.m_radius) * (m_radius + point.m_radius))
            {
                return dir;
            }
            return sf::Vector2f();
        }

        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
        float m_radius;
    };
}
