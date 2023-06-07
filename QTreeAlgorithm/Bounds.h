#pragma once
#include <SFML/Graphics/Transform.hpp>
#include "Particle.h"
#include "Transformations.h"

namespace McRenderer
{
    struct Bounds
    {
        sf::Vector2f m_position;
        sf::Vector2f m_size;

        Bounds()
        {
            m_position = sf::Vector2f();
            m_size = sf::Vector2f(1.0f, 1.0f);
        }

        Bounds(sf::Vector2f p_position, sf::Vector2f p_size)
        {
            m_position = p_position;
            m_size = p_size;
        }

        bool contains(const Particle& p_particle)
        {
            sf::Vector2f l_closestPoint = calculateClosestPoint(p_particle);
            float dist = Transformations::distance(l_closestPoint, p_particle.m_position);
            return dist < p_particle.m_radius;
        }

        sf::Vector2f calculateClosestPoint(const Particle& p_particle)
        {
            float x = p_particle.m_position.x;
            float y = p_particle.m_position.y;

            auto l_rightEdge = m_position.x + m_size.x;
            auto l_leftEdge = m_position.x - m_size.x;
            auto l_topEdge = m_position.y + m_size.y;
            auto l_bottomEdge = m_position.y - m_size.y;

            if (x >= l_rightEdge)
            {
                x = l_rightEdge;
            }
            if (x <= l_leftEdge)
            {
                x = l_leftEdge;
            }
            if (y >= l_topEdge)
            {
                y = l_topEdge;
            }
            if (y <= l_bottomEdge)
            {
                y = l_bottomEdge;
            }

            return sf::Vector2f(x, y);
        }
    };
}//McRenderer
