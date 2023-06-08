#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "Bounds.h"
#include <memory>

namespace McRenderer
{
    class QuadTree
    {
    public:
        QuadTree(const Bounds& p_bounds, int p_treshold)
            :m_bounds(p_bounds), m_threshlod(p_treshold)
        {
            m_leftDown = nullptr;
            m_leftUp = nullptr;
            m_rightUp = nullptr;
            m_rightDown = nullptr;
            float l_thickness = 1.0f;
            m_shape.setPosition(p_bounds.m_position - p_bounds.m_size + sf::Vector2f(l_thickness * 0.5f, l_thickness * 0.5f));
            m_shape.setSize(p_bounds.m_size * 2.0f - sf::Vector2f(l_thickness, l_thickness));
            m_shape.setFillColor(sf::Color::Transparent);
            m_shape.setOutlineThickness(l_thickness);
            m_shape.setOutlineColor(sf::Color::Red);
            m_isDivided = false;
        }

        void insert(const Particle& p_particle)
        {
            if (!m_bounds.contains(p_particle))
            {
                return;
            }
            if (m_particles.size() < m_threshlod)
            {
                m_particles.push_back(p_particle);
            }
            else
            {
                auto l_leftDownBounds = Bounds(m_bounds.m_position + sf::Vector2f(-m_bounds.m_size.x * 0.5f, m_bounds.m_size.y * 0.5f), m_bounds.m_size * 0.5f);

                if (m_leftDown == nullptr)
                {
                    m_leftDown = std::make_unique<QuadTree>(l_leftDownBounds, 4);
                }
                m_leftDown->insert(p_particle);

                auto l_leftUpBounds = Bounds(m_bounds.m_position + sf::Vector2f(-m_bounds.m_size.x * 0.5f, -m_bounds.m_size.y * 0.5f), m_bounds.m_size * 0.5f);

                if (m_leftUp == nullptr)
                {
                    m_leftUp = std::make_unique<QuadTree>(l_leftUpBounds, 4);
                }
                m_leftUp->insert(p_particle);

                auto l_rightUpBounds = Bounds(m_bounds.m_position + sf::Vector2f(m_bounds.m_size.x * 0.5f, -m_bounds.m_size.y * 0.5f), m_bounds.m_size * 0.5f);

                if (m_rightUp == nullptr)
                {
                    m_rightUp = std::make_unique<QuadTree>(l_rightUpBounds, 4);
                }
                m_rightUp->insert(p_particle);

                auto l_rightDownBounds = Bounds(m_bounds.m_position + m_bounds.m_size * 0.5f, m_bounds.m_size * 0.5f);
                if (m_rightDown == nullptr)
                {
                    m_rightDown = std::make_unique<QuadTree>(l_rightDownBounds, 4);
                }
                m_rightDown->insert(p_particle);

                if (!m_isDivided)
                {
                    m_isDivided = true;
                }
            }
        }

        void getAllIntersectingPoints(const Bounds& p_bound, std::vector<Particle>& p_particles, int& p_counter)
        {
            if (!m_bounds.intersectionWithOtherBound(p_bound))
            {
                return;
            }
            else
            {
                for (const auto& l_particle : m_particles)
                {
                    p_counter++;
                    if (p_bound.contains(l_particle))
                    {
                        p_particles.push_back(l_particle);
                    }
                }

                if (m_isDivided)
                {
                    m_leftDown->getAllIntersectingPoints(p_bound, p_particles, p_counter);
                    m_leftUp->getAllIntersectingPoints(p_bound, p_particles, p_counter);
                    m_rightUp->getAllIntersectingPoints(p_bound, p_particles, p_counter);
                    m_rightDown->getAllIntersectingPoints(p_bound, p_particles, p_counter);
                }
            }
        }

        void draw(sf::RenderWindow& p_window)
        {
            if (m_leftDown != nullptr)
            {
                m_leftDown->draw(p_window);
            }
            if (m_leftUp != nullptr)
            {
                m_leftUp->draw(p_window);
            }
            if (m_rightUp != nullptr)
            {
                m_rightUp->draw(p_window);
            }
            if (m_rightDown != nullptr)
            {
                m_rightDown->draw(p_window);
            }
            p_window.draw(m_shape);
        }

        sf::RectangleShape m_shape;

    private:
        std::vector<Particle> m_particles;

        Bounds m_bounds;
        int m_threshlod;
        bool m_isDivided;

        std::unique_ptr<QuadTree> m_leftDown;
        std::unique_ptr<QuadTree> m_leftUp;
        std::unique_ptr<QuadTree> m_rightUp;
        std::unique_ptr<QuadTree> m_rightDown;
    };
}//McRenderer
