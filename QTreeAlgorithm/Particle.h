#pragma once
#include <SFML/Graphics/Transform.hpp>

namespace McRenderer
{
    struct Particle
    {
        Particle()
        {
            m_position = sf::Vector2f();
            m_radius = 1.0f;
        }

        Particle(sf::Vector2f p_position, float p_radius)
        {
            m_position = p_position;
            m_radius = p_radius;
        }

        sf::Vector2f m_position;
        float m_radius;
    };
}
